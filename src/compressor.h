// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com

#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Class with static methods for compression and decompression
class Compressor {
 public:

  // Writes the integer to the output stream in the unary form, starting in the
  // bit passed by the third parameter. If you want to start in the second byte
  // of a certain stream, pass a pointer to that byte as the second parameter.
  // Example: ConvertToUnary(1, string[3], 3).
  // It will always use n bits, n being the first parameter.
  static void ConvertToUnary(unsigned int integer, unsigned char* output, int
  starting_bit);

  // Reads a sequence of bits in unary form from the input stream, starting at
  // the bit passed by the second parameter and converts it the decimal.
  // This will have read n (the return value) bits.
  static int ConvertFromUnary(unsigned char* input, int starting_bit);

  // Writes the integer to the output stream in the elias gamma form, starting
  // in the bit passed by the third parameter. If you want to start in the
  // second byte of a certain stream, pass a pointer to that byte as the second
  // parameter. Example: ConvertToEliasGamma(1, string[3], 3).
  // This will always use 1 + 2 * floor(log2(n)) bits, n being the first
  // parameter. If you want to start at a certain byte, do something like:
  // char temp[10];
  // ConvertToEliasGamma(10, &temp[1], 0);
  static void ConvertToEliasGamma(unsigned int integer, unsigned char* output,
  int starting_bit);

  // Reads a sequence of bits in elias gamma form from the input stream,
  // starting at the bit passed by the second parameter and converts it the
  // decimal.
  // This will have read 1 + 2 * floor(log2(n)) bits, n being the return value. 
  static int ConvertFromEliasGamma(unsigned char* input, int starting_bit);
};

#endif // COMPRESSOR_H
