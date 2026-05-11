#!/bin/bash
# Pre-build script to generate register handlers from YAML

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

echo "Generating register handlers from data/registers.yaml..."
python3 "$SCRIPT_DIR/generate_handlers.py" \
    "$PROJECT_DIR/data/registers.yaml" \
    "$PROJECT_DIR/id_aa64_all_generated.c" \
    "$PROJECT_DIR/id_aa64.h"

if [ $? -eq 0 ]; then
    echo "✓ Generated id_aa64_all_generated.c and id_aa64.h"
    exit 0
else
    echo "✗ Failed to generate code"
    exit 1
fi
