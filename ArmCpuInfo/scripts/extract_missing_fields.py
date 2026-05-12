#!/usr/bin/env python3
"""
Extract missing fields from ARM Registers.json in YAML format.

Usage: python3 extract_missing_fields.py <Registers.json> <register_name>
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


def extract_register_fields(json_file, register_name):
    """Extract all fields from a register."""
    with open(json_file, 'r') as f:
        data = json.load(f)

    # Find the register
    for reg in data:
        if (reg.get('_type') == 'Register' and
            reg.get('state') == 'AArch64' and
            reg.get('name') == register_name):

            fieldsets = reg.get('fieldsets', [])
            if not fieldsets:
                print(f"# {register_name}: No fieldsets found")
                return

            # Build register dictionary
            register_dict = {
                register_name: {
                    'fields': {}
                }
            }

            values = fieldsets[0].get('values', [])

            for field in values:
                result = extract_field_dict(field)
                if result:
                    field_name, field_data = result
                    register_dict[register_name]['fields'][field_name] = (
                        field_data
                    )

            # Output as YAML
            print(yaml.dump(
                register_dict,
                default_flow_style=False,
                sort_keys=False,
                allow_unicode=True
            ))
            return

    print(f"# Register {register_name} not found", file=sys.stderr)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print(__doc__)
        print("\nExample:")
        print("  python3 extract_missing_fields.py Registers.json "
              "ID_AA64MMFR0_EL1")
        sys.exit(1)

    extract_register_fields(sys.argv[1], sys.argv[2])
