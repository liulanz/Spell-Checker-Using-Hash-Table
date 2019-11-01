// Liulan Zheng
// CSCI 335 Homework 3

#include "quadratic_probing.h"

#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string LowerCase(const string & original_word)
{
	string word = original_word;
	for(unsigned int i = 0; i < word.length(); i++)
	{
		word[i] = tolower(word[i]);
	}
	return word;
}
string RemoveSymbol(const string & original_word, string & symbol)
{
	string word = original_word;
	for(unsigned int i =0; i < original_word.length(); i++)
	{
		if(original_word[i] == '\'' || original_word[i] == '.' || original_word[i] == ',')
		{
			symbol = original_word.substr(i);
			word = original_word.substr(0, i);
			return word;
		}
	}
	return word;
}

void SpellCheck(HashTable<string> & hash_table, const string & document_filename, const string & dictionary_filename)
{
	ifstream wordFile;
	wordFile.open(dictionary_filename);
	string words;
   	while(getline(wordFile, words))
	{
		hash_table.Insert(words);
	}	
	wordFile.close();
	
	ifstream documentFile;
	bool case_a = false;
	bool case_b = false;
	bool case_c = false;
	bool correction = false;
	documentFile.open(document_filename);
	string word, new_word, original_word,symbol, document;
   	while(documentFile >> original_word)
	{
		word = RemoveSymbol(original_word, symbol);
		word = LowerCase(original_word);
		if(hash_table.Contains(word))
			word = original_word;
		else
		{
			case_a = false;
			case_b = false;
			case_c = false;
			//case a 
			for(unsigned int i = 97; i < 123; i++) 
			{
				for(unsigned int j = 0; j < word.length()+1; j++)
				{
					if(j == word.length())
						new_word = word + (char)i;
					else
						new_word = word.substr(0, j)+ (char)i+ word.substr(j);
					
					if(hash_table.Contains(new_word))
					{
						case_a = true;
						break;
					}
					
				}
				if(case_a == true)
					break;
			}
			
			if(case_a == false)
			{
				// case c
				for(unsigned int w = 0; w < word.length()-1; w++)
				{
					if(w < word.length()-2)
						new_word = word.substr(0,w) + word[w+1] + word[w] + word.substr(w+2);
					else
						new_word = word.substr(0,w) + word[w+1] + word[w];
					if(hash_table.Contains(new_word))
					{
						case_c = true;
						break;
					}
				}
			}
			if(case_c == false && case_a == false)
			{ // case b
				for(unsigned int m = 0; m < word.length(); m++)
				{
					if(m == 0)
						new_word = word.substr(1);
					else if (m == word.length()-1)
						new_word = word.substr(0, word.length()-1);
					else
						new_word = word.substr(0, m) + word.substr(m + 1);
					if(hash_table.Contains(new_word))
					{
						case_b = true;
						break;
					}
					
				}
			}
			if(case_a == true)
				cout << word << " -> " << new_word << " (case a) " << endl;
			else if(case_b == true)
				cout << word << " -> " << new_word << " (case b) " << endl;
			else if(case_c == true)
				cout << word << " -> " << new_word << " (case c) " << endl;
			else
				cout << word << " -> CANNOT BE CORRECTED." <<endl;	
			if(case_a == true || case_b == true || case_c == true)
				correction = true;
			
			
		}
		if(correction == 1)
		{
			if(symbol != "")
				new_word = new_word + symbol;
			document = document + " " + new_word;
			
		}
		else
		{
			word = original_word;
			document = document + " " + word;
		}
		correction = false;
			
	}	
	cout << document << endl;
	documentFile.close();
	
	
}

// Sample main for program spell_check
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }
  
  const string document_filename(argv[1]);
  const string dictionary_filename(argv[2]);
  
  cout << "Input document filename is " << document_filename << endl;
  cout << "Input dictionary filename is " << dictionary_filename << endl;
  HashTable<string> quadratic_probing_table;
  SpellCheck(quadratic_probing_table, document_filename, dictionary_filename);


  return 0;
}
