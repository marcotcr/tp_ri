#include "./inverted_index.h"
#include <sstream>
InvertedIndex::InvertedIndex(const string& output_file,
const list<string>& document_list) {
  TermFrequencyMap index_terms;
  int i = 1;
  // FIXME: this is not supposed to be here in the constructor.
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
     dictionary_[*it] = dictionary_.size();
    }
    (*index_terms)[*it]++;
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
}
