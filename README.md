BMP Reader & Writer in C++
This repository contains a simple C++ program that reads and writes BMP image files. The program reads 24-bit BMP files, extracts the image's pixel data, and writes it back to a new binary file. Key functionality includes reading the BMP headers, extracting image dimensions, calculating padding, and storing pixel data in a matrix.

Features:
BMP Header Parsing: Extracts file size, width, height, and other metadata from the BMP headers.
Pixel Color Extraction: Reads RGB pixel values into a matrix.
Padding Calculation: Accounts for row padding based on the BMP format.
File Writing: Writes the pixel data and headers to a new binary file.
Usage:
The program processes BMP files by reading a specified file (bmp_24.bmp) and outputs the pixel data to colors.data.
