dijkstra.exe: dijkstra.o hash.o heap.o graph.o
	g++ -o dijkstra.exe hash.o heap.o dijkstra.o graph.o

dijkstra.o: dijkstra.cpp
	g++ -c dijkstra.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

clean:
	rm -rf *.o *.exe  *.exe.dSYM

debug:
	g++ -g -o dijkstraDebug.exe dijkstra.cpp heap.cpp hash.cpp graph.cpp

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups