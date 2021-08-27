#include "inc/Searchengine.h"

using namespace std;

// function for different search input processing
// different search types
// /search => does a full search over documents and returns all matches for a single <keyword>
// /df => searches the number of total occurances of a single <keyword>
// /tf => searches the number of occurances of a single <keyword> in a single <document>
int inputmanager(char* input, Trienode* trie, Mymap* map, int k)
{
	char* token = strtok(input, " \t\n"); // get first token

	// compare the token with different search options
	if (!strcmp(token, "/search"))
		search(token, trie, map, k);
	else if (!strcmp(token, "/df"))
		df(trie);
	else if (!strcmp(token, "/tf"))
	{
		if (tf(token, trie) == -1)
			return -1;
	}
	else if (!strcmp(token, "/exit"))
	{
		cout << "Exiting..." << endl;
		token = NULL;
		free(token);
		return 2;
	}
	else
		return -1;

	token = NULL;
	free(token);
	return 1;
}

// main function for argument processing and input reading
// supported file execution format: /searchEngine -d <datafile> -k <max_matches>
// the datafile is a txt document containing different documents with an added 
// document int id and a tab to their start
// supported searching options: /search <keyword>
//                              /df <keyword>
//                              /tf <document_id> <keyword>
int main(int argc, char** argv)
{
	// execution args processing
	if (argc != 5 || strcmp(argv[1], "-d") || strcmp(argv[3], "-k"))
	{
		cout << "wrong arguments" << endl;
		return -1;
	}

	cout << "Please Wait" << endl;
	int linecounter = 0;
	int maxlength = -1;
	int k = atoi(argv[4]);

	// document length reading and max length setting
	if (read_sizes(&linecounter, &maxlength, argv[2]) == -1)
		return -1;
	Mymap* mymap = new Mymap(linecounter, maxlength);
	Trienode* trie = new Trienode();


	// read documents and insert them into map and trie
	if (read_input(mymap, trie, argv[2]) == -1)
	{
		delete(mymap);
		return -1;
	}

	cout << "Database Ready" << endl;
	char* input = NULL;
	string str_input;
	size_t inputlength = 0;

	// search methods processing from istream
	while (1)
	{
		getline(std::cin, str_input);
		input = &str_input[0];

		int ret = inputmanager(input, trie, mymap, k);
		if (ret == -1)
			cout << "Wrong input" << endl;
		else if (ret == 2)
		{
			break;
		}
		inputlength = 0;

	}
	delete(mymap);
	delete(trie);
	return 1;
}