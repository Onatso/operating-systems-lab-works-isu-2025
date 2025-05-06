#!/bin/bash

# Argument check
if [ $# -eq 0 ]; then
    source_dir=$(pwd)
elif [ $# -eq 1 ]; then
    if [ -d "$1" ]; then
        source_dir=$(realpath "$1")
    else
        echo "Error: directory '$1' does not exist." >&2
        exit 1
    fi
else
    echo "Usage: $0 [directory]" >&2
    exit 1
fi

# Create backup directory with timestamp
timestamp=$(date +"%Y%m%d_%H%M%S")
backup_dir="backup_$timestamp"
mkdir -p "$backup_dir" || exit 1

# Find and copy image files with directory structure preservation
count=0
cd "$source_dir" || exit 1
while IFS= read -r -d '' file; do
    install -D -m 644 "$file" "$backup_dir/$file"
    ((count++))
done < <(find . -type f \( -iname "*.jpg" -o -iname "*.jpeg" -o -iname "*.png" -o -iname "*.gif" -o -iname "*.bmp" -o -iname "*.tiff" \) -print0)

# Output report
echo "Copied files: $count"
echo "Backup created at: $(realpath "$backup_dir")"
