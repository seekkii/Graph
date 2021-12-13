#ifndef UI_H
#define UI_H

#include <QMouseEvent>
#include <QtWidgets>
#include <QPainter>
#include <graph.h>
#include <QtUiTools>
#include <QFile>
#include <cmath>



class GraphWidget : public QWidget
{
 Q_OBJECT
 public:
    friend class Graph;
    QPoint m_mousePos;
    QVector<QPoint> vect;
    QVector<QVector4D> edge;
    QVector<QLine> lines;
       explicit GraphWidget(QWidget *parent = nullptr);
       void paintEvent(QPaintEvent *) override;


       void mousePressEvent(QMouseEvent *event) override
       {
           m_mousePos = event->pos();
           vect.append(m_mousePos);
           update();
       }

     QPoint Pointfromdis(QPoint p, QPoint p0, int d);//return a point that is the intersection of circle r and line rp
     void paintlist(QPainter &painter, QList<QPoint> list);

 private slots:
   void on_DFS_clicked();
   void on_BFS_clicked();
   void on_addEdge_clicked();
   void on_undirected_clicked();
   void on_directed_clicked();
 private:
   Graph g;
   QList<QPoint>l;
   QList<QPoint>l_b;

   QSpinBox *node_1;
   QSpinBox *node_2;
   QSpinBox *weight;
   QSpinBox *fromver;
   QLabel *display;
   static const int h = 55;//diameter of the circle drawn
   bool directed;


};


#endif // UI_H
