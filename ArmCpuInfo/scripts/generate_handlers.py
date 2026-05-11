#!/usr/bin/env python3
"""
Generate C code for ARM register field handlers from YAML definitions.

Usage: generate_handlers.py <registers.yaml> <output.c> <output.h>

Copyright (c) 2026, Marcin Juszkiewicz
SPDX-License-Identifier: BSD-2-Clause-Patent
"""

import yaml
import sys
from pathlib import Path


def get_register_short_name(register_id):
    """Convert register ID to short name.

    Example: ID_AA64MMFR1_EL1 -> MMFR1
    """
    return register_id.replace('ID_AA64', '').replace('_EL1', '')


def get_param_name(register_id):
    """Convert register ID to parameter name.

    Example: ID_AA64MMFR1_EL1 -> Aa64Mmfr1
    """
    base = register_id.replace('ID_', '').replace('_EL1', '')
    base = base.replace('_', '')
    # Take suffix after "AA64" and capitalize first letter only
    suffix = base[4:]  # Everything after "AA64"
    suffix = suffix[0].upper() + suffix[1:].lower() if suffix else ''
    return 'Aa64' + suffix


def get_read_function_name(register_id):
    """Convert register ID to ArmLib read function name.

    Example: ID_AA64MMFR1_EL1 -> ArmReadIdAA64Mmfr1
    """
    base = register_id.replace('ID_', '').replace('_EL1', '')
    base = base.replace('_', '')
    suffix = base[4:]  # Everything after "AA64"
    suffix = suffix[0].upper() + suffix[1:].lower() if suffix else ''
    return f"ArmReadIdAA64{suffix}"


def generate_description_arrays(register_name, fields):
    """Generate static description arrays for all fields."""
    arrays = []

    for field_name, field_data in fields.items():
        descriptions = field_data['descriptions']

        # Check if this is a sparse array (non-consecutive keys)
        desc_keys = sorted(descriptions.keys())
        max_key = max(desc_keys)
        is_sparse = desc_keys != list(range(max_key + 1))

        arrays.append(f"  STATIC CONST CHAR8 *{field_name}Desc[] = {{")

        if is_sparse:
            # Use designated initializers for sparse arrays
            for key in desc_keys:
                comma = "," if key != desc_keys[-1] else ""
                arrays.append(f'    [{key}] = "{descriptions[key]}"{comma}')
        else:
            # Dense array - simple list
            for key in desc_keys:
                comma = "," if key != max_key else ""
                arrays.append(f'    "{descriptions[key]}"{comma}')

        arrays.append("  };")

    return "\n".join(arrays)


def parse_bits_field(bits):
    """Parse bits field to extract shift amount and mask.

    Examples:
        "63:60" -> shift=60, mask=0xf (4 bits)
        "3:0"   -> shift=0, mask=0xf (4 bits)
        "   63" -> shift=63, mask=0x1 (1 bit)
        "11:8"  -> shift=8, mask=0xf (4 bits)

    Returns:
        tuple: (shift, mask_hex_string)
    """
    bits = bits.strip()

    if ':' in bits:
        # Range like "63:60"
        high, low = bits.split(':')
        shift = int(low.strip())
        bit_count = int(high.strip()) - shift + 1
        mask = (1 << bit_count) - 1
        return shift, f"0x{mask:x}"
    else:
        # Single bit like "63"
        shift = int(bits)
        return shift, "0x1"


