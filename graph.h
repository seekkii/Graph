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
    ~Graph();//destructor
    void reSize(int size);// resize the number of vertices
    int size();//return size of graph
    void addEdgedirec(int v, int w,int weight);  // function to add an edge to graph directed
    void addEdgeundirec(int v, int w,int wt);    // function to add an edge to graph undirected
    void clear();

    void DFS(int v);  // DFS
    QList<QPoint> BFS(int s); //  BFS
    const QList<QPoint> getDFSlist();//get a list that contains DFS iterate



private:
    int V;    // numbers of vertices
    bool *visited; // array of bool ptr to record when a node is visited
    QVector<QList<QPoint>> adj;//adjacency list
    QList<QPoint> result;// list contains DFS iterate


};





#endif // GRAPH_H
