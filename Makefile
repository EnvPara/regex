Lregex:Main.o	Adj.o	DFA.o	Edge.o	Vertex.o
	g++ -g Main.o	Adj.o	DFA.o	Edge.o	Vertex.o -o Lregex
Main.o:src/main.cpp	src/dfa.hpp src/adj.hpp
	g++ -std=c++11 -g -c src/main.cpp
Adj.o:src/adj.cpp src/adj.hpp src/vertex.hpp
	g++ -std=c++11 -g -c src/adj.cpp
DFA.o:src/dfa.cpp src/dfa.hpp src/edge.hpp src/vertex.hpp src/adj.hpp
	g++ -std=c++11 -g -c src/dfa.cpp
Edge.o:src/edge.cpp src/edge.hpp
	g++ -std=c++11 -g -c src/edge.cpp
Vertex.o:src/vertex.cpp src/vertex.hpp src/edge.hpp
	g++ -std=c++11 -g -c src/vertex.cpp
clean:
	rm -f *.o Lregex


