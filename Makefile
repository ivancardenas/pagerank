all: PageRank

PageRank: PageRank.C
	mpicc -o PageRank PageRank.C

clean:
	rm *.o
	rm PageRank
