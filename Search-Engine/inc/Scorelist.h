/*
Scorelist data structure to be used for ranking the search results
*/
#include <iostream>
#include <cstdlib>

#ifndef SCORELIST_H
#define SCORELIST_H
class Scorelist
{
    int id;
    Scorelist* next;
    public:
        Scorelist(int did=-1):id(did){next=NULL;}
        ~Scorelist();
        // Function for creating a score list containing the ids of documents
        // containing a specific word
        void insert(int did);
        Scorelist* getnext(){return next;}
        int getid(){return id;}
};
#endif