#!/bin/bash

# Prompt info
echo ""
read -p "Please input the size:  " size
echo ""

# Run
java InsertionSort $size

# Prompt
echo ""
echo "Please close the window mannually"
sleep 10000
