#!/usr/bin/python3
import sys
import random

import networkx as nx
import scipy
import scipy.io


if __name__ == '__main__':
    market_file = sys.argv[1]
    count = int(sys.argv[2])

    rows, cols, *_ = scipy.io.mminfo(market_file)
    assert (rows == cols)
    n = rows

    print(*[
        random.randint(1, n)
        for _ in range(count)
    ], sep='\n', end='')