def generate_field_handler(
    register_param, field_name, field_data, reg_name_var
):
    """Generate code for handling one register field."""
    bits = field_data['bits'].strip()  # Remove any extra spaces from YAML
    conditional = field_data.get('conditional')

    # Parse bits field to get shift and mask
    shift, mask = parse_bits_field(bits)

    # Format bits field for display (pad single-bit fields for alignment)
    # "63:60" stays as is, "63" becomes "   63"
    if ':' not in bits:
        # Single bit - pad to 5 chars for alignment
        bits_display = f"{bits:>5}"
    else:
        # 11:8, 7:4, 3:0 entries
        if len(bits) < 5:
            bits = f"{bits} "
        bits_display = bits

    bits_str = f'"{bits_display}"'

    code = []

    # If conditional, wrap in if statement
    if conditional:
        code.append(f"  Name = \"{field_name}\";")
        code.append("  // conditional field")
        code.append(f"  if ({conditional})")
        code.append("  {{")
        indent = "  "
    else:
        code.append(f"  Bits  = {bits_str};")
        code.append(f"  Name  = \"{field_name}\";")
        indent = ""

    # Generate the field extraction and printing
    if shift == 0:
        code.append(f"{indent}  Value = {register_param} & {mask};")
    else:
        code.append(
            f"{indent}  Value = ({register_param} >> {shift}) & "
            f"{mask};"
        )

    # For sparse arrays, check both bounds AND NULL pointer
    cond1 = f"Value < ARRAY_SIZE({field_name}Desc)"
    cond2 = f"{field_name}Desc[Value] != NULL"
    code.append(f"{indent}  if ({cond1} && {cond2}) {{")
    code.append(f"{indent}    Description = {field_name}Desc[Value];")
    code.append(f"{indent}  }} else {{")
    code.append(f"{indent}    Description = \"unknown\";")
    code.append(f"{indent}  }}")

    # Track unknown values
    code.append(
        f"{indent}  if (AsciiStrCmp(Description, \"unknown\") == 0) {{"
    )
    code.append(f"{indent}    UnknownCount++;")
    code.append(f"{indent}  }}")

    if conditional:
        code.append(
            f'{indent}  PrintValues ({reg_name_var}, Name, '
            f'"{bits_display}", Value, Description);'
        )
        code.append("  }}")
    else:
        code.append(
            f"{indent}  PrintValues ({reg_name_var}, Name, "
            f"Bits, Value, Description);"
        )

    return "\n".join(code)


def generate_warnings(register_id, fields):
    """Generate warning messages for unknown values and WIP registers."""
    code = []

    # Count how many fields have placeholder descriptions
    placeholder_count = sum(
        1 for field_data in fields.values()
        if any(desc == "." for desc in
               field_data.get('descriptions', {}).values())
    )

    code.append("  // Warn about unknown/undefined field values")
    code.append("  if (UnknownCount > 0) {")
    code.append('    AsciiPrint("\\n");')
    code.append(
        '    AsciiPrint("WARNING: %u field(s) have '
        'unknown/undefined values!\\n", UnknownCount);'
    )
    code.append('    AsciiPrint("This may indicate:\\n");')
    code.append(
        '    AsciiPrint("  - New CPU features not yet '
        'documented\\n");'
    )
    code.append(
        '    AsciiPrint("  - Reserved field values being used\\n");'
    )
    code.append('    AsciiPrint("  - Incorrect register value\\n");')

    if placeholder_count > 3:
        code.append('    AsciiPrint("\\n");')
        code.append(
            '    AsciiPrint("NOTE: Multiple fields have '
            'placeholder descriptions.\\n");'
        )
        code.append('    AsciiPrint("Consider reporting at:\\n");')
        code.append(
            '    AsciiPrint("  '
            'https://github.com/hrw/edk2-armcpuinfo/issues\\n");'
        )

    code.append("  }")

    return "\n".join(code)


def generate_function(register_id, register_data):
    """Generate complete function for handling a register."""
    reg_name = get_register_short_name(register_id)
    param_name = get_param_name(register_id)
    fields = register_data['fields']

    function_name = f"Handle{param_name}"

    # Function header
    code = [
        "/**",
        f"  Handle {register_id} system register.",
        "",
        f"  @param[in] {param_name}  value of "
        f"{register_id} system register",
    ]

    # Check if any field has conditional that requires Aa64Pfr0
    needs_pfr0 = any(
        'Aa64Pfr0' in field.get('conditional', '')
        for field in fields.values()
    )
    if needs_pfr0:
        code.append(
            "  @param[in] Aa64Pfr0,  value of ID_AA64PFR0_EL1 system register"
        )

    code.extend([
        "",
        "  @retval Number of unknown field values encountered",
        "**/",
        "UINT32",
        f"{function_name} (",
    ])

    if needs_pfr0:
        code.extend([
            f"  CONST UINT64  {param_name}, CONST UINT64  Aa64Pfr0"
        ])
    else:
        code.append(f"  CONST UINT64  {param_name}")

    code.extend([
        "  )",
        "{",
        "  UINT64              Value;",
        f'  STATIC CONST CHAR8  RegName[] = "{reg_name}";',
        "  CONST CHAR8         *Description;",
        "  CONST CHAR8         *Name;",
        "  CONST CHAR8         *Bits;",
        "  UINT32              UnknownCount = 0;",
        "",
    ])

    # Generate description arrays
    code.append(generate_description_arrays(reg_name, fields))
    code.append("")

    # Generate field handlers
    field_handlers = []
    for field_name, field_data in fields.items():
        field_handlers.append(
            generate_field_handler(
                param_name, field_name, field_data, "RegName"
            )
        )

    code.append("\n\n".join(field_handlers))

    # Return the unknown count
    code.append("")
    code.append("  return UnknownCount;")
    code.append("}")

    return "\n".join(code)


