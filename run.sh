#!/bin/bash

# Remove any .png and .csv files if they exist
# DO NOT TOUCH UNLESS YOU UNDERSTAND! USER DISCRETION: ULTRA HIGH!
rm *.png
rm *.csv

#Safe to edit:
# Set the C++ file and output file names
cpp_file="A4.cpp"
output_file="A4_Part1"

# Compile the C++ code
g++ $cpp_file -o $output_file

# Run the compiled C++ code to generate the CSV files
./$output_file
echo "CSV files generated!"

# Run the Python script to generate the plots from the CSV files
python3 A4_Plot.py
