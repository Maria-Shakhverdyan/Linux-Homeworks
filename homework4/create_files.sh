#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo " $0 <N> <Text>"
    exit 1
fi
N="$1"
Text="$2"

if ! [[ "$N" =~ ^[0-9]+$ ]]; then
    echo "N must be integer number"
    exit 1
fi

for ((i=1; i<=N; i++)); do
    filename="file_${i}.txt"
    echo "$Text $i" > "$filename"
    echo "File $filename created with text:  \"$Text $i\""
done

