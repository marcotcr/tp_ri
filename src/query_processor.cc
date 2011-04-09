// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com

#include "./query_processor.h"

QueryProcessor::QueryProcessor() {
}

void QueryProcessor::Init(const string& inverted_file, const string& index_file,
const string& vocabulary_file, const string& document_url_file) {
  FILE* vocabulary = fopen(vocabulary_file.c_str(), "r");
  char temp_string[1000];
  string oi;
  int temp_id;
  while (fscanf(vocabulary, "%s %d", temp_string, &temp_id) == 2) {
    string temp(temp_string);
    vocabulary_[temp] = temp_id;
  }
  fclose(vocabulary);
  
  int term, position, size;
  FILE* index = fopen(index_file.c_str(), "r");
  while (fscanf(index, "%d %d %d", &term, &position, &size) == 3) {
    pair<int, int> temp_pair(position, size);
    index_[term] = temp_pair;
  }
  fclose(index);
  
  FILE* document_url = fopen(document_url_file.c_str(), "r");
  while (fscanf(document_url, "%d %s", &temp_id, temp_string) == 2) {
    string temp(temp_string);
    document_url_[temp_id] = temp;
  }
  fclose(document_url);
  inverted_file_ = inverted_file;
}

list<string> QueryProcessor::ProcessQuery(string query) {
  list<string> words = Util::SeparateIntoWords(query);
  int i = 1;
  list<string>::iterator it;
  bool is_and = 0;
  vector<int> list_of_documents;
  for (it = words.begin(); it != words.end(); ++it) {
    // If it is a word
    if (i % 2 == 1) {
      vector<int> temp_list = this->GetListOfDocuments(*it);
      sort(temp_list.begin(), temp_list.end());
      vector<int> output (list_of_documents.size() + temp_list.size());
      if (is_and) {
        set_intersection(list_of_documents.begin(), list_of_documents.end(),
        temp_list.begin(), temp_list.end(), output.begin()); 
      }
      else {
        set_union(list_of_documents.begin(), list_of_documents.end(),
        temp_list.begin(), temp_list.end(), output.begin()); 
      }
      list_of_documents.clear();
      list_of_documents.swap(output);
    }
    else {
      if (*it == "and") is_and = 1;
      else is_and = 0;
    }
    ++i;
  }
  list<string> output;
  for (int i = 0; i < list_of_documents.size(); ++i) {
    if (list_of_documents[i] != 0) {
      output.push_back(document_url_[list_of_documents[i]]);
    } 
  }
  return output;
  /*list<DocumentFrequency>::iterator it;
  list<DocumentFrequency> temp = this->GetListOfDocuments(query);
  for (it = temp.begin(); it != temp.end(); ++it) {
    output.push_back(document_url_[it->first]); 
  }
  return output;*/
}

vector<int> QueryProcessor::GetListOfDocuments(string word) {
  vector<int> output;
  if (vocabulary_.count(word) == 0) {
    return output;
  }
  int position = index_[vocabulary_[word]].first;
  int size = index_[vocabulary_[word]].second;
  FILE* inverted_file = fopen(inverted_file_.c_str(), "r");
  fseek(inverted_file, position, SEEK_SET);
  unsigned char temp[size];
  fread(temp, 1, size, inverted_file);
  int number_of_documents = Compressor::ConvertFromEliasGamma(temp, 0);
  int bits = 1 + 2 * floor(log2(number_of_documents)); 
  int bytes = bits/8;
  bits = bits % 8;
  int previous_document = 0;
  int document, frequency;
  for (int i = 0; i < number_of_documents; ++i) {
    document = Compressor::ConvertFromEliasGamma(&temp[bytes], bits);
    bits += 1 + 2 * floor(log2(document));
    bytes += bits / 8;
    bits = bits % 8;
    frequency = Compressor::ConvertFromEliasGamma(&temp[bytes], bits);
    bits += 1 + 2 * floor(log2(frequency));
    bytes += bits / 8;
    bits = bits % 8;
    output.push_back(document + previous_document);
    previous_document += document;
  }
  return output;
}
