// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com
// This is a compendium of useful functions.

#include "util.h"
bool Util::diacritics_ready_ = 0;
unordered_map<unsigned char, char> Util::diacritics_;

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
  string temp = document;
  Util::StringToLowerCase(&temp);
  // This removes non html stuff.
  if (temp.find("content-type: text") == string::npos) {
    return output;
  }
  bool is_UTF8 = HTML::detect_utf8(document.c_str(), document.length());
  HTML::ParserDom parser;
  CharsetConverter converter("ISO-8859-1","ASCII//TRANSLIT");
  string temporary = HTML::decode_entities(document);
  temporary = Util::RemoveDiacritics(temporary);
  if (!is_UTF8) {
    temporary = converter.convert(temporary);
  }
  tree<HTML::Node> dom = parser.parseTree(temporary);
  tree<HTML::Node>::iterator it;
  for (it = dom.begin(); it != dom.end(); ++it) {
    // If this is a script tag, next it is going to be the script content, so
    // skip it.
    if (it->isTag() && it->tagName() == "script") {
      ++it;
      continue;
    }
    if ((!it->isTag()) &&
    (!it->isComment()) &&
    (!Util::IsHTMLComment(it->text())))  {
      output.append(" ");
      output.append(it->text());
     // cout<<"IT: ";
     // cout<<it->text()<<endl;
    }
  }
  return output;
  
}


void Util::InitDiacritics() {
  if (diacritics_ready_ == 1) return;
  diacritics_[192] = 'a';
  diacritics_[193] = 'a';
  diacritics_[194] = 'a';
  diacritics_[195] = 'a';
  diacritics_[196] = 'a';
  diacritics_[197] = 'a';
  diacritics_[199] = 'c';
  diacritics_[200] = 'e';
  diacritics_[201] = 'e';
  diacritics_[202] = 'e';
  diacritics_[203] = 'e';
  diacritics_[204] = 'i';
  diacritics_[205] = 'i';
  diacritics_[206] = 'i';
  diacritics_[210] = 'o';
  diacritics_[211] = 'o';
  diacritics_[212] = 'o';
  diacritics_[213] = 'o';
  diacritics_[217] = 'u';
  diacritics_[218] = 'u';
  diacritics_[219] = 'u';
  diacritics_[224] = 'a';
  diacritics_[225] = 'a';
  diacritics_[226] = 'a';
  diacritics_[227] = 'a';
  diacritics_[231] = 'c';
  diacritics_[232] = 'e';
  diacritics_[232] = 'e';
  diacritics_[233] = 'e';
  diacritics_[234] = 'e';
  diacritics_[236] = 'i';
  diacritics_[237] = 'i';
  diacritics_[238] = 'i';
  diacritics_[242] = 'o';
  diacritics_[243] = 'o';
  diacritics_[244] = 'o';
  diacritics_[245] = 'o';
  diacritics_[246] = 'o';
  diacritics_[249] = 'u';
  diacritics_[250] = 'u';
  diacritics_[251] = 'u';
  diacritics_[252] = 'u';
  diacritics_ready_ = 1;
}

string Util::RemoveDiacritics(const string& text) {
  string output = text;
  Util::InitDiacritics();
  unordered_map<unsigned char, char>::iterator it;
  for (it = Util::diacritics_.begin(); it != Util::diacritics_.end(); ++it) {
    replace(output.begin(), output.end(), (char)it->first, it->second);
  }
  return output;
  
}
