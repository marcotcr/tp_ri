class IndexConstructor {
 public:
  IndexConstructor();
  bool ReadDocument(std::string& document);
  // cleans the 
  void PrintToFile(std::string& temporary_file_name);
 private:
  std::map<string, int> dictionary_;
  // This refers to the term frequency within a document.
  std::map<int, int> term_frequency_; 
  
  std::string output_;
}
