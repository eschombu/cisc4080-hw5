#include "hw5.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

/* Constants, functions, and classes defined in hw5.h:
const int INF
class Matrix
class Graph
read_adjacency_file()
write_adjacency_file()
class PrePostMap
*/

void explore(Graph & g, string vertex, PrePostMap & pre_post,
             int & counter) {
    /* Explore the vertices in the input graph, reachable from the input
    vertex. The pre_post and counter input variables are passed by reference
    and modified to track the vertex exploration order.
    */
    if (!g.contains(vertex)) {
        cerr << "Graph does not contain vertex " << vertex << endl;
        return;
    }
    
    /****
    YOUR IMPLEMENTATION HERE
    ****/
}

class DFSInfo {
    /* Container class for information computed and/or stored during a depth-
    first search. Tracks PrePost numbers and a component number for each
    vertex.
    */
    public:
        PrePostMap pre_post;
        map<string, int> components;
        int n_components() {
            int max = 0;
            for (map<string, int>::iterator it = components.begin();
                    it != components.end(); it++) {
                if (it->second > max) max = it->second;
            }
            return max;
        }
};

DFSInfo DFS(Graph g){
    /* Perform a depth-first search, tracking each vertex's pre/post numbers
    and a component number. Return this info in the DFSInfo data structure.
    */
    PrePostMap pre_post (g);
    map<string, int> components;

    /****
    YOUR IMPLEMENTATION HERE
    ****/

    DFSInfo dfs_info;
    dfs_info.pre_post = pre_post;
    dfs_info.components = components;
    return dfs_info;
}

map<string, int> BFS(Graph g, string start) {
    /* Perform a breadth-first search on the input graph, beginning at the
    start vertex argument. Track the shortest path distance of each vertex in
    the graph from this start vertex.
    */
    map<string, int> dist;

    if (!g.contains(start)) {
        cerr << "Graph does not contain vertex " << start << endl;
        return dist;
    }

    /****
    YOUR IMPLEMENTATION HERE
    ****/

    return dist;
}

Matrix<int> get_distance_matrix(Graph g) {
    /* Build a square matrix storing the shortest path difference between each
    pair of vertices.
    */
    Matrix<int> dist_mat(g.n_vertices(), INF);

    /****
    YOUR IMPLEMENTATION HERE
    ****/

    return dist_mat;
}

int main(int argc, char *argv[]) {
    // Test case
    if (argc == 1) {
        cout << "Testing " << argv[0] << " ...\n\n";
        Graph g = read_adjacency_file("test_undir_graph.txt", true);
        DFSInfo dfs = DFS(g);
        cout << "\nIn egonet graph with " << g.n_vertices() << " vertices and "
             << g.n_edges() << " edges, found " << dfs.n_components()
             << " components\n" << endl;
        Matrix<int> dist_mat = get_distance_matrix(g);
        cout << "Distance matrix:\n";
        dist_mat.print();
        cout << endl;

    // Read input file, print distance matrix to command line
    } else if (argc == 2){
        Graph g = read_adjacency_file(argv[1], true);
        DFSInfo dfs = DFS(g);
        cout << "\nIn egonet graph with " << g.n_vertices() << " vertices and "
             << g.n_edges() << " edges, found " << dfs.n_components()
             << " components\n" << endl;
        Matrix<int> dist_mat = get_distance_matrix(g);
        cout << "Distance matrix:\n";
        dist_mat.print();
        cout << endl;

    // Read input file, write distance matrix to output file
    } else {
        Graph g = read_adjacency_file(argv[1], false);
        DFSInfo dfs = DFS(g);
        cout << "In egonet graph with " << g.n_vertices() << " vertices and "
             << g.n_edges() << " edges, found " << dfs.n_components()
             << " components\n" << endl;
        Matrix<int> dist_mat = get_distance_matrix(g);
        cout << "Writing distance matrix to " << argv[2] << endl;
        dist_mat.print(argv[2]);
    }
}
