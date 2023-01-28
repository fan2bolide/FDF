#!/bin/bash

make

MAPS=$(find . -type f -name "*.fdf" | cut -c3-)

while IFS= read -r line; do
    leaks -q -atExit -- ./fdf $line >> leaks.log
done <<< "$MAPS"