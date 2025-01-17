#!/bin/bash

if [ $# -ne 3 ]; then
    echo "Usage: $0 input.txt output.txt value_to_add"
    exit 1
fi

input_file=$1
output_file=$2
value_to_add=$3

awk -v add="$value_to_add" '{ $1 = $1 + add; print }' "$input_file" > "$output_file"
