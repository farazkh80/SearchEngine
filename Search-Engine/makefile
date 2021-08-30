CC = g++
default: searchengine clean
searchengine: Searchengine.o src/Readinput.o src/Map.o src/Trienode.o src/Listnode.o src/Search.o src/Scorelist.o src/Maxheap.o
	$(CC) -o searchengine Searchengine.o src/Readinput.o src/Map.o src/Trienode.o src/Listnode.o src/Search.o src/Scorelist.o src/Maxheap.o
Scorelist.o: src/Scorelist.cpp inc/Scorelist.h
	$(CC) -c Scorelist.cpp
Maxheap.o: src/Maxheap.cpp inc/Maxheap.h
	$(CC) -c src/Maxheap.cpp
Search.o: src/Search.cpp inc/Search.h
	$(CC) -c src/Search.cpp
Listnode.o: src/Listnode.cpp inc/Listnode.h
	$(CC) -c src/Listnode.cpp
Trienode.o: src/Trienode.cpp inc/Trienode.h
	$(CC) -c src/Trienode.cpp
Map.o: Msrc/ap.cpp inc/Map.h
	$(CC) -c src/Map.cpp
Readinput.o: Readinput.cpp inc/Readinput.h
	$(CC) -c src/Readinput.cpp
Searchengine.o: Searchengine.cpp inc/Searchengine.h
	$(CC) -c Searchengine.cpp
clean:
	rm *.o