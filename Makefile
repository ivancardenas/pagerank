all: PageRank

PageRank: PageRank.o
	g++ -o PageRank PageRank.o

PageRank.o: PageRank.C
	g++ -c -Wall --std=c++11 PageRank.C -o PageRank.o

clean:
	rm *.o
	rm PageRank
