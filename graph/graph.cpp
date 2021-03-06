#include "graph.h"
#include "QDebug"

Graph::Graph()
{
    V = 0;
    visited = new bool[V];
    adj.resize(0);
}// constructor
void Graph::reSize(int size)
{
    adj.resize(size);

    //resize visited[]
    bool *q = new bool[size];
    for (int i = 0; i < V; i++)
    {
        q[i] = visited[i];
    }
    delete []visited;
    visited = q;
    q = NULL;
    V = size;
}//resize number of verticles
int Graph::size()
{
    return V;
}

void Graph::clear()
{
    adj.clear();
    V = 0;

}

Graph::~Graph()
{
    adj.clear();
    delete visited;
    visited = nullptr;
}

void Graph::addEdgedirec(int v, int w, int wt)
{
    QPoint f_pair(w,wt);
    QPoint s_pair(v,wt);
    adj[v].removeOne(f_pair);
    adj[w].removeOne(s_pair);
    adj[v].push_back(f_pair);
}//delete existing edge(v,w,wt) if there is and add this edge to the graph directedly

void Graph::addEdgeundirec(int v, int w,int wt)
{
    QPoint f_pair(w,wt);
    QPoint s_pair(v,wt);
    adj[v].removeOne(f_pair);
    adj[w].removeOne(s_pair);
    adj[v].push_back(f_pair);
    adj[w].push_back(s_pair);
}//delete existing edge(v,w,wt) if there is and add this edge to the graph undirectedly


void Graph::DFS(int v)
{
  visited[v] = true;
  QList<QPoint> adjList = adj[v];
  QList<QPoint>::iterator i;
  for (i = adjList.begin(); i != adjList.end(); ++i)

    if (!visited[(*i).x()])
      {

        QPoint p(v,(*i).x());
        result.push_back(p);

        DFS((*i).x());
    }
}// run recursive function for DFS

const QList<QPoint> Graph::getDFSlist()
{
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }
    QList<QPoint> l = result;
    result.clear();

    return l;
}// return a list of dfs iterate


QList<QPoint> Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    QList<int> queue;

    visited[s] = true;
    queue.push_back(s);

    QList<QPoint>::iterator i;
    QList<QPoint> res;
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();


        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[(*i).x()])
            {
                visited[(*i).x()] = true;
                queue.push_back((*i).x());
                QPoint p(s,(*i).x());
                res.push_back(p);
            }
        }
    }
    delete[] visited;
    visited = nullptr;
    return res;
}


