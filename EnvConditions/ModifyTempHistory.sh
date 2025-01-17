#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 input.txt output.txt"
    exit 1
fi

input_file=$1
output_file=$2

awk '{$1=""; print substr($0,2)}' "$input_file" > "$output_file"