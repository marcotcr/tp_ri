// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com

#include "./query_processor.h"

QueryProcessor::QueryProcessor() {
}

void QueryProcessor::Init(const string& inverted_index_file,
const string& vocabulary_file) {
  FILE* vocabulary = fopen(vocabulary_file.c_str(), "r");
  char temp_string[100];
  int temp_id;
  while (fscanf(vocabulary, "%s %d", temp_string, &temp_id) == 2) {
    string temp(temp_string);
    vocabulary_[temp_string] = temp_id;
  }
  fclose(vocabulary);
  int term, number_of_documents, frequency;
  FILE* inverted_index = fopen(inverted_index_file.c_str(), "r");
  while (fscanf(inverted_index, "%d %d", &term, &number_of_documents) == 2) {
    for (int i = 0; i < number_of_documents; ++i) {
      fscanf(inverted_index, "%s %d", temp_string, &frequency);
      string temp(temp_string);
      DocumentFrequency temp_document_frequency(temp, frequency);
      inverted_index_[term].push_back(temp_document_frequency);
    }
  }
  fclose(inverted_index);
}

list<string> QueryProcessor::ProcessQuery(string query) {
  list<string> output;
  list<DocumentFrequency>::iterator it;
  int term = vocabulary_[query];
  for (it = inverted_index_[term].begin(); it != inverted_index_[term].end();
  ++it) {
    output.push_back(it->first); 
  }
  
  return output;
}