def generate_header(registers):
    """Generate file header with ArmRead* function declarations."""
    lines = [
        "/** @file",
        "  GENERATED FILE - DO NOT EDIT",
        "  Generated from registers.yaml by generate_handlers.py",
        "",
        "Copyright (c) 2026, Marcin Juszkiewicz<BR>",
        "",
        "SPDX-License-Identifier: BSD-2-Clause-Patent",
        "",
        "**/",
        "",
        "#include <Library/UefiLib.h>",
        "#include <Library/ArmLib/AArch64/AArch64Lib.h>",
        "#include \"AArch64LibExtra.h\"",
        "#include \"common.h\"",
        "",
        "// ArmLib register read function declarations",
    ]

    # Generate declarations for all registers
    for register_id in registers.keys():
        read_func = get_read_function_name(register_id)
        lines.append(f"UINT64 {read_func} (VOID);")

    lines.append("")

    return "\n".join(lines)


def generate_h_file_header():
    """Generate header file (.h) header."""
    return """/** @file
  GENERATED FILE - DO NOT EDIT
  Generated from registers.yaml by generate_handlers.py

Copyright (c) 2026, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/
"""


def generate_function_declaration(register_id, register_data):
    """Generate function declaration for header file."""
    param_name = get_param_name(register_id)
    fields = register_data['fields']

    # Check if any field requires Aa64Pfr0
    needs_pfr0 = any(
        'Aa64Pfr0' in field.get('conditional', '')
        for field in fields.values()
    )

    decl = ["UINT32"]
    decl.append(f"Handle{param_name} (")

    if needs_pfr0:
        decl.append(f"  CONST UINT64  {param_name}, CONST UINT64  Aa64Pfr0")
    else:
        decl.append(f"  CONST UINT64  {param_name}")

    decl.append("  );")

    return "\n".join(decl)


