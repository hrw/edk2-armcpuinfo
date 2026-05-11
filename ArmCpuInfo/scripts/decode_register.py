#!/usr/bin/env python3
"""
Decode ARM CPU register values using YAML definitions.

Usage:
    decode_register.py MMFR1 0x12101111
    decode_register.py ID_AA64MMFR1_EL1 0x12101111
    decode_register.py SMFR0 0x8000000100000000
"""

import yaml
import sys
import argparse
import shutil


def parse_bits_field(bits):
    """Parse bits field to extract shift amount and mask.

    Examples:
        "63:60" -> shift=60, width=4
        "3:0"   -> shift=0, width=4
        "63"    -> shift=63, width=1

    Returns:
        tuple: (shift, width)
    """
    bits = bits.strip()

    if ':' in bits:
        high, low = bits.split(':')
        shift = int(low.strip())
        width = int(high.strip()) - shift + 1
        return shift, width
    else:
        shift = int(bits)
        return shift, 1


def normalize_register_name(name):
    """Convert register name to full ID_AA64*_EL1 format.

    Examples:
        "MMFR1" -> "ID_AA64MMFR1_EL1"
        "ID_AA64MMFR1_EL1" -> "ID_AA64MMFR1_EL1"
        "mmfr1" -> "ID_AA64MMFR1_EL1"
    """
    name = name.upper()

    if name.startswith("ID_AA64"):
        return name

    # Add prefix and suffix
    return f"ID_AA64{name}_EL1"


def decode_register(register_data, value):
    """Decode a register value and return field information.

    Args:
        register_data: Register definition from YAML
        value: Integer value of the register

    Returns:
        list: List of (field_name, bits, field_value, description) tuples
    """
    results = []
    fields = register_data.get('fields', {})

    for field_name, field_data in fields.items():
        bits = field_data['bits']
        shift, width = parse_bits_field(bits)
        mask = (1 << width) - 1

        # Extract field value
        field_value = (value >> shift) & mask

        # Get description
        descriptions = field_data.get('descriptions', {})
        description = descriptions.get(field_value, "unknown")

        # Check if conditional
        conditional = field_data.get('conditional')

        results.append({
            'name': field_name,
            'bits': bits.strip(),
            'value': field_value,
            'description': description,
            'conditional': conditional
        })

    return results


def format_output(register_name, register_value, results):
    """Format decoded register output.

    Returns:
        int: Number of unknown field values detected
    """
    reg_short = register_name.replace('ID_AA64', '').replace('_EL1', '')

    # Get terminal width (default to 80 if unavailable)
    terminal_width = shutil.get_terminal_size(fallback=(80, 24)).columns

    # Calculate space for description column
    # Fixed columns: Reg(5) + " | "(3) + Field(12) + " | "(3) +
    #                Bits(5) + " | "(3) + Value(6) + " | "(3)
    # Total fixed = 40 characters
    desc_width = max(terminal_width - 40, 20)

    print(f"Register: {register_name}")
    print(f"Value:    0x{register_value:016x}")
    print()
    print("Reg   | Field        | Bits  | Value  | Description")
    # Adjust separator line to terminal width
    sep_desc = "-" * min(desc_width, 50)
    print(f"------|--------------|-------|--------|{sep_desc}")

    unknown_count = 0

    for r in results:
        # Format bits field for alignment
        bits = r['bits']
        if ':' in bits:
            # Range like "63:60" or "11:8"
            high, low = bits.split(':')
            bits_display = f"{int(high):02d}:{int(low):02d}"
            bit_width = int(high) - int(low) + 1
        else:
            # Single bit like "63" -> right-align to 5 chars
            bits_display = f"{int(bits):>5}"
            bit_width = 1

        # Format value as binary with appropriate width
        # (b0001 format like C code)
        value_display = f"b{r['value']:0{bit_width}b}"

        # Truncate description based on available terminal width
        desc = r['description']
        conditional_marker = " *" if r['conditional'] else ""
        # Reserve 3 chars for conditional marker and ellipsis
        max_desc = desc_width - (3 if r['conditional'] else 0)

        if len(desc) > max_desc:
            desc = desc[:max_desc - 3] + "..."

        # Track unknown values
        # Use full description, not truncated
        if r['description'] == "unknown":
            unknown_count += 1

        print(
            f"{reg_short:5} | {r['name']:12} | {bits_display} | "
            f"{value_display:6} | {desc}{conditional_marker}"
        )

    # Print warnings and notes
    print()
    if any(r['conditional'] for r in results):
        print("* = Conditional field (may not always be displayed)")
        print()

    if unknown_count > 0:
        print(
            f"WARNING: {unknown_count} field(s) have "
            f"unknown/undefined values!"
        )
        print("This may indicate:")
        print("  - New CPU features not yet documented in YAML")
        print("  - Reserved field values being used")
        print("  - Incorrect register value")
        print()

    return unknown_count


