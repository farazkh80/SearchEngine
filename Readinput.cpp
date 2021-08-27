#include "inc/Readinput.h"

using namespace std;

// Function for reading line sizes from document
// and finding max length
int read_sizes(int* linecounter, int* maxlength, char* docfile)
{
	ifstream myfile;
	myfile.open(docfile);
	if (!myfile.is_open())
	{
		cout << "Error opening file" << endl;
		return -1;
	}
	char* line = NULL;
	string str_line;
	int currlength;

	// find max line length
	while (!myfile.eof())
	{
		getline(myfile, str_line);
		line = &str_line[0];
		currlength = str_line.length();


		if (*maxlength < currlength)
			*maxlength = currlength;
		(*linecounter)++;
		line = NULL;
	}
	myfile.close();
	if (*linecounter == 0 || *maxlength < 6)
	{
		cout << "Document is too empty and does not meet requirements" << endl;
		return -1;
	}
	return 1;
}

// Function for splitting input lines to tokens(words) and
// inserting them in the Trie
void split(char* temp, int id, Trienode* trie, Mymap* mymap)
{
	char* token;
	token = strtok(temp, " \t");
	int i = 0;

	// insert tokens with their corresponding document id in the trie
	// untill no more is left
	while (token != NULL)
	{
		i++;
		trie->insert(token, id);
		token = strtok(NULL, " \t");
	}
	mymap->setlength(id, i);
	free(token);
}

// Function for reading documents from dataset and
// inserting documents in the map and their tokens into trie
int read_input(Mymap* mymap, Trienode* trie, char* docfile)
{
	ifstream myfile;
	myfile.open(docfile);
	char* line = NULL;
	string str_line;

	int currlength;
	char* temp = (char*)malloc(mymap->getbuffersize() * sizeof(char));

	// traverse through the map and
	for (int i = 0; i < mymap->getsize(); i++)
	{
		getline(myfile, str_line);
		if(!myfile.eof()){
			line = &str_line[0];
			if (mymap->insert(line, i) == -1)
			{
				cout << "Document does not meet the requirements" << endl;
				myfile.close();
				free(temp);
				return -1;
			}

			// after insertation get document from id
			strcpy(temp, mymap->getDocument(i));

			// split it into tokens for trie insertation
			split(temp, i, trie, mymap);
			line = NULL;

		}
	}
	myfile.close();
	free(temp);
	return 1;
}