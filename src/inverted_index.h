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
#include <cmath>
#include <htmlcxx/html/ParserDom.h>
#include "./util.h"
#include "./Document.h"
#include "./term_document_frequency.h"
#include "./compressor.h"
#include "./CollectionReader.h"
using namespace RICPNS;

const int MAXIMUM_STRING_SIZE = 50;
const long int AVAILABLE_MEMORY = 10485760;//41943040; // 40 MegaBytes

using namespace std;
using namespace std::tr1;
class InvertedIndex {
 public:
  typedef unordered_map<string, int> TermFrequencyMap;

  // Default constructor - initializes variables. Receives as parameters the
  // directory where the data is and the index file to the document collection.
  InvertedIndex(const string& input_directory, const string& index_filename);

  // Initializes and constructs the inverted index. Writes everything in the
  // appropriate files.
  void Init(const list<Document>& document_list, const string& index_file,
  const string& vocabulary_file, const string& inverted_file, const string&
  document_url_file);
  void PrintTriples();
  
 
 private:
  // Keeps track of document ids.
  int current_document_id_;
  // Maps a term to its id.
  unordered_map<string, int> vocabulary_;

  // Maps a document id to it's URL
  unordered_map<int, string> document_url_;

  // Array of triples. A triple (t, d, f(d,t)) is:
  // t --> term (this is the term's id),
  // d --> document,
  // f(d,t) --> frequency of t in d.
  list<TermDocumentFrequency> triples_;

  // This is used to read the data collection.
  RICPNS::CollectionReader* reader;

  int number_of_runs_;

  int number_of_triples_;

  int size_of_vocabulary_;

  // Parses a document into index terms. Fills an unordered_map of index terms
  // related to their frequency in the document. If an index term is not present
  // in the dictionary yet, it is added to it.
  void ParseIntoIndexTerms(const string& document,
  TermFrequencyMap* index_terms);

  // Processes an index term adding a record <t,d,f(d,t)> to the array of
  // triples.
  void ProcessIndexTerm(const string& index_term,
  const int document, const int term_frequency);

  // Processes the list of documents, writing runs to disk whenever the number
  // of triples threatens the memory capacity.
  void ProcessDocumentList(const list<Document>& document_list, const string&
  document_url_file);

  // Merges the runs into the output file, fully sorted.
  void MergeRuns(const string& output_file);

  // Removes the temporary run files from the disk
  void RemoveTemporaryRuns();

  // Transforms the temporary file in an inverted and an index file. 
  // The index file has the format:
  // term_id position_in_the_inverted_file size in bytes
  // The inverted file is compressed using elias-gamma encoding, and the
  // documents are represented as d-gaps. The format is (for a term):
  // number_of_documents document_id frequency document_id frequency...
  void MakeIndex(const string& temporary_file,const string& inverted_file,
  const string& index_file);
  
  // Writes the vocabulary to a file.
  void WriteVocabulary(const string& file_name);

  // Sorts and writes a run to disk. Will write on file named run%d, %d being
  // the first parameter. Will also clear the triples_ vector.
  // Will print a map of document_urls in the file pointed by the second
  // parameter.
  void WriteRunOnDisk(const int run_number, const string& document_url_file);

  // Appends the relation id -> url to document list
  void AppendDocumentUrlFile(const string& file_name);

};

#endif // INVERTED_INDEX_H
