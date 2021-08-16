#include "Scorelist.h"
using namespace std;

Scorelist::~Scorelist()
{
    if(next!=NULL)
        delete(next);
}

void Scorelist::insert(int did)
{
    if(id==did)
        return;
    if(id==-1)
        id=did;
    else
    {
        if(next==NULL)
            next=new Scorelist(did);
        else
            next->insert(did);
    }
}