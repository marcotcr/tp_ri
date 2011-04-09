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

#include <htmlcxx/html/ParserDom.h>

#define SEPARATORS " \n\t\v\r.,:;?!()[]#=+-_|/<>\"\'"
using namespace std;
using namespace htmlcxx;

// Aggregates useful static methods.
class Util {
 public:
  // Splits a string into a list of words. Makes everything lowercase.
  static list<string> SeparateIntoWords(const string& text);

  // Returns true if string contains an html comment - false otherwise. The input
  // string for this function must be one returned by htmlcxx functions.
  static bool IsHTMLComment(const string& text);

  // Converts a string to lowercase.
  static void StringToLowerCase(string *text);

  // Parses an html file using htmlcxx and returns a string with the text.
  static string ParseHTMLdocument(const string& document);
 private:
  Util();
};

#endif // UTIL_H
