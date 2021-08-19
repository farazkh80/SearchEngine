#include <iostream>
#include "Map.h"
#include "Trienode.h"
// function for reading line sizes from document
// and finding max length
int read_sizes(int *linecounter,int *maxlength,char* docfile);

// function for splitting input lines to words and
// inserting them in trie
int read_input(Mymap* mymap,Trienode *trie,char* docfile);