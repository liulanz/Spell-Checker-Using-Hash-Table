//Liulan Zheng
//CSCI 335 Homework 3

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_probing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  
  //..Insert your own code
  ifstream wordFile;
	wordFile.open(words_filename);
	string word;
	
   	while(getline(wordFile, word))
	{
		hash_table.Insert(word);
	}	
	
	wordFile.close();
	int collision = hash_table.GetCollision();
  cout << "Statistics for this Hash Table: " << endl;
  cout << "Elements in table: " << hash_table.GetCurrentSize() << endl;
  cout << "Size of hash table: " << hash_table.GetTableSize() << endl;
  double load_factor = (double)hash_table.GetCurrentSize() / hash_table.GetTableSize();
  cout << "Load factor: " << load_factor << endl;
  cout << "Number of Collisions: " << collision << endl;
  cout << "Avg. number of collisions: " << (double)collision / hash_table.GetCurrentSize() << endl;
  cout << endl;
  cout << "Beginning seaching for query words: " << endl;
  ifstream queryFile;
  bool found;
  string result;
  queryFile.open(query_filename);
   while(getline(queryFile, word))
	{
		found = hash_table.Contains(word);
		if(found == true)
			result = "Found";
		else
			result = "Not Found";
		cout << word << ": " << result << " in " << hash_table.GetProbe() << " probes " << endl;
		
	}
	queryFile.close();

}

// Sample main for program create_and_test_hash
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
     TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } else if (param_flag == "quadratic") {
	HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
	HashTableDouble<string> double_probing_table;
	TestFunctionForHashTable(double_probing_table, words_filename, query_filename);    
  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
