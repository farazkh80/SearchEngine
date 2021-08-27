#include "inc/Search.h"

using namespace std;

const float k1 = 1.2;
const float b = 0.75;

void print_underline(int cols, int* lineflag, int* ucounter, int underline[2][100]) {

	char* output_line = (char*)malloc((cols + 1) * sizeof(char));

	for (int j = 0; j < cols; j++) {
		output_line[j] = ' ';
	}

	*lineflag = 0;
	output_line[cols] = '\0';

	// show found matches
	for (int j = 0; j < *ucounter;j++) {
		for (int v = underline[0][j]; v < (underline[0][j] + underline[1][j]);v++) {
			output_line[v] = '^';
		}
	}

	*ucounter = 0;
	cout << output_line << "\n";
	free(output_line);


}

void search(char* token, Trienode* trie, Mymap* map, int k)
{
	char warray[10][256];
	double IDF[10];
	token = strtok(token, " \t\n");
	Scorelist* scorelist = new Scorelist();
	int i;
	int cols = 120;

	// process the words(tokens) to be searched by generating a score
	// and searching them in the Trie
	for (i = 0;i < 10;i++)
	{
		if (token == NULL)
			break;
		strcpy(warray[i], token);
		IDF[i] = log10(((double)map->getsize() - (double)trie->dsearchword(warray[i], 0) + 0.5) / ((double)trie->dsearchword(warray[i], 0) + 0.5));
		trie->search(warray[i], 0, scorelist);
		token = strtok(NULL, " \t\n");
	}

	// get average length of all documents
	double avgdl = 0;
	for (int m = 0;m < map->getsize();m++)
		avgdl += (double)map->getlength(m);
	avgdl /= (double)map->getsize();

	double score = 0;
	Scorelist* templist = scorelist;
	Maxheap* heap = new Maxheap(k);
	int ceil = 0;

	// calculate the score of all documents based on the number of
	// searched word(token) occurances
	while (templist != NULL)
	{
		for (int l = 0;l < i;l++)
			score += IDF[l] * ((double)trie->tfsearchword(templist->getid(), warray[l], 0) * (k1 + 1.0)) / ((double)trie->tfsearchword(templist->getid(), warray[l], 0) + k1 * (1.0 - b + b * (double)map->getlength(templist->getid()) / (double)avgdl));
		heap->insert(score, templist->getid());
		score = 0;
		templist = templist->getnext();
		ceil++;
	}
	if (ceil > k)
		ceil = k;


	// output search results
	for (int l = 0; l < ceil;l++) {
		int id = heap->getid();
		if (id == -1)
			break;

		// show the score for each document
		double score = (double)heap->remove();

		cout << '(' << id;
		int x = 10, f = 1;
		while (id / x != 0) {
			x *= 10;
			f++;
		}

		while (5 - f >= 0) {

			cout << " ";
			f++;
		}
		printf(")[%10.6f]", score);

		// get the document as a line and process tokens
		char* line = (char*)malloc(map->getbuffersize() * sizeof(char));
		strcpy(line, map->getDocument(id));

		char* temp;
		temp = strtok(line, " \t\n");

		// line printing variables
		int currlength = 0;
		int counter = 0;
		int newline = 1;
		int lineflag = 0;
		int underline[2][100];
		int ucounter = 0;
		bool end = false;

		// while temp words of document is not the end
		while (temp != NULL) {

			// start newline with formating spaces
			if (newline) {
				currlength += 20;
				if (counter != 0) {
					for (int co = 0; co < 20; co++)
						cout << " ";
				}
				newline = 0;
			}

			// compare the current temp token to all of the searched
			// words and adjust underline array bases on matches
			for (int n = 0;n < i;n++) {

				// if current token matches one of the searched words
				if (!strcmp(warray[n], temp)) {
					// setup the underlining start and end for the matched word
					if ((currlength + strlen(temp) + 1) <= cols) {
						underline[0][ucounter] = currlength;
						underline[1][ucounter] = strlen(temp);
						ucounter++;
						lineflag = 1;
					}
					break;

				}
			}

			currlength += strlen(temp) + 1;
			if ((currlength - 1) >= cols) {
				currlength = 0;
				newline = 1;
				cout << endl;

				if (lineflag) {
					print_underline(cols, &lineflag, &ucounter, underline);
				}
				continue;
			}

			cout << temp << " ";
			temp = strtok(NULL, " \t\n");
			counter++;
		}
		cout << "\n";

		// to capture last lines flag
		if (lineflag) {
			print_underline(cols, &lineflag, &ucounter, underline);
		}

		free(line);
		free(temp);
		cout << "[CEL]" << endl;
	}

	delete(heap);
	delete(scorelist);
	cout << endl;
}

// df function for searching frequency of a specific word in all of the documents
// ex1: /df hello
// "hello": word to be searched for
// ex2: /df
// ex1 will only return the frequency of given word,
// but ex2 will return the frequency of all the words
void df(Trienode* trie, char* word)
{
	char* token2;

	// get the word and if not null search
	token2 = strtok(word, " \t\n");
	if (token2 != NULL)
		cout << token2 << " " << trie->dsearchword(token2, 0) << endl;

	// if valid word return the frequency for all of the words
	else
	{
		char* buffer = (char*)malloc(256 * sizeof(char));
		memset(buffer, '\0', 256);
		trie->dsearchall(buffer, 0);
		free(buffer);
	}
	token2 = NULL;
	free(token2);
}

// tf function for searching frequency of a specific word in a specific document
// ex: /tf 2 hello
// "2": document id and "hello": word to be searched for
int tf(char* token, Trienode* trie)
{
	char* token2;
	token2 = strtok(token, " \t\n");
	// if token is null return
	if (token2 == NULL)
	{
		free(token2);
		return -1;
	}
	// check that token is a digit(document id)
	for (int l = 0;l < strlen(token2);l++)
	{
		if (!isdigit(token2[l]))
		{
			token2 = NULL;
			free(token2);
			return -1;
		}
	}

	// convert to int
	int id = atoi(token2);
	// get the word to be searched
	token2 = strtok(NULL, " \t\n");
	if (token2 == NULL)
	{
		free(token2);
		return -1;
	}

	// output the document id and the frequnecy of the word
	cout << id << " " << token2 << " " << trie->tfsearchword(id, token2, 0) << endl;
}