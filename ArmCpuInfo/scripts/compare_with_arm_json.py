#!/usr/bin/env python3
"""
Compare registers.yaml with ARM's Registers.json to find missing fields.

Usage: python3 compare_with_arm_json.py <registers.yaml> <Registers.json>
"""

import json
import yaml
import sys


def extract_arm_register(reg_data):
    """Extract field information from ARM Registers.json format."""
    fields = {}

    fieldsets = reg_data.get('fieldsets', [])
    if not fieldsets:
        return fields

    # Get the first fieldset (usually the main one)
    values = fieldsets[0].get('values', [])

    for field in values:
        if field['_type'] != 'Fields.ConstantField':
            continue

        name = field['name']
        rangeset = field['rangeset'][0]  # Get first range
        start = rangeset['start']
        width = rangeset['width']

        # Calculate bit range
        if width == 1:
            bits = f"{start}"
        else:
            bits = f"{start + width - 1}:{start}"

        # Extract possible values
        possible_values = []
        constraints = field.get('value', {}).get('constraints', {})
        if constraints:
            for val in constraints.get('values', []):
                if val['_type'] == 'Values.Value':
                    # Convert '0000' to integer
                    val_str = val['value'].strip("'")
                    val_int = int(val_str, 2)
                    possible_values.append(val_int)
                elif val['_type'] == 'Values.ConditionalValue':
                    # Conditional values (like FEAT_LPA)
                    for cv in val['values']['values']:
                        val_str = cv['value'].strip("'")
                        val_int = int(val_str, 2)
                        possible_values.append(val_int)

        fields[name] = {
            'bits': bits,
            'values': sorted(possible_values)
        }

    return fields


def compare_registers(yaml_file, json_file):
    """Compare YAML and JSON register definitions."""
    # Load YAML
    with open(yaml_file, 'r') as f:
        yaml_data = yaml.safe_load(f)

    # Load JSON
    with open(json_file, 'r') as f:
        json_data = json.load(f)

    # Index ARM registers by name
    arm_registers = {}
    for reg in json_data:
        if reg.get('_type') == 'Register' and reg.get('state') == 'AArch64':
            name = reg.get('name')
            if name and name.startswith('ID_AA64'):
                arm_registers[name] = reg

    print("Comparing registers between YAML and ARM JSON...\n")

    # Check each register in our YAML
    for reg_name in sorted(yaml_data.keys()):
        if reg_name not in arm_registers:
            print(f"{reg_name}: NOT FOUND in ARM JSON")
            continue

        yaml_fields = yaml_data[reg_name].get('fields', {})
        arm_fields = extract_arm_register(arm_registers[reg_name])

        # Find fields in ARM but not in YAML
        arm_field_names = set(arm_fields.keys())
        yaml_field_names = set(yaml_fields.keys())

        missing_in_yaml = arm_field_names - yaml_field_names
        missing_in_arm = yaml_field_names - arm_field_names

        if missing_in_yaml or missing_in_arm:
            print(f"\n{reg_name}:")

            if missing_in_yaml:
                print(f"  Fields in ARM JSON but not in YAML:")
                for field in sorted(missing_in_yaml):
                    info = arm_fields[field]
                    print(f"    - {field}: bits {info['bits']}, "
                          f"values {info['values']}")

            if missing_in_arm:
                print(f"  Fields in YAML but not in ARM JSON:")
                for field in sorted(missing_in_arm):
                    print(f"    - {field}")

            # Check for value differences in common fields
            common_fields = arm_field_names & yaml_field_names
            for field in sorted(common_fields):
                yaml_vals = sorted(yaml_fields[field]['descriptions'].keys())
                arm_vals = arm_fields[field]['values']

                if yaml_vals != arm_vals:
                    print(f"  Value mismatch in {field}:")
                    print(f"    YAML has: {yaml_vals}")
                    print(f"    ARM has:  {arm_vals}")


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)

    compare_registers(sys.argv[1], sys.argv[2])
