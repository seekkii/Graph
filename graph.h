#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include <QString>
#include <QTextEdit>
#include <QMap>
#include <QList>
class Graph : public QTextEdit
{
    int V;    // No. of vertices
    bool* visited;
    // Pointer to an array containing adjacency
    // lists
    QList<int> *adj;
public:
    using QTextEdit::QTextEdit;

    Graph(int V);  // Constructor

    // function to add an edge to graph
    void addEdge(int v, int w);
    void DFS(int v);  // DFS traversal

    // utility function called by DFS
    // prints BFS traversal from a given source s
    void BFS(int s);

};





#endif // GRAPH_H
