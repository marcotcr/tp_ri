#include "./inverted_index.h"
#include <sstream>

InvertedIndex::InvertedIndex(): number_of_runs_(0), current_document_id_(1) {
}

void InvertedIndex::Init(const string& output_file,
const list<Document>& document_list) {
  this->ProcessDocumentList(document_list);
  string temporary_file = "temp_file";
  this->MergeRuns(temporary_file);
  this->RemoveTemporaryRuns();
  this->MakeIndex(temporary_file, output_file);
  string vocabulary_file = "vocabulary";
  this->WriteVocabulary(vocabulary_file);
}

void InvertedIndex::ProcessDocumentList(const list<Document>& document_list) {
  // It contains a string, so its size must be added by MAXIMUM_STRING_SIZE.
  int size_of_triple = sizeof(TermDocumentFrequency);
  // This is approximate, so be careful.
  int maximum_number_of_triples;
  int number_of_runs = 0;


  TermFrequencyMap index_terms;
  for (list<Document>::const_iterator it = document_list.begin();
  it != document_list.end(); ++it) {
    this->ParseIntoIndexTerms((*it).getText(), &index_terms);
    TermFrequencyMap::iterator it2;

    // FIXME: Think about removing equal URLS.
    document_url_[current_document_id_] = (*it).getURL();
    int document = current_document_id_++;

    for (it2 = index_terms.begin(); it2 != index_terms.end(); ++it2) {

       
      this->ProcessIndexTerm(it2->first, document, it2->second);
      // This is the size of the map structure plus the size of the elements.
      int size_of_vocabulary = sizeof(vocabulary_) + vocabulary_.size() *
      (MAXIMUM_STRING_SIZE + sizeof(int));
      //maximum_number_of_triples = (AVAILABLE_MEMORY - size_of_vocabulary)/
      //size_of_triple;
      maximum_number_of_triples = 5;
      if (maximum_number_of_triples <= triples_.size()) {
        this->WriteRunOnDisk(number_of_runs_++);
      }
    }
    index_terms.clear();
  }
  if (!triples_.empty()) {
    this->WriteRunOnDisk(number_of_runs_++);
  }
}
// This is used to compair a pair triple, run.
bool ComparePairTripleRun(const pair<TermDocumentFrequency, int>& a,
const pair<TermDocumentFrequency, int>& b) {
  return !TermDocumentFrequency::CompareTriples(a.first, b.first); 
}
void InvertedIndex::MergeRuns(const string& output_file) {
  // FIXME: This certainly needs to be fixed.
  int read_size = 3;

  FILE* output = fopen(output_file.c_str(), "w");
  vector<FILE*> runs(number_of_runs_);
  // This pairs a triple to a run, so we know when all the triples have been
  // read from a run's block.
  vector< pair<TermDocumentFrequency, int> > triples;
  // Counts how many triples have been read from a run, and haven't been
  // placed in the output.
  vector<int> triples_left(number_of_runs_, 0);
  for (int i = 0; i < runs.size(); ++i) {
    stringstream stream;
    stream << i;
    string file_name;
    stream >> file_name;
    file_name = "run" + file_name;
    runs[i] = fopen(file_name.c_str(), "r");
  }
  int temp_term, temp_frequency, temp_document;
  // Read the first batch
  for (int i = 0; i < runs.size(); ++i) {
    for (int j = 0; j < read_size; ++j) {
      if (fscanf(runs[i], "%d %d %d", &temp_term, &temp_document,
      &temp_frequency) <= 0) break;
      TermDocumentFrequency temp_triple(temp_term, temp_document,
      temp_frequency);
      pair<TermDocumentFrequency, int> temp_pair(temp_triple, i);
      triples_left[i]++;
      triples.push_back(temp_pair);
    }
  }
  make_heap(triples.begin(), triples.end(), ComparePairTripleRun);
  while (!triples.empty()) {
    int run_number = triples[0].second;
    // Output.
    fprintf(output, "%d %d %d\n", triples[0].first.term(),
    triples[0].first.document(), triples[0].first.frequency());
    printf("%d %d %d\n", triples[0].first.term(),
    triples[0].first.document(), triples[0].first.frequency());
    
    // Remove triple.
    pop_heap(triples.begin(), triples.end(), ComparePairTripleRun);
    triples.pop_back();

    triples_left[run_number]--;
    if (triples_left[run_number] == 0) {
      // FIXME: Maybe make this a function somehow.
      for (int i = 0; i < read_size; ++i) {
        if (fscanf(runs[run_number], "%d %d %d", &temp_term, &temp_document,
        &temp_frequency) <= 0) break;
        TermDocumentFrequency temp_triple(temp_term, temp_document,
        temp_frequency);
        pair<TermDocumentFrequency, int> temp_pair(temp_triple, run_number);
        triples_left[run_number]++;
        triples.push_back(temp_pair);
        push_heap(triples.begin(), triples.end(), ComparePairTripleRun);
      }
    } 
  }

  fclose(output);
  for (int i = 0; i < runs.size(); ++i) {
    fclose(runs[i]);
  }

}

