#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <map>

using namespace std;

const int INF = numeric_limits<int>::max();  // infinity for integers

template <class dType>
class Matrix {
    /* Class for containing and working with rectangular matrices. Does not
    yet perform matrix algebra, just stores them, checks that they have valid
    shape, and provides access and printing methods. Currently used to store
    path distances between vertices in Graphs.
    */
    private:
        vector<vector<dType> > m;  // storage structure

        bool validate() {
            /* Check that storage structure has rectangular dimensions */
            if (m.size() > 0) {
                int nc = m[0].size();
                for (int i=1; i < m.size(); i++) {
                    if (m[i].size() != nc) {
                        throw runtime_error(
                            "Matrix has inconsistent number of columns");
                    }
                }
            }
            return true;
        }

    public:
        int nrow() {
            /* Return number of rows */
            validate();
            return m.size();
        }

        int ncol() {
            /* Return number of columns */
            validate();
            return m.size() > 0 ? m[0].size() : 0;  // 0 cols if 0 rows
        }

        vector<dType>& operator[](int i) {
            /* Access row i */
            validate();
            return m[i];
        }

        Matrix() { /* Default constructor does nothing */ }

        Matrix(int sz) {
            /* Initialize sz x sz square matrix */
            m.resize(sz);
            for (int i=0; i < sz; i++) {
                m[i].resize(sz);
            }
        }

        Matrix(int sz[2]) {
            /* Initialize sz[0] x sz[1] matrix */
            m.resize(sz[0]);
            for (int i=0; i < sz[0]; i++) {
                m[i].resize(sz[1]);
            }
        }

        Matrix(int sz, dType value) {
            /* Initialize sz x sz square matrix filled with value */
            m.resize(sz);
            for (int i=0; i < sz; i++) {
                m[i].resize(sz, value);
            }
        }

        Matrix(int sz[2], dType value) {
            /* Initialize sz[0] x sz[1] matrix filled with value */
            m.resize(sz[0]);
            for (int i=0; i < sz[0]; i++) {
                m[i].resize(sz[1], value);
            }
        }

        Matrix<dType> T() {
            /* Return transposed copy of matrix */
            int s[2] = { ncol(), nrow() };
            Matrix<dType> t (s);
            for (int i=0; i < nrow(); i++) {
                for (int j=0; j < ncol(); j++) {
                    t[j][i] = m[i][j];
                }
            }
            return t;
        }

        void transpose() {
            /* Transpose the matrix "in place" (this Matrix, not a copy) */
            m = T();
        }

        void print(ostream & stream=cout, bool last_newline=true){
            /* Print the matrix to the input ostream (default: cout) */
            for (int i=0; i < nrow(); i++) {
                for (int j=0; j < ncol(); j++) {
                    if (m[i][j] == INF) {
                        stream << "INF ";
                    } else {
                        stream << m[i][j] << " ";
                    }
                }
                if (last_newline || (i < nrow()-1)) stream << "\n";
            }
        }

        void print(string path){
            /* Write the matrix to a file at the input path */
            ofstream f;
            f.open(path.c_str());
            if (f.is_open()) this->print(f, false);
            f.close();
        }
};

class Graph {
    /* Stores graph specification through a list of vertices and their
    adjacencies. Vertices and edges are added to the graph through the
    add_vertex(name) and add_edge(v1, v2) methods. Vertices are identified by
    strings, and edges are stored in a map, which uses vertex names as keys to
    vectors of strings containing the ending vertex names for edges starting
    from the vertex labeled by the key.
    */
    public:
        vector<string> vertices;
        map<string, vector<string> > edges;

        int n_vertices() {
            /* Return number of vertices */
            return vertices.size();
        }

        int n_edges() {
            /* Return total number of edges */
            int n = 0;
            for (int i=0; i < vertices.size(); i++) {
                n += edges[vertices[i]].size();
            }
            return n;
        }

        int n_edges(string vertex) {
            /* Return number of edges connected to vertex */
            return edges[vertex].size();
        }

        void add_vertex(string name) {
            /* Add a vertex with the specified name to the graph. An error is
            thrown if the graph already has a vertex with that name. */
            vector<string> e;
            pair<map<string, vector<string> >::iterator, bool> added =
                edges.insert(pair<string, vector<string> >(name, e));
            if (!added.second) {
                cerr << "Graph already has vertex " << name << endl;
                throw runtime_error("duplicate vertex label");
            }
            vertices.push_back(name);
        }

