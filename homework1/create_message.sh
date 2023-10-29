#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <message>"
    exit 1
fi
mkdir -p workDir
cd workDir || exit 1
echo "$1" > message.txt
echo "Directory and file have been created and filled."