void InvertedIndex::RemoveTemporaryRuns() {
  system("rm run*");
}

void InvertedIndex::MakeIndex(const string& temporary_file,
const string& output) {
  FILE* temp_file = fopen(temporary_file.c_str(), "r");
  FILE* output_file = fopen(output.c_str(), "w");
  int current_term = 1;
  int number_of_documents = 0;
  char temp_string[100];
  int term, frequency;
  list< pair<string, int> > document_frequency;
  // FIXME: This has to be done better.
  while ( fscanf(temp_file, "%d %s %d", &term, temp_string, &frequency) == 3) {
    if (term != current_term) {
      fprintf(output_file, "%d %d ", current_term, number_of_documents); 
      std::list< pair<string, int> >::iterator it;
      for (it = document_frequency.begin(); it != document_frequency.end();
      ++it) {
        // This is printing an extra space in the end of the line.
        fprintf(output_file, "%s %d ", (*it).first.c_str(), (*it).second);
      }
      fprintf(output_file, "\n");
      document_frequency.clear();
      current_term = term;
      number_of_documents = 0;
    }
    string document(temp_string);
    pair<string, int> temp_document_frequency(document, frequency);
    document_frequency.push_back(temp_document_frequency);
    number_of_documents++;
  }

  // Print the last one.
  fprintf(output_file, "%d %d ", current_term, number_of_documents); 
  std::list< pair<string, int> >::iterator it;
  for (it = document_frequency.begin(); it != document_frequency.end();
  ++it) {
    // This is printing an extra space in the end of the line.
    fprintf(output_file, "%s %d ", (*it).first.c_str(), (*it).second);
  }
  fprintf(output_file, "\n");
  document_frequency.clear();

  fclose(temp_file);
  fclose(output_file);
}

void InvertedIndex::WriteVocabulary(const string& file_name) {
  FILE* file = fopen(file_name.c_str(), "w");
  unordered_map<string, int>::iterator it;
  for (it = vocabulary_.begin(); it != vocabulary_.end(); ++it) {
    fprintf(file, "%s %d\n", it->first.c_str(), it->second);
  }
  fclose(file);
}

void InvertedIndex::ParseIntoIndexTerms(const string& document,
TermFrequencyMap* index_terms) {
  list<string> terms = Util::SeparateIntoWords(document);
  list<string>::iterator it;
  for (it = terms.begin(); it != terms.end(); ++it) {
    if (vocabulary_.count(*it) == 0) {
     // Only allow for MAXIMUM_STRING_SIZE characters max for each word.
     vocabulary_[(*it).substr(0,MAXIMUM_STRING_SIZE)] = vocabulary_.size();
    }
    (*index_terms)[(*it).substr(0,MAXIMUM_STRING_SIZE)]++;
  }
}

void InvertedIndex::ProcessIndexTerm(const string& index_term,
const int document, const int term_frequency) {
  TermDocumentFrequency temp(vocabulary_[index_term], document, term_frequency);
  triples_.push_back(temp);
}

void InvertedIndex::PrintTriples() {
  unordered_map<string, int>::iterator it;
  for (it = vocabulary_.begin(); it != vocabulary_.end(); ++it) {
    cout<<it->first<<" "<<it->second<<endl;
  }
 /* triples_.sort(TermDocumentFrequency::CompareTriples);
  list<TermDocumentFrequency>::iterator it;
  for (it = triples_.begin(); it != triples_.end(); ++it) {
    std::cout<< (*it).term() << " " << (*it).document() << " " <<
    (*it).frequency() << std::endl;
  }*/
}

//FIXME(make this be encoded, and maybe use fwrite and etc)
void InvertedIndex::WriteRunOnDisk(const int run_number) {
  stringstream stream;
  stream << run_number;
  string file_name;
  stream >> file_name;
  file_name = "run" + file_name;
  triples_.sort(TermDocumentFrequency::CompareTriples);
  FILE *output = fopen(file_name.c_str(), "w");
  list<TermDocumentFrequency>::iterator it;
  for (it = triples_.begin(); it != triples_.end(); ++it) {
    fprintf(output, "%d %d %d\n", (*it).term(), (*it).document(),
    (*it).frequency());
  }
  triples_.clear();
  fclose(output);
  
  //FIXME
  file_name = "document_url";
  this->AppendDocumentUrlFile(file_name);
  document_url_.clear();
}

void InvertedIndex::AppendDocumentUrlFile(const string& file_name) {
  FILE* file = fopen(file_name.c_str(), "a");
  unordered_map<int, string>::iterator it;
  for (it = document_url_.begin(); it != document_url_.end(); ++it) {
    fprintf(file, "%d %s\n", it->first, it->second.c_str());
  }
  fclose(file);
}
