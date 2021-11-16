#!/usr/bin/fish

# a all-in-one script for fetch-data & build & benchmark

echo '=== fetch datasets ==='
cd data/
./download-data.fish
./edges_to_csr.py
cd ../

echo '=== build ==='
cmake .
make

echo '=== benchmark ==='
