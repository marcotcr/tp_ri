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
#include "./query_processor.h"

using namespace RICPNS;
using namespace htmlcxx;

int main(int argc, char** argv) {

  std::string input_directory("./data/");
  std::string index_filename("index.txt");
 /* CollectionReader * reader = new CollectionReader(input_directory,
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
  /*std::list<Document> document_list;
  Document teste;
  teste.setURL("url1");
  teste.setText("Pease porridge hot, pease porridge cold, oi");
  document_list.push_back(teste);
  teste.setURL("url2");
  teste.setText("Pease porridge in the pot,oi");
  document_list.push_back(teste);
  teste.setURL("url3");
  teste.setText("Nine days old.oi");
  document_list.push_back(teste);
  teste.setURL("url4");
  teste.setText("Some like it hot, some like it cold,oi");
  document_list.push_back(teste);
  teste.setURL("url5");
  teste.setText("Some like it in the pot,oi");
  document_list.push_back(teste);
  teste.setURL("url6");
  teste.setText("Nine days old.oi");
  document_list.push_back(teste);*/
  //FIXME
  system ("rm document_url");
  std::string output_file = "output";
  InvertedIndex oi(input_directory, index_filename);
  oi.AVAILABLE_MEMORY = atoi(argv[1]);
  string index_file = "index";
  string vocabulary_file = "vocabulary";
  string document_url_file =  "document_url";
  oi.Init(index_file, vocabulary_file, output_file,
  document_url_file);
  /*
  QueryProcessor ola;
  string query;
  ola.Init(output_file, index_file,vocabulary_file, document_url_file); 
  printf("Digite a consulta que você deseja buscar:\n");
  getline(cin, query);
  //query = "javascript";
  list<string> documents = ola.ProcessQuery(query);
  list<string>::iterator it;
  printf("Documentos com a palavra %s:\n", query.c_str());
  for (it = documents.begin(); it != documents.end(); ++it) {
    cout<< *it << endl;
    
  }*/
//  oi.PrintTriples();

}