        void add_edge(string v1, string v2, bool check_v2=true) {
            /* Add an edge to vertex v2 in the edge list for vertex v1. If
            (optional) check_v2 argument is set to false, does not first check
            to make sure vertex v2 is already in the graph. v2 is NOT added to
            the vertex list if this is set to false. */
            try {
                edges[v1].push_back(v2);
            } catch (exception& e) {
                cerr << "vertex 1 may not be contained in edge list\n";
                cerr << e.what() << endl;
            }
            if (check_v2) {
                bool v2_found = false;
                int i = 0;
                while (!v2_found && i < vertices.size()) {
                    if (v2 == vertices[i]) v2_found = true;
                    i++;
                }
                if (!v2_found) {
                    cerr << "Downstream vertex in added edge not in vertices"
                         << endl;
                    throw (runtime_error("vertex not found"));
                }
            }
        }

        bool contains(string vertex) {
            /* Return true if vertex is in graph, otherwise return false */
            return edges.find(vertex) != edges.end();
        }
};

Graph read_adjacency_file(const string & path, bool verbose=false) {
    /* Read a text adjacency list file and return the graph it specifies. The
    file should have one line per vertex, starting with the vertex label, which
    may be followed by a colon (':'), but does not have to be. If the optional
    second argument is set to true, the file lines and resulting vertices and
    adjacency list will be printed to cout.
    */
    ifstream f;
    string line;
    Graph graph;

    f.open(path.c_str());
    if (f.is_open()) {
        do {
            getline(f, line);
            if (line.size() > 0) {
                istringstream line_stream (line);
                string v1;

                // First entry is starting vertex, perhaps with colon
                line_stream >> v1;
                int colon_idx = v1.find(':');
                if (colon_idx < v1.npos) {
                    v1 = v1.substr(0, colon_idx);
                }
                graph.add_vertex(v1);

                // List of connected vertices follow
                string v2;
                do {
                    line_stream >> v2;
                    if (v2.size() > 0) {
                        graph.add_edge(v1, v2, false);
                    }
                } while (!line_stream.eof());
            }
        } while (!f.eof());
        if (verbose) cout << endl;
        f.close();
    } else {
        cerr << path << " not found!" << endl;
        return graph;
    }

    if (verbose) {
        cout << "Nodes:\n";
        for (int i = 0; i < graph.n_vertices(); i++) {
            cout << graph.vertices[i] << " ";
        }
        cout << "\n\nEdges:\n";
        for (int i = 0; i < graph.n_vertices(); i++) {
            cout << graph.vertices[i] << ": ";
            for (int j = 0; j < graph.n_edges(graph.vertices[i]); j++) {
                cout << graph.edges[graph.vertices[i]][j] << " ";
            }
            cout << "\n";
        }
    }

    return graph;
}

bool write_adjacency_file(Graph g, string path) {
    /* Write a text adjacency list file to the input path for the input graph.
    The file will be in the format readable by read_adjacency_file(path),
    described above.
    */
    ofstream f;
    bool written;
    f.open(path.c_str());
    if (f.is_open()){
        for (int i = 0; i < g.vertices.size(); i++) {
            cout << g.vertices[i] << ": ";
            for (int j = 0; j < g.n_edges(g.vertices[i]); j++) {
                cout << g.edges[g.vertices[i]][j] << " ";
            }
            cout << "\n";
        }
        written = true;
        f.close();
    } else written = false;
    return written;
}

struct PrePost {
    /* Simple struct for storing pre and post numbers tracked during a depth-
    first search (DFS).
    */
    int pre;
    int post;
};

class PrePostMap: public map<string, PrePost> {
    /* A map for tracking pre/post-numbers during DFS, keyed by the strings
    labeling vertices. A constructor accepting a graph argument can be used to
    create a PrePost value for each vertex in the graph, initialized to
    {-1, -1}, which indicates that a vertex has not been visited.
    */
    public:
        PrePostMap(Graph g) {
            PrePost neg = {-1, -1};
            for (int i=0; i < g.n_vertices(); i++) {
                insert(pair<string, PrePost>(g.vertices[i], neg));
            }
        }
        PrePostMap() {}
};