def check_unhandled_registers(
    register_name, value, all_registers, unknown_count
):
    """Check if register has issues and show warnings."""
    # Registers known to be incomplete or work-in-progress
    wip_registers = {
        'ID_AA64MMFR3_EL1':
            'MMFR3 has placeholder descriptions for many fields',
    }

    # Show extra warning if register is WIP and has unknown values
    if register_name in wip_registers and unknown_count > 0:
        print("=" * 70)
        print("NOTE: This register definition is incomplete.")
        print(f"      {wip_registers[register_name]}")
        print()
        print(
            "If you're seeing this on real hardware, "
            "please consider:"
        )
        print(
            "  - Adding proper field descriptions to "
            "registers_full.yaml"
        )
        print(
            "  - Opening an issue at "
            "https://github.com/hrw/edk2-armcpuinfo/issues"
        )
        print("  - Including this full output")
        print("=" * 70)
        print()

    # Show general message if many unknown values
    elif unknown_count >= 3:
        print("=" * 70)
        print("NOTICE: Multiple unknown field values detected.")
        print()
        print("This could mean:")
        print(
            "  - Your CPU has newer features not yet in ARM specs"
        )
        print("  - The YAML definitions need updating")
        print("  - There's an issue with the register value")
        print()
        print(
            "Consider reporting at: "
            "https://github.com/hrw/edk2-armcpuinfo/issues"
        )
        print("=" * 70)
        print()


def main():
    parser = argparse.ArgumentParser(
        description='Decode ARM CPU ID register values',
        epilog='''
Examples:
  %(prog)s MMFR1 0x12101111
  %(prog)s ID_AA64MMFR1_EL1 0x12101111
  %(prog)s SMFR0 0x8000000100000000
  %(prog)s pfr0 0x0000000011111111
        ''',
        formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        'register',
        help='Register name (MMFR1, ID_AA64MMFR1_EL1, etc.)'
    )
    parser.add_argument(
        'value',
        help='Register value in hex (0x1234... or 1234...)'
    )
    parser.add_argument(
        '-y', '--yaml', default='registers.yaml',
        help='YAML file with register definitions '
             '(default: registers.yaml)'
    )

    args = parser.parse_args()

    # Load YAML
    try:
        with open(args.yaml, 'r') as f:
            registers = yaml.safe_load(f)
    except FileNotFoundError:
        print(f"Error: YAML file '{args.yaml}' not found", file=sys.stderr)
        sys.exit(1)

    # Normalize register name
    register_name = normalize_register_name(args.register)

    # Check if register exists
    if register_name not in registers:
        print(
            f"Error: Register '{args.register}' not found in YAML",
            file=sys.stderr
        )
        print(f"Tried: {register_name}", file=sys.stderr)
        print("\nAvailable registers:", file=sys.stderr)
        for reg in sorted(registers.keys()):
            short = reg.replace('ID_AA64', '').replace('_EL1', '')
            print(f"  {short:10} ({reg})", file=sys.stderr)
        sys.exit(1)

    # Parse value
    try:
        if args.value.startswith('0x') or args.value.startswith('0X'):
            value = int(args.value, 16)
        else:
            value = int(args.value, 16)  # Assume hex even without 0x prefix
    except ValueError:
        print(f"Error: Invalid hex value '{args.value}'", file=sys.stderr)
        sys.exit(1)

    # Decode register
    register_data = registers[register_name]
    results = decode_register(register_data, value)

    # Format and print output
    unknown_count = format_output(register_name, value, results)

    # Check if this register needs special warnings
    check_unhandled_registers(register_name, value, registers, unknown_count)


if __name__ == "__main__":
    main()
