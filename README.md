# Spell-Checker-Using-Hash-Table

This project has 2 parts:


PART 1:

  Storing strings into hash table with either linear probing method, quadratic method, or double hashing method.
  Then base on the hash table that was created we can compute number of element, total number of collisions, average collisions, 
  table size, and load factor.
  We can also check if certain strings can be found in the hash table. It will also prints out the number of probes.
  
  
PART 2:

  First, it will reads a dictionary file into a hash table using qudratic probing method.
  Then checks spelling errors in a document file, and makes corrections based on the hash table.
  At the end, it will prints a revised document after making spelling corrections
  
**********************************************************************************************************************
You can compile one program individually by just typing make <Program Name>, 
	
for example, "make create_and_test_hash"

By typing "make clean"

	You delete all .o files and executables.

To execute part 1:

	You will need a words file and a query words file as input files and create_and_test_hash.cc
	You will type "make create_and_test_hash"
	Then ./create_and_test_hash <words file name> <query words file name> <flag>
		where words file contains a list of words you want to store in a hash table,
		query file contains words that you want to check if they can be found on a hash table, 
		and flag is method of how a hash table can be implemented 
		(type "linear" for linear probing, "quadratic" for quadratic probing, and "double" for double hashing)
	For example, you will type "./create_and_test_hash words.txt query_words.txt quadratic"

To executables part 2:

	You will need a document file and a dictionary file as input files and spell_check.cc
	You will type "make spell_check"
	Then ./spell_check <document file> <dictionary file>
		where document file contains whatever document you want to perform a spell check
		and dictionary file contains words that you want to store in to a hash table and that hash table will be used as a dictionary
	For example, you will type "./spell_check document1.txt wordsEn.txt"
 ******************************************************************************************************************************
