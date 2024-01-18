// File: Graph/Graph.hpp

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream> // ostream.
#include "ArrayT.hpp"
#include "ListL.hpp"
#include "QueueL.hpp"
using namespace std;

enum ColorType {WHITE, GRAY, BLACK};

class GraphVertex {
public:
    ColorType color;
    int discovered;
    int finished;
    int distance;
    int predecessor;
    
    explicit GraphVertex(
        ColorType newColor = WHITE,
        int isDiscovered = -1,
        int isFinished = -1,
        int newDistance = -1,
        int newPredecessor = -1 ):
        color(newColor),
        discovered(isDiscovered),
        finished(isFinished),
        distance(newDistance),
        predecessor(newPredecessor) {
    }     
};

class Graph {
private:
    int _numVertices;
    bool _isDigraph;
    int _time;
    ArrayT<GraphVertex> _vertex;
    ArrayT<shared_ptr<ListL<int>>> _graph;
    ArrayT<shared_ptr<ListLIterator<int>>> _graphIter;

public:
    Graph(bool isDigraph, int numVert);
    // Pre: 0 < numVert.
    // Post: The graph is allocated and initialized to have
    // zero edges and numVert vertices.

    void breadthFirstSearch(int s, ostream &os);
    // Post: A breadth-first search of this graph beginning
    // at vertex s is output to os.
    // Post: Discovered time, finished time, distance from s,
    // and predecessor vertex for each vertex is output to os.

    void depthFirstSearch(int u, ostream &os);
    // Post: A depth-first search of this graph beginning
    // at vertex s is output to os.
    // Post: Discovered time, finished time, and predecessor vertex
    // for each vertex is output to os.

    void insertEdge(int from, int to);
    // Pre: 0 <= from < _numVertices, and 0 <= to < numVertices().
    // Post: If the edge <from, to> is not already in the graph,
    // it is installed; otherwise, the graph is unchanged.

    int numEdges();
    // Post: The number of edges is returned.

    void removeEdge(int from, int to);
    // Pre: 0 <= from < _numVertices, and 0 <= to < _numVertices.
    // Post: If the edge <from, to> is in the graph, it is removed;
    // otherwise, the graph is unchanged.

    void writeAdjacencyLists(ostream &os);
    // Post: The adjacency lists for each vertex with a nonempty list
    // is output to os.

    void writeComponents(ostream &os);
    // Post: A list of all the connected components is output to os,
    // with a count of how many components exist.

    void writePath(int from, int to, ostream &os);
    // Pre: 0 <= from < _numVertices, and 0 <= to < _numVertices.
    // Post: If there is a path from vertex "from" to vertex "to" a
    // path of smallest distance and its length is output to os;
    // otherwise, a statement that no path exists is output.

private:
    void bfs(int s, ostream &os);
    // Post: A breadth-first search of this graph beginning at
    // vertex s is performed without initialization.

    void dfs(int u, ostream &os);
    // Pre: color for each vertex is well-defined and the color
    // of vertex u is WHITE.
    // Post: A depth-first search of this graph beginning at
    // vertex u is performed with the color of each vertex visited,
    // including the color of u, set to BLACK.
    // Post: Vertex u is output to os.

    void initGraph();
    // Post: Every vertex of the graph is initialized in preparation
    // for a breadth-first or depth-first search.

    void writePathHelper(int from, int to, ostream &os);

    void writeVerticesPostBreadth(ostream &os);
    // Post: Discovered time, finished time, predecessor vertex,
    // and distance from s,for each vertex is output to os.

    void writeVerticesPostDepth(ostream &os);
    // Post: Discovered time, finished time, and predecessor
    // vertex for each vertex is output to os.
};

// ========= operator>> =========

// Needed for ArrayT<GraphVertex> in class Graph.
istream &operator>>(istream &is, GraphVertex &) {
    // do nothing
    return is;
}

// ========= operator<< =========

// Needed for ArrayT<GraphVertex> in class Graph.
ostream &operator<<(ostream &os, GraphVertex &) {
    // do nothing
    return os;
}

