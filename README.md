# INTERNSHIP TASK - 04

# DATA-COMPRESSION-TOOL

 COMPANY: CODTECH IT SOLUTIONS

 NAME: YUKTA ANAND

 INTERN ID: CT04DN1416

 DOMAIN: C PROGRAMMING

 DURATION: 4 WEEKS

 MENTOR: NEELA SANTOSH

#  📘 Explanation of the Program (Run-Length Encoding and Decoding Tool)

This C program implements a basic data compression tool using a method called Run-Length Encoding (RLE). 
It allows the user to compress or decompress a file by specifying a mode and input/output file names from the command line.

# 🔧 1. What is Run-Length Encoding (RLE)?
Run-Length Encoding is a lossless data compression algorithm that is useful when data contains many consecutive repeated characters.

# ✅ Example:

Original Data:

    nginx
          AAAABBBCCDAA

Compressed Data (RLE):

    nginx
          A4B3C2D1A2
          
Each run of characters is replaced by:

-> The character itself

-> The number of times it repeats consecutively

# 📌 2. Components of the Program

🧩 a. runLengthEncode(FILE *infp, FILE *outfp)

-> Reads input character-by-character.

-> Tracks consecutive repeated characters.

-> Writes the character followed by the count (e.g., A4) to the output.

🧩 b. runLengthDecode(FILE *infp, FILE *outfp)

-> Reads character and the digits following it (which represent the count).

-> Reconstructs the original by writing the character multiple times based on the count.

🧩 c. main(int argc, char *argv[])

-> Takes 3 command-line arguments: mode (c for compress, d for decompress), input file, and output file.

-> Opens the files and calls the appropriate function (runLengthEncode or runLengthDecode).

-> Displays success or error messages.

# 📤 3. Usage of the Tool

💡 How to compile:

     bash
          gcc -o rle_tool rle_tool.c
          
💡 How to use:

Compression:

    bash
          ./rle_tool c input.txt compressed.txt
          
Decompression:

    bash
         ./rle_tool d compressed.txt decompressed.txt
         
# 📚 4. Theory Behind Compression Tool

🔍 Why use RLE?

Very efficient for simple, repetitive data, such as:

-> Bitmap images with flat areas (e.g., black/white)

-> Basic textual data with repeated characters

# ❌ Limitations:

Not efficient for data without many repetitions — might even increase size!

   Example: "ABCD" → "A1B1C1D1" (larger than original)

# ⚙️ Design Highlights:

-> Robust error checking (e.g., malformed count, non-printable characters)

-> Uses fgetc and fputc for binary-safe file operations

-> Handles multi-digit counts (e.g., A12 for 12 A's)

# ✅ 5. Summary

            Feature                                         	Description

           Algorithm	                                   Run-Length Encoding (RLE)

          Compression	                        Converts repeated characters to character + count

          Decompression	                      Reconstructs original data from compressed format

           File Type                        	Works with any binary or text file (no format restriction)

            Use Case                            	Simple compression for data with repeated characters

This is a beginner-friendly compression tool that demonstrates core principles of lossless compression and 
can be extended for more advanced formats or integrated into other applications.

 # OUTPUT

 ![Image](https://github.com/user-attachments/assets/8c8992b5-1ac3-4c94-8524-6da66f7d6797)
