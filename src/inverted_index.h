// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com

#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <iostream>
#include <string>
#include <list>
#include <tr1/unordered_map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "./util.h"
#include "./Document.h"
#include "./term_document_frequency.h"
using namespace RICPNS;

const int MAXIMUM_STRING_SIZE = 50;
const long int AVAILABLE_MEMORY = 41943040; // 40 MegaBytes

using namespace std;
using namespace std::tr1;
class InvertedIndex {
 public:
  typedef unordered_map<string, int> TermFrequencyMap;

  // Default constructor - initializes variables.
  InvertedIndex();

  // Initializes and constructs the inverted index. Uses the output file as
  // final output.
  void Init(const string& output_file, const list<Document>& document_list);
  void PrintTriples();
  
 
 private:
  // Maps a term to its id.
  unordered_map<string, int> vocabulary_;

  // Array of triples. A triple (t, d, f(d,t)) is:
  // t --> term (this is the term's id),
  // d --> document,
  // f(d,t) --> frequency of t in d.
  list<TermDocumentFrequency> triples_;

  int number_of_runs_;

  // Parses a document into index terms. Fills an unordered_map of index terms
  // related to their frequency in the document. If an index term is not present
  // in the dictionary yet, it is added to it.
  void ParseIntoIndexTerms(const string& document,
  TermFrequencyMap* index_terms);

  // Processes an index term adding a record <t,d,f(d,t)> to the array of
  // triples.
  void ProcessIndexTerm(const string& index_term,
  const string& document, const int term_frequency);

  // Processes the list of documents, writing runs to disk whenever the number
  // of triples threatens the memory capacity.
  void ProcessDocumentList(const list<Document>& document_list);

  // Merges the runs into the output file, fully sorted.
  void MergeRuns(const string& output_file);

  // Removes the temporary run files from the disk
  void RemoveTemporaryRuns();

  // Transforms the temporary file in an index file. The index file has the
  // format:
  // term_id number_of_documents document1 frequency1 document2 frequency2...
  void MakeIndex(const string& temporary_file,const string& output);
  
  // Writes the vocabulary to a file.
  void WriteVocabulary(const string& file_name);

  // Sorts and writes a run to disk. Will write on file named run%d, %d being
  // the first parameter. Will also clear the triples_ vector.
  void WriteRunOnDisk(const int run_number);

};

#endif // INVERTED_INDEX_H
