#!/usr/bin/python3
import sys

import networkx as nx
import scipy
import scipy.io


def convert_one(src_path: str, dst_path: str) -> None:
    graph = nx.read_edgelist(src_path)
    matrix = nx.to_scipy_sparse_matrix(graph)
    with open(dst_path, 'wb') as f:
        scipy.io.mmwrite(f, matrix)


if __name__ == '__main__':
    market_files = sys.argv[1:]
    for i in market_files:
        print(f'[edges to matrix market] converting {i}')
        convert_one(i, i+'.mm')
        print(f'[edges to matrix market] finished {i}')
