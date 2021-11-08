#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include <QString>
#include <QTextEdit>
#include <QMap>
#include <QList>
class Graph : public QObject
{
     Q_OBJECT
    int V;    // No. of vertices
    bool* visited;
    // Pointer to an array containing adjacency
    // lists
    QList<int> *adj;
public:
    Graph(int V);  // Constructor


    void addEdge(int v, int w);  // function to add an edge to graph
    void DFS(int v);  // DFS
    void BFS(int s); //  BFS

};





#endif // GRAPH_H
