#!/usr/bin/fish


# fetch the first 4 testing dataset from snap,
# aria2 is employed for parallelzed downloading
aria2c -j6 https://snap.stanford.edu/data/roadNet-CA.txt.gz
aria2c -j6 https://snap.stanford.edu/data/bigdata/communities/com-orkut.ungraph.txt.gz
aria2c -j6 https://snap.stanford.edu/data/soc-LiveJournal1.txt.gz
aria2c -j6 https://snap.stanford.edu/data/web-Stanford.txt.gz

# decompress
set files (ls | grep '.gz$')
for f in $files
	gzip --keep --decompress $f
end

# generate RMAT graphs
./gen-RMAT.fish

# convert the edgeslist files into matrix market coordinate format
set files (ls | grep '.txt$')
for f in $files
	../bin/snap_to_mm $f $f.mm
end
