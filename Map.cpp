#include "Map.h"
using namespace std;
Mymap::Mymap(int size,int buffersize):size(size),buffersize(buffersize)
{
    documents=(char**)malloc(size*sizeof(char*));
    lengths=(int*)malloc(size*sizeof(int));
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
    if(curr!=i)
    {
        token=NULL;
        free(token);
        return -1;
    }
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
    token=NULL;
    free(token);
}