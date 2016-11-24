all: PageRank

PageRank: PageRank.C
	mpic++ -o PageRank PageRank.C -std=c++0x

clean:
	rm PageRank
