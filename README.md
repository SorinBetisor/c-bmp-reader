# BMP Reader & Writer in C++

This repository contains a simple C++ program that reads and writes BMP image files. The program is designed to handle 24-bit BMP files, extract image data, and write it to a new binary file. 

## Features

- **BMP Header Parsing**: The program reads the BMP file headers (file header and information header) to extract important metadata, such as:
  - File size
  - Image width and height
  - Pixel format (RGB)
- **Color Matrix Extraction**: The program reads the pixel data (RGB values) and stores them in a matrix, which can be processed or written to another file.
- **Padding Calculation**: Accounts for padding used in BMP files to align each row to a 4-byte boundary.
- **File Writing**: The pixel data can be written back to a new file, preserving the original BMP format.

## How It Works

1. **Initialize an Image**: The BMP file is read, and its headers are parsed to retrieve metadata (file size, width, height, etc.).
2. **Extract Pixel Data**: The program processes each pixel, extracting its RGB values into a `color_matrix`.
3. **Write Data**: The image is written back to a new binary file (`colors.data`).

## Requirements

- A C++ compiler supporting C++11 or higher.
- Standard C++ libraries (`fstream`, `stdint.h`).

## Compilation & Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/bmp-reader.git
