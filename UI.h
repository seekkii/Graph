#ifndef UI_H
#define UI_H

#include <QMouseEvent>
#include <QtWidgets>
#include <QPainter>
#include <QtUiTools>
#include <QFile>
#include <QTextStream>
#include <QSaveFile>
#include <QRandomGenerator>
#include <graph.h>

#define WIDTH 500
#define HEIGHT 700

class GraphWidget : public QWidget
{
 Q_OBJECT
 public:
    friend class Graph;
    QPoint mousePos;// qpoint that contains mouse positions
    QVector<QPoint> vect;// vector that stores all mouse positions
    QVector<QVector4D> edge;// vector that has edge, weight and bool value for directed/undirected

    explicit GraphWidget(QWidget *parent = nullptr);// constructor
    void paintEvent(QPaintEvent *) override;// paintevent to draw gui


    void mousePressEvent(QMouseEvent *event) override
    {
        if(event->buttons() & Qt::RightButton)
        {
            mousePos = event->pos();

            vect.push_back(mousePos);
            update();
        }
    }//store cursor's position each time mouse is clicked

    void mouseMoveEvent(QMouseEvent *event) override;


    QPoint Pointfromdis(QPoint p, QPoint p0, int d);//return a point that is on pp0 and far from po a distance d
    void paintlist(QPainter &painter, QList<QPoint> list);//draw a graph from QList<QPoint> list

 private slots:

   void on_doalgo_clicked();//do DFS or BFS
   void on_addEdge_clicked();// do connecting vertices
   void on_undirected_clicked();// add edge diected
   void on_directed_clicked();// add edge undirected
   void on_load_clicked();
   void on_save_clicked();

   void AdvanceState();
 private:
   Graph g;//Graph data structure
   void DFS();
   void BFS();
   int _edge_num;
   int _growthNum;

   QTimer _timer;

   QList<QPoint>l;// list that contains dfs iterate
   QList<QPoint>l_b;// list that contains bfs iterate


   QSpinBox *node_1;// spinbox to get v1 value
   QSpinBox *node_2;// spinbox to get v2 value
   QSpinBox *weight;// spinbox to get v1 v2 weight
   QSpinBox *fromver;// spinbox to get the verticle you want to dfs or bfs from
   QComboBox *algo;// combo box to choose what algorithm you want to do

   QLabel *display;// qlabel that print dfs or bfs iterate

   static const int h = 55;//diameter of the circle drawn
   bool directed;//if this value is true, the verticles will be connected directedly, undirectedly otherwise
};


#endif // UI_H
