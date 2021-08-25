#include "inc/Listnode.h"

listnode::~listnode()
{
    if(next!=NULL)
        delete(next);
}

// Getter function for incrementing times of occurance of a word in
// the document with id did
void listnode::add(int did)
{
    if(did==id)
        times++;
    else
    {
        if(next==NULL)
            next=new listnode(did);
        next->add(did);
    }
    
}
// Getter function for the times of occurance of a word in
// the document with id did
int listnode::search(int did)
{
    if(did==id)
        return times;
    else
    {
        if(next==NULL)
            return 0;
        else
            return next->search(did);
    }
}

// Function for returining the number of documents the word
// has been found in
int listnode::volume()
{
    if(next!=NULL)
        return 1+next->volume();
    else
        return 1;
}

// Function for inserting the scorelist of each documents
// for search ranking
void listnode::passdocuments(Scorelist* scorelist)
{
    scorelist->insert(id);
    if(next!=NULL)
        next->passdocuments(scorelist);
}