CC = g++
default: searchengine clean
searchengine: Searchengine.o Readinput.o Map.o Trienode.o Listnode.o Search.o Scorelist.o Maxheap.o
	$(CC) -o searchengine Searchengine.o Readinput.o Map.o Trienode.o Listnode.o Search.o Scorelist.o Maxheap.o
Scorelist.o: Scorelist.cpp inc/Scorelist.h
	$(CC) -c Scorelist.cpp
Maxheap.o: Maxheap.cpp inc/Maxheap.h
	$(CC) -c Maxheap.cpp
Search.o: Search.cpp inc/Search.h
	$(CC) -c Search.cpp
Listnode.o: Listnode.cpp inc/Listnode.h
	$(CC) -c Listnode.cpp
Trienode.o: Trienode.cpp inc/Trienode.h
	$(CC) -c Trienode.cpp
Map.o: Map.cpp inc/Map.h
	$(CC) -c Map.cpp
Readinput.o: Readinput.cpp inc/Readinput.h
	$(CC) -c Readinput.cpp
Searchengine.o: Searchengine.cpp inc/Searchengine.h
	$(CC) -c Searchengine.cpp
clean:
	rm *.o