// File: Graph/GraphMain.cpp

#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE.
#include <cctype> // toupper.
#include "Graph.hpp"
#include "Utilities.hpp" // promptFileOpen.
using namespace std;

int main() {
    int fromVert, toVert;
    int numVertices;
    char response;

    cout << "Digraph? (y, n): ";
    cin >> response;
    numVertices = promptIntGE("Number of vertices", 1);
    Graph graph(toupper(response) == 'Y' ? true : false, numVertices);
    do {
        cout << "\n(i)nsert  (r)emove  (b)readth-first  (d)epth-first"
             << "\n(w)rite   (e)dges   (p)ath           (c)omponents   (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'I':
            fromVert = promptIntBetween("From vertex", 0, numVertices - 1);
            toVert = promptIntBetween("To vertex", 0, numVertices - 1);
            graph.insertEdge(fromVert, toVert);
            break;
        case 'R':
            fromVert = promptIntBetween("From vertex", 0, numVertices - 1);
            toVert = promptIntBetween("To vertex", 0, numVertices - 1);
            graph.removeEdge(fromVert, toVert);
            break;
        case 'B':
            fromVert = promptIntBetween("Start vertex", 0, numVertices - 1);
            graph.breadthFirstSearch(fromVert, cout);
            break;
        case 'D':
            fromVert = promptIntBetween("Start vertex", 0, numVertices - 1);
            graph.depthFirstSearch(fromVert, cout);
            break;
        case 'W':
            cout << endl;
            graph.writeAdjacencyLists(cout);
            break;
        case 'E':
            cout << "\nNumber of edges: " << graph.numEdges() << endl;
            break;
        case 'P':
            fromVert = promptIntBetween("From vertex", 0, numVertices - 1);
            toVert = promptIntBetween("To vertex", 0, numVertices - 1);
            graph.writePath(fromVert, toVert, cout);
            break;
        case 'C':
            cout << endl;
            graph.writeComponents(cout);
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    }
    while (toupper(response) != 'Q');
    return EXIT_SUCCESS;
}
