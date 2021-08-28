#include "inc/Searchengine.h"
#include <algorithm>

using namespace std;

// function for different search input processing
// different search types
// /search => does a full search over documents and returns all matches for a single <keyword>
// /df => searches the number of total occurrences of a single <keyword>
// /tf => searches the number of occurrences of a single <keyword> in a single <document>
int inputmanager(char* mode, char* words, Trienode* trie, Mymap* map, int k)
{

	// compare the mode with different search options
	if (!strcmp(mode, "/search"))
		search(words, trie, map, k);
	else if (!strcmp(mode, "/df"))
		df(trie, words);
	else if (!strcmp(mode, "/tf"))
	{
		if (tf(words, trie) == -1)
			return -1;
	}
	else if (!strcmp(mode, "/exit"))
	{
		cout << "Exiting..." << endl;
		return 2;
	}
	else
		return -1;

	return 1;
}

// main function for argument processing and input reading
// supported file execution format:
// searchEngine -d <datafile> -k <max_matches> -m <mode> -w <keyword>
// the datafile is a txt document containing different documents with an added document int id and a tab to their start
// supported searching modes: -m /search -w <keyword1,keyword2,...>
//                            -m /df -w <keyword>
//                            -m /tf -w <keyword> -i <document-id> (not fully supported yet) 
int main(int argc, char** argv)
{
	// Process execution args
	if (argc != 9 || strcmp(argv[1], "-d") || strcmp(argv[3], "-k") || strcmp(argv[5], "-m") || strcmp(argv[7], "-w"))
	{
		cout << "wrong arguments" << endl;
		return -1;
	}

	int linecounter = 0;
	int maxlength = -1;
	int k = atoi(argv[4]);

	// document length reading and max length setting
	if (read_sizes(&linecounter, &maxlength, argv[2]) == -1)
		return -1;

	Mymap* mymap = new Mymap(linecounter, maxlength);
	Trienode* trie = new Trienode();


	// setup the database by reading documents and insert them into map and trie
	if (read_input(mymap, trie, argv[2]) == -1)
	{
		delete(mymap);
		return -1;
	}

	char* input = NULL;
	string str_input;
	size_t inputlength = 0;


	// process words to be searched
	string words = argv[8];
	replace(words.begin(), words.end(), ',', ' ');

	// call input manager for handling the actual searching operation
	inputmanager(argv[6], &words[0], trie, mymap, k);

	delete(mymap);
	delete(trie);
	return 1;
}