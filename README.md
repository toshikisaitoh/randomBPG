# Random generation of Bipartite Permutation Graphs

The program is written in C++. You complile the program `genBPG.cpp` and execute it with the number of vertices in the graph. The program generates an bipartite permutation graph uniformly at random and outputs its adjacency list and the permutation diagram of the graph. 

## Example how to compile and execute the program

We compile and execute the program as follows. 

```
$ g++ genBPG.cpp
$ ./a.out 6
```

The program outputs the permutation diagram of an bipartite permutation graph and its adjacency list of the graph. 

```
Permutation: 3 4 6 1 2 5 
Graph: (n, m) = (6, 7)
1: 4 5 
2: 4 5 
3: 4 5 6 
4: 1 2 3 
5: 1 2 3 
6: 3 
```