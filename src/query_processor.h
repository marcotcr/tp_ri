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

using namespace std;
using namespace std::tr1;

class QueryProcessor {
 public:
  typedef pair<string, int> DocumentFrequency;
  // Default constructor - does nothing.
  QueryProcessor();
  
  // Reads the inverted index and the vocabulary.
  void Init(const string& inverted_index_file, const string& vocabulary_file);
  // Returns a list of the documents containing the terms in the query.
  list<string> ProcessQuery(string query);
 private:
  unordered_map<string, int> vocabulary_;
  unordered_map<int, list<DocumentFrequency> > inverted_index_;
  
};

#endif // QUERY_PROCESSOR_H
