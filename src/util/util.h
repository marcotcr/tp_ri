// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com
// This is a compendium of useful functions.

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <list>
#include <cstdio>
#include <cstring>

#define SEPARATORS " \n\t\v\r.,:;?!()[]#=+-_|/<>\"\'"
using namespace std;

// Aggregates useful static methods.
class Util {
 public:
  // Splits a string into a list of words.
  static list<string> SeparateIntoWords(const string& text);

  // Returns true if string contains an html comment - false otherwise. The input
  // string for this function must be one returned by htmlcxx functions.
  static bool IsHTMLComment(string text);

  // Converts a string to lowercase.
  static void StringToLowerCase(string *text);
 private:
  Util();
};

#endif // UTIL_H
