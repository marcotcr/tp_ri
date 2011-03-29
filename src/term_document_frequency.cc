#include "./term_document_frequency.h"

TermDocumentFrequency::TermDocumentFrequency(const int term,const string&
document,const int frequency):
term_(term), document_(document), frequency_(frequency) {
}

int TermDocumentFrequency::term() const {
  return term_;
}

string TermDocumentFrequency::document() const {
  return document_;
}

int TermDocumentFrequency::frequency() const {
  return frequency_;
}

bool TermDocumentFrequency::CompareTriples(const TermDocumentFrequency& a,
const TermDocumentFrequency & b) {
  if (a.term() == b.term()) {
    if (a.document() == b.document()) {
      return a.frequency() < b.frequency();
    }
    else {
      // FIXME: check if this is working alphabetically
      return a.document() < b.document();
    }
  }
  else {
    return a.term() < b.term();
  }
}
