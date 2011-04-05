#include <string>

using namespace std;

// Represents a triple (t, d, f(d,t)). That is:
// t --> term (this is the term's id),
// d --> document,
// f(d,t) --> frequency of t in d.
class TermDocumentFrequency {
 public: 
  // Default constructor - does nothing.
  TermDocumentFrequency();

  // Constructor
  TermDocumentFrequency(const int term, const int document,
  const int frequency);
  
  // Returns the term's id
  int term() const;

  // Returns the document's identifier.
  int document() const;

  // Returns the frequency.
  int frequency() const;

  // This is used to sort the triples by term, document and frequency (in that
  // order).
  static bool CompareTriples(const TermDocumentFrequency& a,
  const TermDocumentFrequency & b);

 private:
  int term_;
  int document_;
  int frequency_;
};
