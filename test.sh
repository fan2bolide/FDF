#!/bin/bash

make

MAPS=$(find . -type f -name "*.fdf" | cut -c3-)

while IFS= read -r line; do
    ./fdf $line
done <<< "$MAPS"