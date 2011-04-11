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
#include <algorithm>
#include <iostream>
#include <tr1/unordered_map>

#include <htmlcxx/html/ParserDom.h>
#include <htmlcxx/html/utils.h>
#include <htmlcxx/html/CharsetConverter.h>

#define SEPARATORS " \n\t\v\r.,:;?!()[]#=+-_|/<>\"\'"
using namespace std;
using namespace std::tr1;
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
  // Returns empty string if document is not a HTML file. Return string in
  // UTF-8.
  static string ParseHTMLdocument(const string& document);

  // Removes most diacritics from an ISO-8851 string.
  static string RemoveDiacritics(const string& text);


  // Initializes the diacritics map.
  static void InitDiacritics(); 

 private:
  // Maps the diacritics into their correspondents.
  static unordered_map<unsigned char, char> diacritics_;


  Util();
  static bool diacritics_ready_;
};

#endif // UTIL_H
