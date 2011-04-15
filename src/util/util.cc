// Copyright 2011 Marco Ribeiro
// Author: Marco Ribeiro
// E-mail: marcotcr@gmail.com
// This is a compendium of useful functions.

#include "util.h"
#include <limits.h>

list<string> Util::SeparateIntoWords(const string& text) {
  char temp_string[text.size()];
  strcpy(temp_string, text.c_str());
  char* temp_pointer = strtok(temp_string, SEPARATORS);
  list<string> output;
  int i = 0;
  while (temp_pointer) {
    //printf("WORD:%s\n",temp_pointer);
    string temp(temp_pointer);
    output.push_back(temp);
    temp_pointer = strtok(NULL, SEPARATORS);
    ++i;
  }
  return output;
}

bool Util::IsHTMLComment(const string& text) {
  string comment = "<!--";
  if (text.find(comment) != string::npos)
    return true;
  else
    return false;
}

void Util::StringToLowerCase(string *text) {
  for (int i = 0; i < (*text).length(); ++i) {
    (*text)[i] = tolower((*text)[i]);
  }
}

string Util::ParseHTMLdocument(const string& document) {
  string output;
  string temp = document;
  Util::StringToLowerCase(&temp);
  // This removes non html stuff.
  if (temp.find("content-type: text") == string::npos) {
    return output;
  }
  bool is_UTF8 = HTML::detect_utf8(temp.c_str(), temp.length());
  HTML::ParserDom parser;
  CharsetConverter converter("ISO-8859-1","ASCII//TRANSLIT");
  string temporary = Util::DecodeEntities(temp);
  if (!is_UTF8) {
    temporary = converter.convert(temporary);
  }
  else {
    CharsetConverter converter2("UTF-8", "ASCII//TRANSLIT");
    temporary = converter2.convert(temporary);
  }
  tree<HTML::Node> dom = parser.parseTree(temporary);
  tree<HTML::Node>::iterator it = dom.begin();
  // Ignore the html header.
  ++it;
  ++it;
  for (; it != dom.end(); ++it) {
    // If this is a script tag, next it is going to be the script content, so
    // skip it.
    if (it->isTag() && it->tagName() == "script") {
      ++it;
      if (it == dom.end()) break;
      continue;
    }
    if ((!it->isTag()) &&
    (!it->isComment()) &&
    (!Util::IsHTMLComment(it->text())))  {
      output.append(" ");
      output.append(it->text());
     // cout<<"IT: ";
     // cout<<it->text()<<endl;
    }
  }
  return output;
  
}


static struct {
	const char *str;
	char chr;
} entities[] = {
	/* 00 */
	{ "quot", 34 },
	{ "amp", 38 },
	{ "lt", 60 },
	{ "gt", 62 },
	{ "nbsp", ' ' },
	{ "iexcl", 161 },
	{ "cent", 162 },
	{ "pound", 163 },
	{ "curren", 164 },
	{ "yen", 165 },
	/* 10 */
	{ "brvbar", 166 },
	{ "sect", 167 },
	{ "uml", 168 },
	{ "copy", 169 },
	{ "ordf", 170 },
	{ "laquo", 171 },
	{ "not", 172 },
	{ "shy", 173 },
	{ "reg", 174 },
	{ "macr", 175 },
	/* 20 */
	{ "deg", 176 },
	{ "plusmn", 177 },
	{ "sup2", 178 },
	{ "sup3", 179 },
	{ "acute", 180 },
	{ "micro", 181 },
	{ "para", 182 },
	{ "middot", 183 },
	{ "cedil", 184 },
	{ "sup1", 185 },
	/* 30 */
	{ "ordm", 186 },
	{ "raquo", 187 },
	{ "frac14", 188 },
	{ "frac12", 189 },
	{ "frac34", 190 },
	{ "iquest", 191 },
	{ "Agrave", 'a' },
	{ "Aacute", 'a' },
	{ "Acirc", 'a' },
	{ "Atilde", 'a' },
	/* 40 */
	{ "Auml", 'a' },
	{ "ring", 'a' },
	{ "AElig", 'a' },
	{ "Ccedil", 'c' },
	{ "Egrave", 'e' },
	{ "Eacute", 'e' },
	{ "Ecirc", 'e' },
	{ "Euml", 'e' },
	{ "Igrave", 'i' },
	{ "Iacute", 'i' },
	/* 50 */
	{ "Icirc", 'i' },
	{ "Iuml", 'i' },
	{ "ETH", 208 },
	{ "Ntilde", 'n' },
	{ "Ograve", 'o' },
	{ "Oacute", 'o' },
	{ "Ocirc", 'o' },
	{ "Otilde", 'o' },
	{ "Ouml", 'o' },
	{ "times", 215 },
	/* 60 */
	{ "Oslash", 'o' },
	{ "Ugrave", 'u' },
	{ "Uacute", 'u' },
	{ "Ucirc", 'u' },
	{ "Uuml", 'u' },
	{ "Yacute", 'y' },
	{ "THORN", 222 },
	{ "szlig", 223 },
	{ "agrave", 'a' },
	{ "aacute", 'a' },
	/* 70 */
	{ "acirc", 'a' },
	{ "atilde", 'a' },
	{ "auml", 'a' },
	{ "aring", 'a' },
	{ "aelig", 'a' },
	{ "ccedil", 'c' },
	{ "egrave", 'e' },
	{ "eacute", 'e' },
	{ "ecirc", 'e' },
	{ "euml", 'e' },
	/* 80 */
	{ "igrave", 'i' },
	{ "iacute", 'i' },
	{ "icirc", 'i' },
	{ "iuml", 'i' },
	{ "ieth", 'i' },
	{ "ntilde", 'n' },
	{ "ograve", 'o' },
	{ "oacute", 'o' },
	{ "ocirc", 'o' },
	{ "otilde", 'o' },
	/* 90 */
	{ "ouml", 'o' },
	{ "divide", 247 },
	{ "oslash", 'o' },
	{ "ugrave", 'u' },
	{ "uacute", 'u' },
	{ "ucirc", 'u' },
	{ "uuml", 'u' },
	{ "yacute", 'y' },
	{ "thorn", 254 },
	{ "yuml", 'y' },
	/* 100 */
	{ NULL, 0 },
};

string Util::DecodeEntities(const string &str)
		{
			unsigned int count = 0;
			const char *ptr = str.c_str();
			const char *end;

			string ret(str);
			string entity;

			ptr = strchr(ptr, '&');
			if (ptr == NULL) return ret;

			count += static_cast<unsigned int>(ptr - str.c_str());

//			printf("url_init: %s\n", str.c_str());
			while (*ptr)
			{
				if (*ptr == '&' && ((end = strchr(ptr, ';')) != NULL))
				{
					entity.assign(ptr + 1, end);
//					printf("Entity: %d %s\n", entity.length(), entity.c_str());
					if (!entity.empty() && entity[0] == '#')
					{
						entity.erase(0, 1);
						int chr = atoi(entity.c_str());
						if (chr > 0 && chr <= UCHAR_MAX)
						{
							ret[count++] = chr;
						}
						ptr = end + 1;
					}
					else
					{
						bool found = false;
						for (int i = 0; entities[i].str != NULL; i++)
						{
							if (entity == entities[i].str)
							{
								found = true;
								ret[count++] = entities[i].chr;
								ptr = end + 1;
								break;
							}
						}

						if (!found)
						{
							ret[count++] = *ptr++;
						}
					}
				}
				else
				{
					ret[count++] = *ptr++;
				}
			}

			ret.erase(count);

//			printf("url_end: %s\n", ret.c_str());
			return ret;
}

