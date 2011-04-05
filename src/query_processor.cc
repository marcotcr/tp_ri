// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com

#include "./query_processor.h"

QueryProcessor::QueryProcessor() {
}

void QueryProcessor::Init(const string& inverted_index_file,
const string& vocabulary_file, const string& document_url_file) {
  FILE* vocabulary = fopen(vocabulary_file.c_str(), "r");
  char temp_string[100];
  int temp_id;
  while (fscanf(vocabulary, "%s %d", temp_string, &temp_id) == 2) {
    string temp(temp_string);
    vocabulary_[temp] = temp_id;
  }
  fclose(vocabulary);
  int term, number_of_documents, frequency, temp_document;
  FILE* inverted_index = fopen(inverted_index_file.c_str(), "r");
  while (fscanf(inverted_index, "%d %d", &term, &number_of_documents) == 2) {
    for (int i = 0; i < number_of_documents; ++i) {
      fscanf(inverted_index, "%d %d", &temp_document, &frequency);
      DocumentFrequency temp_document_frequency(temp_document, frequency);
      inverted_index_[term].push_back(temp_document_frequency);
    }
  }
  fclose(inverted_index);
  FILE* document_url = fopen(document_url_file.c_str(), "r");
  while (fscanf(document_url, "%d %s", &temp_id, temp_string) == 2) {
    string temp(temp_string);
    document_url_[temp_id] = temp;
  }
  fclose(document_url);
  
}

list<string> QueryProcessor::ProcessQuery(string query) {
  list<string> output;
  list<DocumentFrequency>::iterator it;
  int term = vocabulary_[query];
  for (it = inverted_index_[term].begin(); it != inverted_index_[term].end();
  ++it) {
    output.push_back(document_url_[it->first]); 
  }
  
  return output;
}
