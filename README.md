# Random generation of Bipartite Permutation Graphs

The program is written in C++. You complile the program `genBPG.cpp` and execute it with the number of vertices in the graph. The program generates an bipartite permutation graph uniformly at random and outputs its adjacency list and the permutation diagram of the graph. This algorithm is based on the algorithm in [1].

## Example how to compile and execute the program

We compile and execute the program as follows. 

```
$ g++ genBPG.cpp
$ ./a.out 6
```

The program outputs the permutation diagram of an bipartite permutation graph and its adjacency list of the graph. 

```
Permutation: 4 1 6 2 3 5 
Graph: (n, m) = (6, 6)
1: 4 
2: 4 6 
3: 4 6 
4: 1 2 3 
5: 6 
6: 2 3 5 
```

## References
[1] [Toshiki Saitoh, Yota Otachi, Katsuhisa Yamanaka, and Ryuhei Uehara: “Random Generation and Enumeration of Bipartite Permutation Graphs,” Journal of Discrete Algorithms, vol. 10, pp. 84-97, 2012, January.](https://linkinghub.elsevier.com/retrieve/pii/S1570866711001006)

