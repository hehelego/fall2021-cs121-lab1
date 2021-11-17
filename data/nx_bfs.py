#!/usr/bin/python

# used to verify the correctness

# networkx use a 0-based index
import networkx as nx
import scipy
import scipy.io
import sys

if __name__ == '__main__':
    file = sys.argv[1]
    source = int(sys.argv[2])-1
    mm = scipy.io.mmread(file)
    graph = nx.from_scipy_sparse_matrix(mm)

    bfs_tree = nx.bfs_tree(graph, source)
    nodes = set(bfs_tree.nodes)
    edges = sum(1 if e[0] in nodes and e[1]
                in nodes else 0 for e in graph.edges)

    print(len(nodes), edges)
    for k, v in nx.shortest_path_length(bfs_tree, source).items():
        print(k+1, v)
