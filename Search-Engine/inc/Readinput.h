/*
File for reading document sizes, document to map insertation
and token to trie insertion
*/
#include <iostream>
#include <fstream>
#include <string>
#include "Map.h"
#include "Trienode.h"
// Function for reading line sizes from document
// and finding max length
int read_sizes(int* linecounter, int* maxlength, char* docfile);

// Function for splitting input lines to tokens(words) and
// inserting them in the Trie
void split(char* temp, int id, Trienode* trie, Mymap* mymap);

// Function for splitting input lines to words and
// inserting them in trie
int read_input(Mymap* mymap, Trienode* trie, char* docfile);