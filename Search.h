#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Trienode.h"
#include "Scorelist.h"
#include "Maxheap.h"
#include "Map.h"
#include <cmath>
#include "./sys/iloctl.h"
#include <unistd.h>

void search(char* token,Trienode *trie,Mymap *map,int k);
void df(Trienode* trie);
int tf(char* token,Trienode* trie);