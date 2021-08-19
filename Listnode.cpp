#include "inc/Listnode.h"

listnode::~listnode()
{
    if(next!=NULL)
        delete(next);
}

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

int listnode::volume()
{
    if(next!=NULL)
        return 1+next->volume();
    else
        return 1;
}

void listnode::passdocuments(Scorelist* scorelist)
{
    scorelist->insert(id);
    if(next!=NULL)
        next->passdocuments(scorelist);
}