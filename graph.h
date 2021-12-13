#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include <QString>
#include <QTextEdit>
#include <QMap>
#include <QList>

class Graph
{


public:
    Graph();//constructor
    void reSize(int size);// resize the number of vertices
    void addEdgedirec(int v, int w,int weight);  // function to add an edge to graph
    void addEdgeundirec(int v, int w,int wt);
    void delEdge(int v, int w); // function to delete an edge from graph
    void DFS(int v);  // DFS
    QList<QPoint> BFS(int s); //  BFS
    QList<QPoint> getDFSlist();//get a list that contains DFS iterate
    QList<QPoint> result;// list contains DFS iterate
    QVector<QList<QPoint>> adj;//adjacency list

private:
    int V;    // numbers of vertices
    bool *visited; // array of bool ptr to record when a node is visited
    int weight;

};





#endif // GRAPH_H