def generate_process_all_function(registers):
    """Generate ProcessAllRegisters() that handles all registers."""
    # Convert register IDs to parameter names
    reg_info = []
    for register_id in registers.keys():
        param_name = get_param_name(register_id)

        # Determine if Pfr0 parameter is needed
        fields = registers[register_id]['fields']
        needs_pfr0 = any(
            'Aa64Pfr0' in field.get('conditional', '')
            for field in fields.values()
        )

        reg_info.append({
            'id': register_id,
            'param': param_name,
            'func': f"Handle{param_name}",
            'needs_pfr0': needs_pfr0
        })

    code = [
        "/**",
        "  Process all ID_AA64*_EL1 registers.",
        "",
        "  Reads all registers, prints their values, and calls handlers.",
        "**/",
        "VOID",
        "ProcessAllRegisters (",
        "  VOID",
        "  )",
        "{",
    ]

    # Declare all register variables (both handled and unhandled)
    for info in reg_info:
        code.append(f"  UINT64  {info['param']};")

    # Add unhandled registers
    unhandled_regs = [
        'Aa64Afr0', 'Aa64Afr1', 'Aa64Dfr1', 'Aa64Dfr2',
        'Aa64Fpfr0', 'Aa64Isar3', 'Aa64Mmfr4', 'Aa64Pfr2'
    ]
    for ureg in unhandled_regs:
        code.append(f"  UINT64  {ureg};")

    code.append("")

    # Read all registers (both handled and unhandled)
    for info in reg_info:
        read_func = get_read_function_name(info['id'])
        code.append(f"  {info['param']} = {read_func} ();")

    # Read unhandled registers
    for ureg in unhandled_regs:
        # Convert param name back to register ID
        # Aa64Afr0 -> AFR0 -> ID_AA64AFR0_EL1
        suffix = ureg[4:]  # Everything after "Aa64"
        register_id = f"ID_AA64{suffix.upper()}_EL1"
        read_func = get_read_function_name(register_id)
        code.append(f"  {ureg} = {read_func} ();")

    code.append("")

    # Print all register values
    for info in reg_info:
        pad = " " * (17 - len(info['id']))
        code.append(
            f'  AsciiPrint ("{info["id"]}{pad}= 0x%016lx\\n", '
            f'{info["param"]});'
        )

    # Print unhandled register values
    unhandled_reg_ids = [
        ('Aa64Afr0', 'ID_AA64AFR0_EL1'),
        ('Aa64Afr1', 'ID_AA64AFR1_EL1'),
        ('Aa64Dfr1', 'ID_AA64DFR1_EL1'),
        ('Aa64Dfr2', 'ID_AA64DFR2_EL1'),
        ('Aa64Fpfr0', 'ID_AA64FPFR0_EL1'),
        ('Aa64Isar3', 'ID_AA64ISAR3_EL1'),
        ('Aa64Mmfr4', 'ID_AA64MMFR4_EL1'),
        ('Aa64Pfr2', 'ID_AA64PFR2_EL1')
    ]
    for param, reg_id in unhandled_reg_ids:
        pad = " " * (17 - len(reg_id))
        code.append(
            f'  AsciiPrint ("{reg_id}{pad}= 0x%016lx\\n", '
            f'{param});'
        )

    code.append('  AsciiPrint ("\\n");')
    code.append("")
    code.append(
        '  PrintText ("Reg", "Name", "Bits", "Value", "Feature");'
    )
    code.append('  PrintSpacer ();')
    code.append("")

    # Declare variables to track unknown values
    code.append("  UINT32 TotalUnknowns = 0;")
    code.append("  UINT32 UnknownCount = 0;")
    code.append("  UINT32 RegistersWithUnknowns = 0;")
    code.append(
        "  CONST CHAR8 *RegisterNames[20];  "
        "// Max registers with unknowns"
    )
    code.append("")

    # Call handlers for all registers
    # Base registers (ending in 0) always shown, others if non-zero
    for i, info in enumerate(reg_info):
        # Check if this is a base register
        # (MMFR0, PFR0, ISAR0, DFR0, etc.)
        is_base = (
            info['param'].endswith('0') or
            info['param'] in [
                'Aa64Mmfr0', 'Aa64Pfr0', 'Aa64Isar0', 'Aa64Dfr0'
            ]
        )

        reg_short_name = info['id'].replace('ID_AA64', '')
        reg_short_name = reg_short_name.replace('_EL1', '')

        if is_base:
            # Always show base registers
            if info['needs_pfr0']:
                code.append(
                    f"  UnknownCount = {info['func']} "
                    f"({info['param']}, Aa64Pfr0);"
                )
            else:
                code.append(
                    f"  UnknownCount = {info['func']} "
                    f"({info['param']});"
                )
            code.append("  PrintSpacer ();")
            code.append("  if (UnknownCount > 0) {")
            code.append(
                f'    RegisterNames[RegistersWithUnknowns++] = '
                f'"{reg_short_name}";'
            )
            code.append("    TotalUnknowns += UnknownCount;")
            code.append("  }")
        else:
            # Others only if register value is non-zero
            code.append(f"  if ({info['param']}) {{")
            if info['needs_pfr0']:
                code.append(
                    f"    UnknownCount = {info['func']} "
                    f"({info['param']}, Aa64Pfr0);"
                )
            else:
                code.append(
                    f"    UnknownCount = {info['func']} "
                    f"({info['param']});"
                )
            code.append("    PrintSpacer ();")
            code.append("    if (UnknownCount > 0) {")
            code.append(
                f'      RegisterNames[RegistersWithUnknowns++] = '
                f'"{reg_short_name}";'
            )
            code.append("      TotalUnknowns += UnknownCount;")
            code.append("    }")
            code.append("  }")

        if i < len(reg_info) - 1:
            code.append("")

    # Print summary of unknown values at the end
    code.append("")
    code.append("  // Print summary of unknown values")
    code.append("  if (TotalUnknowns > 0) {")
    code.append('    AsciiPrint ("\\n");')
    code.append(
        '    AsciiPrint ("WARNING: %u field(s) have '
        'unknown/undefined values!\\n", TotalUnknowns);'
    )
    code.append('    AsciiPrint ("Affected registers: ");')
    code.append(
        "    for (UINT32 i = 0; i < RegistersWithUnknowns; i++) {"
    )
    code.append("      AsciiPrint (\"%a\", RegisterNames[i]);")
    code.append("      if (i < RegistersWithUnknowns - 1) {")
    code.append('        AsciiPrint (", ");')
    code.append("      }")
    code.append("    }")
    code.append('    AsciiPrint ("\\n");')
    code.append('    AsciiPrint ("\\n");')
    code.append('    AsciiPrint ("This may indicate:\\n");')
    code.append(
        '    AsciiPrint ("  - New CPU features not yet '
        'documented in YAML\\n");'
    )
    code.append(
        '    AsciiPrint ("  - Reserved field values being '
        'used\\n");'
    )
    code.append(
        '    AsciiPrint ("  - Incorrect register value\\n");'
    )
    code.append('    AsciiPrint ("\\n");')
    code.append(
        '    AsciiPrint ("Consider reporting at: '
        'https://github.com/hrw/edk2-armcpuinfo/issues\\n");'
    )
    code.append("  }")
    code.append("")
    code.append(
        "  // Check if any unhandled registers have non-zero values"
    )
    code.append(
        "  if (Aa64Afr0 | Aa64Afr1 | Aa64Dfr1 | Aa64Dfr2 | "
        "Aa64Fpfr0 |"
    )
    code.append("      Aa64Isar3 | Aa64Mmfr4 | Aa64Pfr2) {")
    code.append('    AsciiPrint ("\\n");')
    code.append(
        '    AsciiPrint ("Your system has unhandled registers with '
        'non-zero values.\\n");'
    )
    code.append(
        '    AsciiPrint ("Please contact author and report at:\\n");'
    )
    code.append(
        '    AsciiPrint ("  '
        'https://github.com/hrw/edk2-armcpuinfo/issues\\n");'
    )
    code.append('    AsciiPrint ("\\n");')
    code.append("  }")
    code.append("}")

    return "\n".join(code)


