// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com

#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include <iostream>
#include <string>
#include <list>
#include <tr1/unordered_map>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "./compressor.h"
#include "./util.h"

using namespace std;
using namespace std::tr1;

typedef pair<int, int> DocumentFrequency;

class QueryProcessor {
 public:
  // Default constructor - does nothing.
  QueryProcessor();
  
  // Reads the inverted index and the vocabulary.
  void Init(const string& inverted_file, const string& index_file,
  const string& vocabulary_file, const string& document_url_file);
  // Returns a list of the documents containing the terms in the query.
  list<string> ProcessQuery(string query);
 private:
  unordered_map<string, int> vocabulary_;
  unordered_map<int, pair<int, int> > index_;
  unordered_map<int, string> document_url_;
  string inverted_file_;
  // Returns a list of the documents containing the word
  vector<int> GetListOfDocuments(string word);
 
  
};

#endif // QUERY_PROCESSOR_H
