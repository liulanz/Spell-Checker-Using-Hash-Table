// Liulan Zheng
// CSCI 335
/* This program reads a dictionary file and a document file
	Base on the dictionary file, make spelling check on document file
	Makes possible spelling corrections 
	At the end print out all the corrections that was made and the revised document 
*/
#include "quadratic_probing.h"

#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/**
 * @original_word: word may have capitalized letters
 * @word: all letters of word are lower case
 * This function turns every letter of original_word to lowercase 
 */
string LowerCase(const string & original_word)
{
	string word = original_word;
	for(unsigned int i = 0; i < word.length(); i++)
	{
		word[i] = tolower(word[i]);
	}
	return word;
}

/**
 * @original_word: word may have punctuation at then end
 * @punctuation: stores "", "'", ".", or ","
 * @word: stores only letter part of original_word (no punctuation)
 * This function separates word and punctuation in original_word
 */
string RemovePunctuation(const string & original_word, string & punctuation)
{
	string word = original_word;
	for(unsigned int i =0; i < original_word.length(); i++)
	{
		if(original_word[i] == '\'' || original_word[i] == '.' || original_word[i] == ',')
		{
			punctuation = original_word.substr(i);
			word = original_word.substr(0, i);
			return word;
		}
	}
	return word;
}

/** 
 * @hash_table: an object of HashTable, which uses quadratic probing method to store items in hash table 
 * @document_filename: file name of document that needs to be check
 * @dictionary_filename: file name of a dictionary (a small portion of a real dictionary)
 * @case_a: true if a word can be corrected (found in hash table) by adding a new letter to word, else false
 * @case_b: true if a word can be corrected (found in hash table) by removing a letter, else false
 * @case_c: true if a word can be corrected (found in hash table) by swapping adjacent letters, else false
 * @document: stores the contents in document file after corrections were made
 * This function stores words from dictionary file into hash_table using quadratic probing
  	Then reads a document file, and check for misspelled words, which are words that can't be found in hash_table
	Lastly, it would make corrections based on case a, case b, case c.
	Finally, it will print out the document after correcting the spelling
 */
void SpellCheck(HashTable<string> & hash_table, const string & document_filename, const string & dictionary_filename)
{
	ifstream wordFile;
	string words, word, new_word, original_word, punctuation, document;
	
	// Reads dictionary file and store words into hash_table using quadratic probing
	wordFile.open(dictionary_filename);
   	while(getline(wordFile, words))
	{
		hash_table.Insert(words);
	}	
	wordFile.close();
	
	bool case_a, case_b, case_c;
	bool correction = false;
	
	// Reads document file
	ifstream documentFile;
	documentFile.open(document_filename);
   	while(documentFile >> original_word)
	{
		word = RemovePunctuation(original_word, punctuation); // Separates letters and punctuation
		word = LowerCase(original_word); // Turns all letters into lowercase
		if(!hash_table.Contains(word)) // if the word is spelled incorrectly (can't be found in hash table)
		{
			case_a = false;
			case_b = false;
			case_c = false;
			
			//case a: true if word can be corrected by adding one letter to any possible spot
			for(unsigned int i = 97; i < 123; i++) // checking letters a to z
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
			
			// case c : true if word can be corrected by swapping adjacent letters
			if(case_a == false)
			{
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
			
			// case b: true if word can be corrected by removing a letter
			if(case_c == false && case_a == false)
			{ 
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
			
			// Prints the corresponding correction that was made
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
		
		// Putting together the words into a new document after spell check
		if(correction == 1)
		{
			new_word = new_word + punctuation;
			document = document + " " + new_word;
		}
		else
		{
			word = original_word;
			document = document + " " + word;
		}
		correction = false;
			
	}	
	document = document.substr(1); // remove the empty space at the beginning
	cout << document << endl;  // prints the whole document
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
