#!/bin/bash

# Clear the out.csv to re-start the records about experiments
rm -rf "out.csv"

# Generate arry size
for i in {1..100}; do

# Repeat for different permutation based on random generation characters
 for j in {1..1000}; do
 
# Conduct the experiment
	java InsertionSort $i
	
  done

# Change a new line to record data with another input size  
  echo "" >> out.csv

done
