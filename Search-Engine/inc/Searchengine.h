/*
Main file for reading args and handling different
search operations
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Readinput.h"
#include "Map.h"
#include "Trienode.h"
#include "Search.h"

// function for different search input processing
// different search types
// /search => does a full search over documents and returns all matches for a single <keyword>
// /df => searches the number of total occurrences of a single <keyword>
// /tf => searches the number of occurrences of a single <keyword> in a single <document>
int inputmanager(char* mode, char* words, Trienode* trie,Mymap* map,int k);

// main function for argument processing and input reading
// supported file execution format:
// searchEngine -d <datafile> -k <max_matches> -m <mode> -w <keyword>
// the datafile is a txt document containing different documents with an added document int id and a tab to their start
// supported searching modes: -m /search -w <keyword1,keyword2,...>
//                            -m /df -w <keyword>
//                            -m /tf -w <keyword> -i <document-id> (not fully supported yet) 
int main(int argc, char **argv);