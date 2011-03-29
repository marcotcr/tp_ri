// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com

// This is a test program.

#include <cstdlib>
#include <iostream>
#include <htmlcxx/html/ParserDom.h>
#include "./util.h"
#include "./CollectionReader.h"
#include "./inverted_index.h"

using namespace RICPNS;
using namespace htmlcxx;

int main(int argc, char** argv) {

 /* std::string input_directory("./");
  std::string index_filename("indexToCompressedColection.txt");
  CollectionReader * reader = new CollectionReader(input_directory,
                              index_filename);
  Document doc;
  doc.clear();
  int i = 0;
  while(reader->getNextDocument(doc))  {
    if((i%1000) == 1) {
      printf("URL: %s\n", doc.getURL().c_str());
      std::string html = doc.getText();
      HTML::ParserDom parser;
      tree<HTML::Node> dom = parser.parseTree(html);
      tree<HTML::Node>::iterator it = dom.begin();
      tree<HTML::Node>::iterator end = dom.end();
      //cout<< " Vo imprimir os links da pagina "<<endl;
      for ( ; it != end; ++it) {

       // This is for the links
       //if (it->tagName() == "a") {
       //  it->parseAttributes();
       //  std::map<string,string> attributes = it->attributes();;
       //  string oi = "href";
       //  cout << attributes[oi] <<endl;
       //}

        // Prints each word of the page.
        if ((!it->isTag()) && (!it->isComment())) {
          if (!Util::IsHTMLComment(it->text())) {
            std::list<std::string> words = Util::SeparateIntoWords(it->text());
            for (std::list<std::string>::iterator it2 = words.begin();
                 it2 != words.end(); ++it2)
              printf("word: %s\n", it2->c_str()); 
          }
        }
      }
    }
    doc.clear();
    ++i;
  }
  printf("Total: %d\n", i);
  delete reader;
  return EXIT_SUCCESS;*/
  std::list<std::string> document_list;
  document_list.push_back("Pease porridge hot, pease porridge cold,");
  document_list.push_back("Pease porridge in the pot,");
  document_list.push_back("Nine days old.");
  document_list.push_back("Some like it hot, some like it cold,");
  document_list.push_back("Some like it in the pot,");
  document_list.push_back("Nine days old.");
  std::string output_file = "output";
  InvertedIndex oi(output_file, document_list);
  oi.PrintTriples();

}

