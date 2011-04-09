// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com
// This is a compendium of useful functions.

#include "util.h"

list<string> Util::SeparateIntoWords(const string& text) {
  string string_ = text;
  Util::StringToLowerCase(&string_);
  char temp_string[string_.size()];
  strcpy(temp_string, string_.c_str());
  char* temp_pointer = strtok(temp_string, SEPARATORS);
  list<string> output;
  while (temp_pointer) {
    //printf("WORD:%s\n",temp_pointer);
    string temp(temp_pointer);
    output.push_back(temp);
    temp_pointer = strtok(NULL, SEPARATORS);
  }
  return output;
}

bool Util::IsHTMLComment(const string& text) {
  string comment = "<!--";
  if (text.find(comment) != string::npos)
    return true;
  else
    return false;
}

void Util::StringToLowerCase(string *text) {
  for (int i = 0; i < (*text).length(); ++i) {
    (*text)[i] = tolower((*text)[i]);
  }
}

string Util::ParseHTMLdocument(const string& document) {
  string output;

  HTML::ParserDom parser;
  tree<HTML::Node> dom = parser.parseTree(document);
  tree<HTML::Node>::iterator it;
  for (it = dom.begin(); it != dom.end(); ++it) {
    if ((!it->isTag()) &&
    (!it->isComment()) &&
    (!Util::IsHTMLComment(it->text())))  {
      output.append(" ");
      output.append(it->text());
    }
  }
  return output;
  
}
