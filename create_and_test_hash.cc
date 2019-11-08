//Liulan Zheng
//CSCI 335 Homework 3

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
 * @words_filename: a file that contains a list of words, and it will be stored into a hash table
 * @query_filename: a file which contains words that wants to be checked if they can be found in the hash_table
 * @collision: total number of times when a element is inserted to hash_table based on the hash function, and the spot is being taken by another element
 * @load_factor: current size of table / total capacity of table
 * This function stores elements from words_filename, and prints out some statistics for the table after insertion
	Then look for words in query_filename, and check if they can be found in the table, and prints number of probes, 
	which is 1 + total number of collision.
 */
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
	cout << "TestFunctionForHashTables..." << endl;
	cout << "Words filename: " << words_filename << endl;
	cout << "Query filename: " << query_filename << endl;
	hash_table.MakeEmpty();  //Empty the hash table, so it's ready to insert a new set of data

	ifstream wordFile;
	string word;
	
	// Reads words file in to hash_table (using either linear probing, quadratic probing, or double hashing
	wordFile.open(words_filename);
	while(getline(wordFile, word))
	{
		if(word != "")
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
	
	cout << "Beginning searching for query words: " << endl;
	
	bool found;
	string result;
	ifstream queryFile;
	
	// Reads query file, which contains couple words that want to be checked if it's in the hash_table
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
int main(int argc, char **argv) {
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
