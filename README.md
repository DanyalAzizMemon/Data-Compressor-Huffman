# Huffman Coding Implementation

This project implements Huffman coding, a widely used algorithm for lossless data compression. Huffman coding assigns variable-length codes to input characters, with shorter codes assigned to more frequent characters, resulting in efficient compression.

## Overview

- **`code.cpp`**: Contains the C++ code implementing Huffman coding algorithm.
- **`Project_Data.txt`**: Sample text file that can be used to test the Huffman coding algorithm.

## Features

- **Huffman Encoding**: Converts input text into compressed binary data using Huffman coding.
- **Huffman Decoding**: Decompresses Huffman-encoded binary data back into the original text.
- **Character Frequency Analysis**: Analyzes the frequency of characters in the input text to determine optimal Huffman codes.
- **Efficient Compression**: Achieves efficient compression by assigning shorter codes to frequently occurring characters.

## Usage

1. Compile and run `code.cpp` using a C++ compiler.
2. Provide the input text file (e.g., `Project_Data.txt`) containing the text to be compressed.
3. The program will output the compressed binary data and additional information, including compression ratios and Huffman codes.

## Example

```bash
$ g++ code.cpp -o huffman
$ ./huffman
Enter the File name you want to open : Project_Data.txt

-----------------Data in file------------------------
a
Number of time repeated : 5
b
Number of time repeated : 9
c
Number of time repeated : 12
d
Number of time repeated : 13
e
Number of time repeated : 16
f
Number of time repeated : 45

Huffman tree decoded Task 1 :
a:- 00000
b:- 00001
c:- 0001
d:- 001
e:- 01
f:- 1

Average Bit rate is : 2.46316
Compression Ratio of Tree 1 is : 3.24786

Huffman tree decoded Task 2 :
f:- 0
c:- 100
d:- 101
a:- 1100
b:- 1101
e:- 111

Average Bit rate is : 2.24
Compression Ratio of Tree 2 is : 3.57143

Huffman tree decoded Tree 3 :
f:- 0
e:- 10
d:- 110
d:- 110
c:- 1110
b:- 11110
a:- 11111

Average Bit rate is : 2.46316
Compression Ratio of Tree 3 is : 3.24786

Using Huffman Tree 2 is better for compression due to its compression ratio of : 3.57143
