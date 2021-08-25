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
int inputmanager(char* input,Trienode* trie,Mymap* map,int k);

// main function for argument processing and input reading
int main(int argc, char **argv);