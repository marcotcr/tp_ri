#include "./compressor.h"

void Compressor::ConvertToUnary(unsigned int integer,
unsigned char* output, int starting_bit) {
  int i;
  for (i = starting_bit; i < integer + starting_bit - 1; ++i) {
    output[i / 8] = output[i / 8] | 1 << (7 - (i % 8));
  }
  output[i / 8] = output[i / 8] & ~(1 << (7 - (i % 8)));
}

int Compressor::ConvertFromUnary(unsigned char* input, int starting_bit) {
  int i = starting_bit;
  while ((input[i / 8] & (1 << (7 - (i % 8)))) != 0) {
    ++i;
  }
  return i - starting_bit + 1;
}

void Compressor::ConvertToEliasGamma(unsigned int integer,
unsigned char* output, int starting_bit) {
  int log_base_two = floor(log2(integer));
  ConvertToUnary(1 + log_base_two, output, starting_bit);
  starting_bit += 1 + log_base_two;
  unsigned int second_part = integer - (1 << log_base_two);
  int position = log_base_two - 1;
  bool is_set;
  for (int i = starting_bit; i < log_base_two + starting_bit; ++i) {
    // Set the bit to zero.
    output[i / 8] = output[i / 8] & ~(1 << (7 - (i % 8)));
    is_set = (1 << position  & second_part) == 1 << position;
    // The stuff after the last << is just shifting the bits to the desired
    // position.
    output[i / 8] = output[i / 8] | is_set << (7 - (i % 8)) ;
    --position;
  }
}

int Compressor::ConvertFromEliasGamma(unsigned char* input, int starting_bit) {
  int unary = ConvertFromUnary(input, starting_bit);
  starting_bit += unary;
  unsigned int second_part = 0;
  int position = unary - 1 - 1;
  bool is_set;
  for (int i = starting_bit; i < starting_bit + unary - 1; ++i) {
    is_set = (input[i / 8] & (1 << (7 - (i % 8)))) == 1 << (7 - (i % 8));
    second_part = second_part | is_set << position;
    --position;
  }
  return (1 << (unary - 1)) + second_part;
}

