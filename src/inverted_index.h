#include <iostream>
#include <string>
#include <list>
#include <tr1/unordered_map>
#include <vector>
#include <algorithm>
#include "./util.h"
#include "./term_document_frequency.h"
using namespace std;
using namespace std::tr1;
class InvertedIndex {
 public:
  typedef unordered_map<string, int> TermFrequencyMap;
  InvertedIndex(const string& output_file, const list<string>& document_list);
  void PrintTriples();
  
 
 private:
  // unordered_maps a term to its id.
  unordered_map<string, int> dictionary_;

  // Array of triples. A triple (t, d, f(d,t)) is:
  // t --> term (this is the term's id),
  // d --> document,
  // f(d,t) --> frequency of t in d.
  vector<TermDocumentFrequency> triples_;

  // Parses a document into index terms. Fills an unordered_map of index terms
  // related to their frequency in the document. If an index term is not present
  // in the dictionary yet, it is added to it.
  void ParseIntoIndexTerms(const string& document,
  TermFrequencyMap* index_terms);

  // Processes an index term adding a record <t,d,f(d,t)> to the array of
  // triples.
  void ProcessIndexTerm(const string& index_term,
  const string& document, const int term_frequency);

};
