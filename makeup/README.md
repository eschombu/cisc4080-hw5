# [CISC 4080: Algorithms](http://www.dsm.fordham.edu/~eschomburg/algorithms/)

## Homework 5 Supplement
### Problem 4

This folder contains modified HW5 code to track distances with DFS and compare
them to those found with BFS. I have also modified the test graph a bit for testing.
Output of the compiled program is shown below.

```
$ g++ hw5.cpp 
$ ./a.out 
Testing ./a.out ...


Nodes:
A B C D E F G H I J K 

Edges:
A: B C D 
B: A E F 
C: A F 
D: A G H 
E: B I J 
F: B C 
G: D H 
H: D G 
I: E J 
J: E I 
K: 

In egonet graph with 11 vertices and 24 edges, found 2 components

Distance matrix:
0 1 1 1 2 2 2 2 3 3 INF 
1 0 2 2 1 1 3 3 2 2 INF 
1 2 0 2 3 1 3 3 4 4 INF 
1 2 2 0 3 3 1 1 4 4 INF 
2 1 3 3 0 2 4 4 1 1 INF 
2 1 1 3 2 0 4 4 3 3 INF 
2 3 3 1 4 4 0 1 5 5 INF 
2 3 3 1 4 4 1 0 5 5 INF 
3 2 4 4 1 3 5 5 0 1 INF 
3 2 4 4 1 3 5 5 1 0 INF 
INF INF INF INF INF INF INF INF INF INF 0 

A: 1,20 (pre, post)
B: 2,13 (pre, post)
C: 10,11 (pre, post)
D: 14,19 (pre, post)
E: 3,8 (pre, post)
F: 9,12 (pre, post)
G: 15,18 (pre, post)
H: 16,17 (pre, post)
I: 4,7 (pre, post)
J: 5,6 (pre, post)
K: 21,22 (pre, post)

A: component 1
B: component 1
C: component 1
D: component 1
E: component 1
F: component 1
G: component 1
H: component 1
I: component 1
J: component 1
K: component 2

BFS vs DFS distances from A:
A: 0 0
B: 1 1
C: 1 1
D: 1 1
E: 2 2
F: 2 2
G: 2 2
H: 2 2
I: 3 3
J: 3 3
K: INF INF

eschombu@Eriks-MacBook-Air makeup (master) $ ./a.out test_undir_graph_2.txt 

In egonet graph with 10 vertices and 28 edges, found 1 components

BFS vs DFS distances from A:
A: 0 0
B: 1 1
C: 1 1
D: 1 1
E: 2 2
F: 2 2
G: 2 2
H: 2 2
I: 3 3
J: 2 2

```