// ========= Constructor =========
Graph::Graph(bool isDigraph, int numVert):
    _time(0),
    _numVertices(numVert),
    _isDigraph(isDigraph),
    _vertex(numVert),
    _graph(numVert),
    _graphIter(numVert) {
    for (int i = 0; i < numVert; i++) {
        _graph[i] = make_shared<ListL<int>>();
        _graphIter[i] = make_shared<ListLIterator<int>>();
        _graphIter[i]->setIterListL(_graph[i]);
    }
}

// ========= Breadth first search =========
void Graph::breadthFirstSearch(int s, ostream &os) {
    initGraph();
    os << endl;
    bfs(s, os);
    writeVerticesPostBreadth(os);
}

void Graph::bfs(int s, ostream &os) {
    cerr << "Graph::bfs: Exercise for the student." << endl;
    throw -1;
}

// ========= Depth first search =========
void Graph::depthFirstSearch(int u, ostream &os) {
    initGraph();
    os << endl;
    dfs(u, os);
    writeVerticesPostDepth(os);
}

void Graph::dfs(int u, ostream &os) {
    cerr << "Graph::dfsVisit: Exercise for the student." << endl;
    throw -1;
}

// ========= initGraph =========
void Graph::initGraph() {
    _time = 0;
    for (int i = 0; i < _numVertices; i++) {
        _vertex[i].color = WHITE;
        _vertex[i].discovered = -1;
        _vertex[i].finished = -1;
        _vertex[i].distance = -1;
        _vertex[i].predecessor = -1;
    }
}

// ========= insertEdge =========
void Graph::insertEdge(int from, int to) {
    if ((from < 0) || (_numVertices <= from) || (to < 0) || (_numVertices <= to)) {
        cerr << "insertEdge precondition violated: from or to out of range." << endl;
        cerr << "from == " << from << "  to == " << to << endl;
        throw -1;
    }
    if (!_graph[from]->contains(to)) {
        _graph[from]->prepend(to);
    }
    if (!_isDigraph && !_graph[to]->contains(from)) {
        _graph[to]->prepend(from);
    }
}

// ========= numEdges =========
int Graph::numEdges() {
    cerr << "Graph::numEdges: Exercise for the student." << endl;
    throw -1;
}

// ========= removeEdge =========
void Graph::removeEdge(int from, int to) {
    cerr << "Graph::removeEdge: Exercise for the student." << endl;
    throw -1;
}

// ========= writeAdjacencyLists =========
void Graph::writeAdjacencyLists(ostream &os) {
    os << "Adjacency lists" << endl;
    for (int i = 0; i < _numVertices; i++) {
        os << i << ": ";
        os << *_graph[i] << endl;
    }
}

// ========= writeComponents =========
void Graph::writeComponents(ostream &os) {
    cerr << "Graph::connectedComponents: Exercise for the student." << endl;
    throw -1;
}

// ========= writePath =========
void Graph::writePath(int from, int to, ostream &os) {
    if ((from < 0) || (_numVertices <= from) || (to < 0) || (_numVertices <= to)) {
        cerr << "minimumDistance precondition violated: from or to out of range." << endl;
        cerr << "from == " << from << "  to == " << to << endl;
        throw -1;
    }
    initGraph();
    os << "\nBreadth-first search from " << from << ": ";
    bfs(from, os);
    os << "\nPath from " << from << " to " << to << " is: ";
    writePathHelper(from, to, os);
    if (_vertex[to].distance != -1) {
        os << "\nDistance = " << _vertex[to].distance << endl;
    }
}

void Graph::writePathHelper(int from, int to, ostream &os) {
    cerr << "writePathHelper: Exercise for the student." << endl;
    throw -1;
}

// ========= write vertices =========
void Graph::writeVerticesPostBreadth(ostream &os) {
    os << "\n\nDiscovered/finished, predecessor, distance";
    os << endl;
    for (int i = 0; i < _numVertices; i++) {
        os << i << ": "
           << _vertex[i].discovered << "/" << _vertex[i].finished << ", "
           << _vertex[i].predecessor << ", "
           << _vertex[i].distance << endl;
    }
}

void Graph::writeVerticesPostDepth(ostream & os) {
    os << "\n\nDiscovered/finished, predecessor";
    os << endl;
    for (int i = 0; i < _numVertices; i++) {
        os << i << ": "
           << _vertex[i].discovered << "/" << _vertex[i].finished << ", "
           << _vertex[i].predecessor << endl;
    }
}

#endif