def main():
    if len(sys.argv) < 2:
        print(
            "Usage: generate_handlers.py <registers.yaml> "
            "[output.c] [output.h]"
        )
        sys.exit(1)

    yaml_file = Path(sys.argv[1])
    if len(sys.argv) > 2:
        output_c_file = Path(sys.argv[2])
    else:
        output_c_file = Path("id_aa64_all_generated.c")
    if len(sys.argv) > 3:
        output_h_file = Path(sys.argv[3])
    else:
        output_h_file = Path("id_aa64.h")

    # Load YAML
    with open(yaml_file, 'r') as f:
        registers = yaml.safe_load(f)

    # Generate C code
    c_code = [generate_header(registers)]
    for register_id, register_data in registers.items():
        c_code.append(generate_function(register_id, register_data))
        c_code.append("")

    # Add ProcessAllRegisters function
    c_code.append(generate_process_all_function(registers))
    c_code.append("")

    # Write C file
    with open(output_c_file, 'w') as f:
        f.write("\n".join(c_code))
    print(f"Generated {output_c_file}")

    # Generate H file
    h_code = [generate_h_file_header()]
    for register_id, register_data in registers.items():
        h_code.append(generate_function_declaration(register_id,
                                                    register_data))
        h_code.append("")

    # Add ProcessAllRegisters declaration
    h_code.append("VOID")
    h_code.append("ProcessAllRegisters (")
    h_code.append("  VOID")
    h_code.append("  );")
    h_code.append("")

    # Write H file
    with open(output_h_file, 'w') as f:
        f.write("\n".join(h_code))
    print(f"Generated {output_h_file}")


if __name__ == "__main__":
    main()
