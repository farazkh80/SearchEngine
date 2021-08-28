/*
File of trie data structure for storing the tokens of documents.
For each token the Trienode containing the last letter will point
to a Listnode containing the ids of the documents they have been
found at
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Listnode.h"
#include "Scorelist.h"
#ifndef TRIENODE_H
#define TRIENODE_H

using namespace std;
class Trienode
{
    Trienode* sibling;
    Trienode* child;
    listnode* list;
    char value;
    public:
        Trienode();
        ~Trienode();
        void insert(char* token,int id);
        // function for searching a word in Trie and returning its 
        // frequency in the document specified by id
        int tfsearchword(int id,char* word,int curr);
        // function for searching a word in Trie and returning the number
        // of documents the word has been found in
        int dsearchword(char* word,int curr);
        // function for searching for all the words in Trie 
        // and returning the number of documents that the word
        // has been found in
        void dsearchall(char* buffer,int curr);
        //
        //
        void search(char* word,int curr,Scorelist* scorelist);
};

#endif