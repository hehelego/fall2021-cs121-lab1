#!/usr/bin/fish

git clone https://github.com/farkhor/PaRMAT.git
cd PaRMAT/Release
make
mv PaRMAT ../../
cd ../../

set n 100000000
set m 1000000000
set n 1000
set m 10000
./PaRMAT -nVertices $n -nEdges $m -undirected -thread 32 -noDuplicateEdges -a 0.3  -b 0.25 -c 0.25 -output ../RMAT1.txt
./PaRMAT -nVertices $n -nEdges $m -undirected -thread 32 -noDuplicateEdges -a 0.45 -b 0.25 -c 0.15 -output ../RMAT2.txt
./PaRMAT -nVertices $n -nEdges $m -undirected -thread 32 -noDuplicateEdges -a 0.57 -b 0.19 -c 0.19 -output ../RMAT3.txt

