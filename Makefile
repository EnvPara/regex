Lregex:Main.o	Adj.o	DFA.o	Edge.o	Vertex.o
	g++ -g Main.o	Adj.o	DFA.o	Edge.o	Vertex.o -o Lregex
Main.o:src/Main.cpp	src/DFA.h src/Adj.h
	g++ -g -c src/Main.cpp
Adj.o:src/Adj.cpp src/Adj.h src/Vertex.h
	g++ -g -c src/Adj.cpp
DFA.o:src/DFA.cpp src/DFA.h src/Edge.h src/Vertex.h src/Adj.h
	g++ -g -c src/DFA.cpp
Edge.o:src/Edge.cpp src/Edge.h
	g++ -g -c src/Edge.cpp
Vertex.o:src/Vertex.cpp src/Vertex.h src/Edge.h
	g++ -g -c src/Vertex.cpp
clean:
	rm -f Main.o Adj.o DFA.o Edge.o	Vertex.o Lregex


