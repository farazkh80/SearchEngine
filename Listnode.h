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
        void add(int did);
        int search(int did);
        int volume();
        void passdocuments(Scorelist* scorelist);
};
#endif