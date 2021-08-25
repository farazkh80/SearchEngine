#include "inc/Map.h"
using namespace std;
Mymap::Mymap(int size,int buffersize):size(size),buffersize(buffersize)
{
    documents=(char**)malloc(size*sizeof(char*)); // char double pointer for storing the documents of dataset
    lengths=(int*)malloc(size*sizeof(int)); // int pointer for storing document length
    for(int i=0;i<size;i++)
        documents[i]=(char*)malloc(buffersize*sizeof(char));
}
Mymap::~Mymap()
{
    for(int i=0;i<size;i++)
        free(documents[i]);
    free(documents);
    free(lengths);
}
int Mymap::insert(char* line,int i)
{
    int curr;
    char* token;
    token=strtok(line," \t");
    curr=atoi(token);

    // check if the input id is the same as passed i
    if(curr!=i)
    {
        token=NULL;
        free(token);
        return -1;
    }

    // whitespace trimming from both sides
    token=strtok(NULL,"\n");
    while(token[0]==' ')
        token++;
    int end=0;
    while(token[end]!='\0')
        end++;
    end--;
    while(end!=0 && token[end]==' ')
        token[end--]='\0';
    strcpy(documents[i],token);
    cout << "token is " << token << endl;
    token=NULL;
    free(token);
}