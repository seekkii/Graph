#include "UI.h"

//UI for drawing
void DrawLineWithArrow(QPainter& painter, QPoint start, QPoint end) {

  painter.setRenderHint(QPainter::Antialiasing, true);

  qreal arrowSize = 10; // size of head

  QLineF line(end, start);

  double angle = std::atan2(-line.dy(), line.dx());
  QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
  QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);

  QPolygonF arrowHead;
  arrowHead.clear();
  arrowHead << line.p1() << arrowP1 << arrowP2;
  painter.drawLine(line);
  painter.drawPolygon(arrowHead);

}//draw arrow

void paintnumber(QPainter& painter , QRect r, int i)
{
    QString str1 = QString::number(i);
    QByteArray ba = str1.toLocal8Bit();
    const char *c_str2 = ba.data();
    painter.drawText(r,Qt::AlignCenter, (c_str2));
}//draw number from rectangle

void paintnumfrompoint(QPainter& painter , QPoint p, int i)
{
    QString str1 = QString::number(i);
    QByteArray ba = str1.toLocal8Bit();
    const char *c_str2 = ba.data();
    painter.drawText(p, (c_str2));
}//draw number from point


//UI for interacting
GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent)
{
    QUiLoader loader;

    QFile file(":/form.ui");
    file.open(QFile::ReadOnly);
    QWidget *formWidget = loader.load(&file, this);
    file.close();
    node_1 = findChild<QSpinBox*>("V1");
    node_2 = findChild<QSpinBox*>("V2");
    weight = findChild<QSpinBox*>("weight");
    fromver = findChild<QSpinBox*>("fromver");
    QMetaObject::connectSlotsByName(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(formWidget);
    display = new QLabel;

    layout->addWidget(display);


    setLayout(layout);
    directed = false;

}//constructor of graph widget

void GraphWidget::paintlist(QPainter &painter, QList<QPoint> list)
{
    for (int i = 0; i < edge.size(); i++)
    {
      int f_node = edge[i].x();
      int s_node = edge[i].y();
      QPoint p2 = Pointfromdis(vect[s_node],vect[f_node],h);
      QPoint p1 = Pointfromdis(vect[f_node],vect[s_node],h);


      painter.setPen(Qt::black);
      painter.setBrush(Qt::black);
      if (edge[i].z() == 1)
      {
         DrawLineWithArrow(painter,p2,p1);
         if (edge[i].w() != 0)
         {
            QPoint p = ((p2+p1)/2);
            paintnumfrompoint(painter,p,edge[i].w());
         }
       }
       if (edge[i].z() == -1)
       {
          painter.setRenderHint(QPainter::Antialiasing, true);
          painter.drawLine(p2,p1);
          if (edge[i].w() != 0)
          {
              QPoint p = ((p2+p1)/2);
              paintnumfrompoint(painter,p,edge[i].w());
          }
        }

     }

        painter.setPen(QPen{Qt::red,3});
        painter.setBrush(Qt::red);
        QList<QPoint>::iterator iter;
        for (iter = list.begin();iter!=list.end();++iter)
        {

            QPoint p2 = Pointfromdis(vect[(*iter).y()], vect[(*iter).x()],h);


            QPoint p1 = Pointfromdis(vect[(*iter).x()], vect[(*iter).y()],h);
            DrawLineWithArrow(painter,p2,p1);

        }

     }

QPoint GraphWidget::Pointfromdis(QPoint p, QPoint p0,int d)
{

    double x0 = p0.x();
    double y0 = p0.y();

    double xa = p.x();
    double ya = p.y();

    //line equation y=ax+b of p_1 and center of circle o(x0,y0)
    double a = (y0-ya)/(x0-xa);
    double b = y0-a*x0;

    double cof1 = a*a + 1;
    double cof2 = 2*a*(b-y0) - 2*x0;
    double cof3 = x0*x0+(b-y0)*(b-y0)-(d/2)*(d/2);

    double xb ;
    if (xa<x0)
    {
        xb = (cof2*-1-sqrt(cof2*cof2-4*cof1*cof3))/(2*cof1);
    }
    else
    {
        xb = (cof2*-1+sqrt(cof2*cof2-4*cof1*cof3))/(2*cof1);
    }
    double yb = a*xb+b;


    QPoint re_point(round(xb),round(yb));
    return re_point;
}

void GraphWidget::paintEvent(QPaintEvent *)
{

 QPainter painter(this);
 auto r = QRect{QPoint(100, 100), QSize(50, 50)};
 QImage image(":/images/blue.png");
  painter.setPen(QPen{Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});

 for (int i = 0; i < vect.size(); i++)
 {
   r.moveCenter(vect[i]);

   painter.drawEllipse(r);

   painter.drawImage(r,image);
   paintnumber(painter,r,i);
   g.reSize(vect.size());

   //in the event of connecting two nodes
   for (int i = 0; i < edge.size(); i++)
   {
     int f_node = edge[i].x();
     int s_node = edge[i].y();
     QPoint p2 = Pointfromdis(vect[s_node],vect[f_node],h);
     QPoint p1 = Pointfromdis(vect[f_node],vect[s_node],h);


     painter.setPen(QPen{Qt::black, 2,Qt::SolidLine});
     painter.setBrush(Qt::black);
     if (edge[i].z() == 1)
     {
        DrawLineWithArrow(painter,p2,p1);
        if (edge[i].w() != 0)
        {
           QPoint p = ((p2+p1)/2);
           paintnumfrompoint(painter,p,edge[i].w());
        }
      }
      if (edge[i].z() == -1)
      {
         painter.drawLine(p2,p1);
         if (edge[i].w() != 0)
         {
             QPoint p = ((p2+p1)/2);
             paintnumfrompoint(painter,p,edge[i].w());
         }
       }

    }



   if(l_b.size())
   {

     paintlist(painter,l_b);

   }
    if(l.size())
    {

      paintlist(painter,l);

    }


    //


  painter.setPen(QPen{Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});




 }
}

void GraphWidget::on_addEdge_clicked()
{
   if (node_1->value() < vect.size() && node_2->value() < vect.size())
    {
        if (directed == true)
        {
         for (int i = 0; i < edge.size();i++)
         {
               if (edge[i].z() == 1
                    && (edge[i].x() == node_1->value()
                    && edge[i].y() == node_2->value()
                    && edge[i].w() == weight->value())
                   )
                   {
                       edge[i].setZ(1);

                   }
         }

         QVector4D p(node_1->value(), node_2->value(),1,weight->value());
         edge.append(p);
         g.addEdgedirec(node_1->value(), node_2->value(),weight->value());
         update();
        }
        else
        {
            for (int i = 0; i < edge.size();i++)
            {
                if (edge[i].z() == 1
                     && (edge[i].x() == node_1->value()
                     && edge[i].y() == node_2->value()
                     && edge[i].w() == weight->value())
                    )
                    {
                        edge[i].setZ(-1);
                    }

            }
            QVector4D p(node_1->value(), node_2->value(),-1,weight->value());
            edge.append(p);

            g.addEdgeundirec(node_1->value(), node_2->value(),weight->value());

            update();
        }
    }
}

void GraphWidget::on_BFS_clicked()
{
    if(fromver->value() > vect.size())
    {
     return;
    }
    l_b = g.BFS(fromver->value());
    l.clear();
    QList<QPoint>::iterator i;
    QString str;
    for (i = l_b.begin();i!=l_b.end();++i)
    {
        str.append(QString::number((*i).x())+" " +(QString::number((*i).y())));
    }
    update();
    display->setText(str);


}

void GraphWidget::on_DFS_clicked()
{
    if(fromver->value() > vect.size())
    {
     return;
    }
    g.DFS(fromver->value());
    l = g.getDFSlist();
     l_b.clear();
    QList<QPoint>::iterator i;



    QString str;
    for (i = l.begin();i!=l.end();++i)
    {
        str.append(QString::number((*i).x()) +" " +(QString::number((*i).y())));
    }

     update();
     display->setText(str);

}

void GraphWidget::on_undirected_clicked()
{
    directed = false;

}

void GraphWidget::on_directed_clicked()
{
    directed = true;

}
