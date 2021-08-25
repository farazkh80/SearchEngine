#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Scorelist.h"
#ifndef LISTNODE_H
#define LISTNODE_H
class listnode
{
    listnode *next; //next list item
    int id;         //document id
    int times;      //how many times to the specific doc
    public:
        listnode(int did):id(did),times(0){next=NULL;}
        ~listnode();
        // Getter function for incrementing times of occurance of a word in
        // the document with id did
        void add(int did);
        // Getter function for the times of occurance of a word in
        // the document with id did
        int search(int did);
        // Function for returining the number of documents the word
        // has been found in
        int volume();
        // Function for inserting the scorelist of each documents
        // for search ranking
        void passdocuments(Scorelist* scorelist);
};
#endif