/*
File handling different search operations including
/search <keyword> => searches for the matching results of <keyword> in the doc
/df <keyword> => searches for the <keyword> num of occurrence in all docs
/tf <id> <keyword> => searches for the <keyword> num of occurrence in doc with id <id>
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Trienode.h"
#include "Scorelist.h"
#include "Maxheap.h"
#include "Map.h"
#include <cmath>

// /search function for searching occurrence of a specific word in all of the documents
// ex1: /search hello
// "hello": word to be searched for is hello
// returns: a ranked list of documents showing the exact location of word
// ex2: /search hello
// "hello,data": words to be searched for are hello and data
// returns: a ranked list of documents showing the exact location of words
void search(char* token, Trienode* trie, Mymap* map, int k);
// df function for searching frequency of a specific word in all of the documents
// ex1: /df hello
// "hello": word to be searched for
// ex2: /df
// ex1 will only return the frequency of given word,
// but ex2 will return the frequency of all the words
void df(Trienode* trie, char* word);
// tf function for searching frequency of a specific word in a specific document
// ex: /tf 2 hello
// "2": document id and "hello": word to be searched for
int tf(char* token, Trienode* trie);