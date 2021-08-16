CC = g++
default: searchengine clean
searchengine: Searchengine.o Readinput.o Map.o Trienode.o Listnode.o Search.o Scorelist.o Maxheap.o
	$(CC) -o searchengine Searchengine.o Readinput.o Map.o Trienode.o Listnode.o Search.o Scorelist.o Maxheap.o
Scorelist.o: Scorelist.cpp Scorelist.h
	$(CC) -c Scorelist.cpp
Maxheap.o: Maxheap.cpp Maxheap.h
	$(CC) -c Maxheap.cpp
Search.o: Search.cpp Search.h
	$(CC) -c Search.cpp
Listnode.o: Listnode.cpp Listnode.h
	$(CC) -c Listnode.cpp
Trienode.o: Trienode.cpp Trienode.h
	$(CC) -c Trienode.cpp
Map.o: Map.cpp Map.h
	$(CC) -c Map.cpp
Readinput.o: Readinput.cpp Readinput.h
	$(CC) -c Readinput.cpp
Searchengine.o: Searchengine.cpp Searchengine.h
	$(CC) -c Searchengine.cpp
clean:
	rm *.o