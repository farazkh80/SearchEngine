#include "Search.h"

using namespace std;

const float k1=1.2;
const float b=0.75;
void search(char* token,Trienode* trie,Mymap* map,int k)
{
    char warray[10][256];
    double IDF[10];
    token=strtok(NULL," \t\n");
    Scorelist* scorelist=new Scorelist();
    int i;
    for(i=0;i<10;i++)
    {
        if(token==NULL)
            break;
        strcpy(warray[i],token);
        IDF[i]=log10(((double)map->getsize()-(double)trie->dsearchword(warray[i],0)+0.5)/((double)trie->dsearchword(warray[i],0)+0.5));
        trie->search(warray[i],0,scorelist);
        token=strtok(NULL," \t\n");
    }
    double avgdl=0;
    for(int m=0;m<map->getsize();m++)
        avgdl+=(double)map->getlength(m);
    avgdl/=(double)map->getsize();
    double score=0;
    Scorelist* templist=scorelist;
    Maxheap* heap=new Maxheap(k);
    int ceil=0;
    while(templist!=NULL)
    {
        for(int l=0;l<i;l++)
            score+=IDF[l]*((double)trie->tfsearchword(templist->getid(),warray[l],0)*(k1+1.0))/((double)trie->tfsearchword(templist->getid(),warray[l],0)+k1*(1.0-b+b*(double)map->getlength(templist->getid())/(double)avgdl));
        heap->insert(score,templist->getid());
        score=0;
        templist=templist->getnext();
        ceil++;
    }
    if(ceil>k)
        ceil=k;
    struct winsize w;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
}

// df function for searching frequency of a specific word in all of the documents
// ex1: /df hello
// "hello": word to be searched for
// ex2: /df
// ex1 will only return the frequency of given word,
// but ex2 will return the frequency of all the words
void df(Trienode* trie)
{
    char* token2;

    // get the word and if not null search
    token2=strtok(NULL," \t\n");
    if(token2!=NULL)
        cout<<token2<<" "<<trie->dsearchword(token2,0)<<endl;

    // else return the frequency for all of the words
    else
    {
        char* buffer=(char*)malloc(256*sizeof(char));
        memset(buffer,'\0',256);
        trie->dsearchall(buffer,0);
        free(buffer);
    }
    token2=NULL;
    free(token2);
}

// tf function for searching frequency of a specific word in a specific document
// ex: /tf 2 hello
// "2": document id and "hello": word to be searched for
int tf(char* token,Trienode* trie)
{
    char* token2;
    token2=strtok(NULL," \t\n");

    // if token is null return
    if(token2==NULL)
    {
        free(token2);
        return -1;
    }
    // check that token is a digit(document id)
    for(int l=0;l<strlen(token2);l++)
    {
        if(!isdigit(token2[l]))
        {
            token2=NULL;
            free(token2);
            return -1;
        }
    }

    // get the int id
    int id=atoi(token2);
    // get and check the word to be searched
    token2=strtok(NULL," \t\n");
    if(token2==NULL)
    {
        free(token2);
        return -1;
    }

    // output the document id and the frequnecy of the word
    cout<<id<<" "<<token2<<" "<<trie->tfsearchword(id,token2,0)<<endl;
}