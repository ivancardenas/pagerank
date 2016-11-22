all: PageRank

PageRank: PageRank.c
	mpicc -o PageRank PageRank.c

clean:
	rm PageRank
