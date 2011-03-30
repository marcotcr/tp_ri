#include "./inverted_index.h"
#include <sstream>

InvertedIndex::InvertedIndex() {
}

void InvertedIndex::Init(const string& output_file,
const list<string>& document_list) {
  // It contains a string, so its size must be added by MAXIMUM_STRING_SIZE.
  int size_of_triple = sizeof(TermDocumentFrequency) + sizeof(char) *
  MAXIMUM_STRING_SIZE;
  // This is approximate, so be careful.
  int maximum_number_of_triples;
  int number_of_runs = 0;


  TermFrequencyMap index_terms;
  int i = 1;
  for (list<string>::const_iterator it = document_list.begin();
  it != document_list.end(); ++it) {
    this->ParseIntoIndexTerms(*it, &index_terms);
    TermFrequencyMap::iterator it2;
    for (it2 = index_terms.begin(); it2 != index_terms.end(); ++it2) {
      stringstream oi;
      oi<<i;
      string d;
      oi >> d;
      this->ProcessIndexTerm(it2->first, d, it2->second);
      // This is the size of the map structure plus the size of the elements.
      int size_of_dictionary = sizeof(dictionary_) + dictionary_.size() *
      (MAXIMUM_STRING_SIZE + sizeof(int));
      //maximum_number_of_triples = (AVAILABLE_MEMORY - size_of_dictionary)/
      //size_of_triple;
      maximum_number_of_triples = 3;
      if (maximum_number_of_triples <= triples_.size()) {
        this->WriteRunOnDisk(number_of_runs++);
      }
    }
    ++i;
    index_terms.clear();
  }
}


void InvertedIndex::ParseIntoIndexTerms(const string& document,
TermFrequencyMap* index_terms) {
  list<string> terms = Util::SeparateIntoWords(document);
  list<string>::iterator it;
  for (it = terms.begin(); it != terms.end(); ++it) {
    if (dictionary_.count(*it) == 0) {
     // Only allow for MAXIMUM_STRING_SIZE characters max for each word.
     dictionary_[(*it).substr(0,MAXIMUM_STRING_SIZE)] = dictionary_.size();
    }
    (*index_terms)[(*it).substr(0,MAXIMUM_STRING_SIZE)]++;
  }
}

void InvertedIndex::ProcessIndexTerm(const string& index_term,
const string& document, const int term_frequency) {
  TermDocumentFrequency temp(dictionary_[index_term], document, term_frequency);
  triples_.push_back(temp);
}

void InvertedIndex::PrintTriples() {
  sort(triples_.begin(), triples_.end(), TermDocumentFrequency::CompareTriples);
  for (int i = 0; i < triples_.size(); ++i) {
    std::cout<< triples_[i].term() << " " << triples_[i].document() << " " <<
    triples_[i].frequency() << std::endl;
  }
  std::string oi = "ae manolos";
  std::cout<< sizeof(char)<<std::endl;
}

//FIXME(make this be encoded, and maybe use fwrite and etc)
void InvertedIndex::WriteRunOnDisk(int run_number) {
  stringstream stream;
  stream << run_number;
  string file_name;
  stream >> file_name;
  file_name = "run" + file_name;
  sort(triples_.begin(), triples_.end(), TermDocumentFrequency::CompareTriples);
  FILE *output = fopen(file_name.c_str(), "w");
  for (int i = 0; i < triples_.size(); ++i) {
    fprintf(output, "%d %s %d\n", triples_[i].term(),
    triples_[i].document().c_str(), triples_[i].frequency());
  }
  triples_.clear();
}
