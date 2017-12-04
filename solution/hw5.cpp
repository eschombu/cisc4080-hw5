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
             int & counter,  map<string, int> & components,
             int & component_counter) {
    /* Explore the vertices in the input graph, reachable from the input
    vertex. The pre_post, components, and counter input variables are passed by
    reference and modified to track the vertex exploration order.
    */
    if (!g.contains(vertex)) {
        cerr << "Graph does not contain vertex " << vertex << endl;
        return;
    }

    /**********************/
    pre_post[vertex].pre = counter;
    counter++;
    components[vertex] = component_counter;
    for (int i=0; i < g.n_edges(vertex); i++) {
        if (pre_post[g.edges[vertex][i]].pre < 0) {
            explore(g, g.edges[vertex][i], pre_post, counter, components,
                    component_counter);
        }
    }
    pre_post[vertex].post = counter;
    counter++;
    /**********************/
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
    
    /**********************/
    int explore_counter = 1;
    int component_counter = 1;
    for (int i=0; i < g.n_vertices(); i++){
        if (pre_post[g.vertices[i]].pre < 0) {
            explore(g, g.vertices[i], pre_post, explore_counter, components,
                    component_counter);
            component_counter++;
        }
    }
    /**********************/

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

    /**********************/
    for (int i=0; i < g.n_vertices(); i++) {
        dist[g.vertices[i]] = INF;
    }
    dist[start] = 0;
    queue<string> Q;
    Q.push(start);

    while (!Q.empty()) {
        string v1 = Q.front();
        Q.pop();
        for (int i=0; i < g.n_edges(v1); i++) {
            string v2 = g.edges[v1][i];
            if (dist[v2] == INF) {
                Q.push(v2);
                dist[v2] = dist[v1] + 1;
            }
        }
    }
    /**********************/

    return dist;
}

Matrix<int> get_distance_matrix(Graph g) {
    /* Build a square matrix storing the shortest path difference between each
    pair of vertices.
    */
    Matrix<int> dist_mat(g.n_vertices(), INF);

    /**********************/
    for (int i=0; i < g.n_vertices(); i++) {
        map<string, int> d = BFS(g, g.vertices[i]);
        for (int j=0; j < g.n_vertices(); j++) {
            dist_mat[i][j] = d[g.vertices[j]];
        }
    }
    /**********************/

    return dist_mat;
}

int main(int argc, char *argv[]) {
    /*
        In this solution, I have altered the main block a bit to simplify the
        additional information I'd like to display/save, and writing the path
        distances, pre_post numbers, and component numbers to hard-coded file
        names if a graph file is passed to the program. Otherwise, run on the
        test graph and print the results to standard out.
    */

    Graph g;
    DFSInfo dfs;
    Matrix<int> dist_mat;
    ofstream f;

    // Test case
    if (argc == 1) {
        cout << "Testing " << argv[0] << " ...\n\n";
        g = read_adjacency_file("test_undir_graph.txt", true);
        dfs = DFS(g);
        cout << "\nIn egonet graph with " << g.n_vertices() << " vertices and "
             << g.n_edges() << " edges, found " << dfs.n_components()
             << " components\n" << endl;
        dist_mat = get_distance_matrix(g);
        cout << "Distance matrix:\n";
        dist_mat.print();
        cout << endl;

        // Print pre/post numbers
        for (int i=0; i < g.n_vertices(); i++) {
            string v = g.vertices[i];
            cout << v << ": " << dfs.pre_post[v].pre << ","
                 << dfs.pre_post[v].post << " (pre, post)" << endl;
        }
        cout << endl;

        // Print component numbers
        for (int i=0; i < g.n_vertices(); i++) {
            string v = g.vertices[i];
            cout << v << ": component " << dfs.components[v] << endl;
        }
        cout << endl;

    // Read input file, print distance matrix to command line
    } else {
        g = read_adjacency_file(argv[1], false);
        dfs = DFS(g);
        cout << "\nIn egonet graph with " << g.n_vertices() << " vertices and "
             << g.n_edges() << " edges, found " << dfs.n_components()
             << " components\n" << endl;

        // Write distance matrix to output file
        dist_mat = get_distance_matrix(g);
        cout << "Writing distance matrix to dist_mat.dat" << endl;
        dist_mat.print("dist_mat.dat");

        // Write pre/post numbers to output file
        cout << "Writing pre/post numbers to pre_post.txt" << endl;
        f.open("pre_post.txt");
        if (f.is_open()) {
            for (int i=0; i < g.n_vertices(); i++) {
                string v = g.vertices[i];
                f << v << ": " << dfs.pre_post[v].pre << ","
                  << dfs.pre_post[v].post << " (pre, post)" << endl;
            }
        }
        f.close();

        // Write component numbers to output file
        cout << "Writing component numbers to components.txt" << endl;
        f.open("components.txt");
        if (f.is_open()) {
            for (int i=0; i < g.n_vertices(); i++) {
                string v = g.vertices[i];
                f << v << ": component " << dfs.components[v] << endl;
            }
        }
        f.close();
    }
}