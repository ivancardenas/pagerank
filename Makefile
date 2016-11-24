all: PageRankSV PageRankPV

PageRankSV: PageRankSV.C
	mpic++ -o PageRankSV PageRankSV.C -std=c++0x

PageRankPV: PageRankPV.C
	mpic++ -o PageRankPV PageRankPV.C -std=c++0x

clean:
	rm PageRankSV
	rm PageRankPV
