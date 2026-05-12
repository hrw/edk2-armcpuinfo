#!/usr/bin/env python3
"""
Extract only missing fields (not already in registers.yaml).

Usage: python3 extract_only_missing.py <registers.yaml> <Registers.json>
       [register_name]
"""

import json
import yaml
import sys


def extract_field_dict(field):
    """Convert ARM JSON field to Python dict for YAML."""
    if field['_type'] != 'Fields.ConstantField':
        return None

    name = field['name']
    rangeset = field['rangeset'][0]
    start = rangeset['start']
    width = rangeset['width']

    # Calculate bit range
    if width == 1:
        bits = f"{start}"
    else:
        bits = f"{start + width - 1}:{start}"

    # Build field dictionary
    field_dict = {
        'bits': bits,
        'descriptions': {}
    }

    # Extract possible values and conditions
    constraints = field.get('value', {}).get('constraints', {})
    if constraints:
        for val in constraints.get('values', []):
            if val['_type'] == 'Values.Value':
                val_str = val['value'].strip("'")
                val_int = int(val_str, 2)
                field_dict['descriptions'][val_int] = "TODO: Add description"
            elif val['_type'] == 'Values.ConditionalValue':
                # Show what feature this is conditional on
                cond = val.get('condition', {})
                feat = None
                if cond.get('_type') == 'AST.Function':
                    if cond.get('name') == 'IsFeatureImplemented':
                        args = cond.get('arguments', [])
                        if args:
                            feat = args[0].get('value')

                for cv in val['values']['values']:
                    val_str = cv['value'].strip("'")
                    val_int = int(val_str, 2)
                    desc = "TODO: Add description"
                    if feat:
                        desc = f"TODO: {feat} related"
                    field_dict['descriptions'][val_int] = desc

    return name, field_dict


def extract_missing_fields(yaml_file, json_file, filter_reg=None):
    """Extract fields that are in ARM JSON but not in our YAML."""
    # Load YAML
    with open(yaml_file, 'r') as f:
        yaml_data = yaml.safe_load(f)

    # Load JSON
    with open(json_file, 'r') as f:
        json_data = json.load(f)

    # Index ARM registers by name
    arm_registers = {}
    for reg in json_data:
        if (reg.get('_type') == 'Register' and
            reg.get('state') == 'AArch64'):
            name = reg.get('name')
            if name and name.startswith('ID_AA64'):
                arm_registers[name] = reg

    # Build output for missing fields
    missing_data = {}

    for reg_name in sorted(yaml_data.keys()):
        # Filter if requested
        if filter_reg and reg_name != filter_reg:
            continue

        if reg_name not in arm_registers:
            continue

        yaml_fields = set(yaml_data[reg_name].get('fields', {}).keys())

        # Extract ARM fields
        arm_reg = arm_registers[reg_name]
        fieldsets = arm_reg.get('fieldsets', [])
        if not fieldsets:
            continue

        values = fieldsets[0].get('values', [])

        # Find missing fields
        missing_fields = {}
        for field in values:
            result = extract_field_dict(field)
            if result:
                field_name, field_data = result
                if field_name not in yaml_fields:
                    missing_fields[field_name] = field_data

        if missing_fields:
            missing_data[reg_name] = {'fields': missing_fields}

    if missing_data:
        print("# Missing fields to add to registers.yaml:")
        print()
        print(yaml.dump(
            missing_data,
            default_flow_style=False,
            sort_keys=False,
            allow_unicode=True
        ))
    else:
        print("# No missing fields found")


if __name__ == '__main__':
    if len(sys.argv) < 3:
        print(__doc__)
        print("\nExamples:")
        print("  # Show all missing fields:")
        print("  python3 extract_only_missing.py data/registers.yaml "
              "../arm-docs/AARCHMRS/Registers.json")
        print()
        print("  # Show missing fields for one register:")
        print("  python3 extract_only_missing.py data/registers.yaml "
              "../arm-docs/AARCHMRS/Registers.json ID_AA64PFR1_EL1")
        sys.exit(1)

    yaml_file = sys.argv[1]
    json_file = sys.argv[2]
    filter_reg = sys.argv[3] if len(sys.argv) > 3 else None

    extract_missing_fields(yaml_file, json_file, filter_reg)
