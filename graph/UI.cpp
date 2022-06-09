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

}//void function to draw arrow

void paintnumber(QPainter& painter , QRect r, int i)
{
    QString str1 = QString::number(i);
    QByteArray ba = str1.toLocal8Bit();
    const char *c_str2 = ba.data();
    painter.drawText(r,Qt::AlignCenter, (c_str2));
}//void fuction to draw number from rectangle

void paintnumfrompoint(QPainter& painter , QPoint p, int i)
{
    QString str1 = QString::number(i);
    QByteArray ba = str1.toLocal8Bit();
    const char *c_str2 = ba.data();
    painter.drawText(p, (c_str2));
}//void function to draw number from point


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
    algo = findChild<QComboBox*>("algo");
    display = findChild<QLabel*>("display");
    //create first instances of widget

    QMetaObject::connectSlotsByName(this);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(AdvanceState()));
      _timer.start(100);

    QVBoxLayout *layout = new QVBoxLayout;
    createActions();
    createMenus();
    bar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addWidget(bar);
    layout->addWidget(formWidget);





    setLayout(layout);

    directed = false;

}//constructor of graph widget

void GraphWidget::createActions()
{
    clAct = new QAction(tr("&Clear graph"), this);

    clDrawn = new QAction(tr("&Clear DFS/BFS"), this);

    loadact = new QAction(tr("&Load"), this);

    saveact = new QAction(tr("&Save"), this);
    connect(clAct, &QAction::triggered, this, &GraphWidget::clear);
    connect(clDrawn, &QAction::triggered, this, &GraphWidget::cleardrawn);
    connect(loadact, &QAction::triggered, this, &GraphWidget::load);
    connect(saveact, &QAction::triggered, this, &GraphWidget::save);
}

void GraphWidget::createMenus()
{
    bar = new QMenuBar;
    fileMenu = bar->addMenu(tr("&File"));
    graphMenu = bar->addMenu(tr("&Graph"));
    graphMenu->addAction(clAct);
    graphMenu->addAction(clDrawn);
    fileMenu->addAction(loadact);
    fileMenu->addAction(saveact);
}


void GraphWidget::paintlist(QPainter &painter, QList<QPoint> list)
{
    for (int i = 0; i < edge.size(); i++)
    {
      // get v1 and v2 from edge
      int f_node = edge[i].x();
      int s_node = edge[i].y();

      //draw edge
      QPoint p2 = Pointfromdis(vect[s_node],vect[f_node],h);
      QPoint p1 = Pointfromdis(vect[f_node],vect[s_node],h);


      painter.setPen(Qt::black);
      painter.setBrush(Qt::black);
      //in case of directed
      if (edge[i].z() == 1)
      {
         DrawLineWithArrow(painter,p2,p1);
         if (edge[i].w() >1 )
         {
            QPoint p = ((p2+p1)/2);
            paintnumfrompoint(painter,p,edge[i].w());
         }

       }

      // in case of undirected
       if (edge[i].z() == -1)
       {

          painter.drawLine(p2,p1);
          if (edge[i].w() >1)

          {
              QPoint p = ((p2+p1)/2);
              paintnumfrompoint(painter,p,edge[i].w());
          }

        }
     //
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

void GraphWidget :: AdvanceState()
{
   _edge_num += _growthNum;
   if (_edge_num > 50) _growthNum = -1;
   if (_edge_num < 10) _growthNum = 1;
   update();
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
}// return a point that belongs to line pp0 and is far from p0 a distance d

void GraphWidget::paintEvent(QPaintEvent *)
{

 QPainter painter(this);
 auto r = QRect{QPoint(100, 100), QSize(50, 50)};
 QImage image(":/images/blue.png");
  painter.setPen(QPen{Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});

 for (int i = 0; i < vect.size(); i++)
 {
   //draw the verticles
   r.moveCenter(vect[i]);

   painter.drawEllipse(r);

   painter.drawImage(r,image);
   paintnumber(painter,r,i);
   g.reSize(vect.size());

   //draw the edge between verticles
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
        if (edge[i].w() >1 )
        {
           QPoint p = ((p2+p1)/2);
           paintnumfrompoint(painter,p,edge[i].w());
        }
      }
      if (edge[i].z() == -1)
      {
          painter.setRenderHint(QPainter::Antialiasing, true);


         painter.drawLine(p2,p1);
         if (edge[i].w() >1 )
         {
             QPoint p = ((p2+p1)/2);
             paintnumfrompoint(painter,p,edge[i].w());
         }
       }
    }


       //draw bfs iterate
       if(l_b.size())
       {
          paintlist(painter,l_b);
       }
       //draw dfs iterate
       if(l.size())
       {
          paintlist(painter,l);
       }
       painter.setPen(QPen{Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
   }
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        mousePos = event->pos();
        int x = mousePos.x();
        int y = mousePos.y();
        for(int i = vect.size() -1 ; i >=0; i--)
        {
            int dx = vect[i].x() - x;
            int dy = vect[i].y() - y;
            if (dx*dx + dy*dy < (h*h/4))
            {
                vect[i].setX(x);
                vect[i].setY(y);
                break;
            }
        }
        update();
    }
}//mouse move event

void GraphWidget::on_addEdge_clicked()
{
   if (node_1->value() >= vect.size() && node_2->value() >= vect.size())
       throw("invalid node");

   if (node_1->value() < vect.size() && node_2->value() < vect.size())
    {
        if (directed)// if user want to add verticle directedly
        {
           for (int i = 0; i < edge.size();i++)
           {
              if (edge[i].z() == -1
                 && edge[i].x() == node_1->value()
                 && edge[i].y() == node_2->value()
                 )
              {
                 edge[i].setZ(1);
                 edge[i].setW(weight->value());
              }


          }
          QVector4D p(node_1->value(), node_2->value(),1,weight->value());
          edge.append(p);

          g.addEdgedirec(node_1->value(), node_2->value(),weight->value());

        }
        else // if user want to add verticle undirectedly
        {

           for (int i = 0; i < edge.size();i++)
           {
                if ((edge[i].z() == 1
                    && edge[i].x() == node_1->value()
                    && edge[i].y() == node_2->value()
                    )
                    ||
                    (edge[i].z() == 1
                    && edge[i].x() == node_2->value()
                    && edge[i].y() == node_1->value()
                    ))
                 {
                    edge[i].setZ(-1);
                    edge[i].setW(weight->value());

                 }
           }
               QVector4D p(node_1->value(), node_2->value(),-1,weight->value());
               edge.append(p);
           g.addEdgeundirec(node_1->value(), node_2->value(),weight->value());

        }
    }
  cleardrawn();
  update();
}//adding edge

void GraphWidget::BFS()
{
    if(fromver->value() > vect.size() || g.size() == 0)
    {
        throw("invalid node");
        return;
    }// if the verticle doesn't exist return void

    l_b = g.BFS(fromver->value());// get bfs iterate list
    l.clear();// clear dfs iterate list if there is any so as to not draw them on top of others
    QList<QPoint>::iterator i;
    QString str;
    for (i = l_b.begin();i!=l_b.end();++i)
    {
        str.append(QString::number((*i).x()) +"->" +(QString::number((*i).y())) + ", " );
    }// print bfs iterate list
    update();
    display->setText(str);
}// do bfs on clicked

void GraphWidget::DFS()
{
    if(fromver->value() > vect.size() || g.size() == 0 )
    {
     throw("invalid node");
     return;
    }// if the verticle doesn't exist return void
    g.getDFSlist();//reset visitted
    g.DFS(fromver->value());
    l = g.getDFSlist();// get dfs iterate list
    l_b.clear();// clear bfs iterate list if there is any so as to not draw them on top of others
    QList<QPoint>::iterator i;
    QString str;

    for (i = l.begin();i!=l.end();++i)
    {
        str.append(QString::number((*i).x()) +"->" +(QString::number((*i).y())) + ", " );
    }// print dfs iterate list
      display->setText(str);
    update();

}//do dfs on clicked

void GraphWidget::on_doalgo_clicked()
{
    if (algo->currentText() == "      DFS")
    {
        DFS();
    }

    if (algo->currentText() == "      BFS")
    {
        BFS();
    }
}

void GraphWidget::on_undirected_clicked()
{
    directed = false;
}

void GraphWidget::on_directed_clicked()
{
    directed = true;
}

void GraphWidget::load()
{
    QString line;
    QString fileName = QFileDialog::getOpenFileName(this);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox::information(this, tr("No file name specified"),
        file.errorString());
        return;
     }

    QTextStream in(&file);
    int row = 0;
    clear();
    while (!in.atEnd())
    {
            line = in.readLine();

            QStringList slist = line.split(" ");
            for (int i = 0 ; i <slist.length(); i++)
            {
               if (slist[i].toInt()!=0)
               {
                   QVector4D p(row,i,1,slist[i].toInt());
                   edge.append(p);
               }
            }
            row ++;

    }

    vect.resize(row);
    g.reSize(row);
    for (int i = 0 ; i < edge.size(); i ++)
    {
        g.addEdgedirec(edge[i].x(),edge[i].y(),edge[i].w());
    }

    for (int i = 0 ; i < row; i ++)
    {
        quint32 x_cor = QRandomGenerator::global()->bounded(0,WIDTH);
        quint32 y_cor = QRandomGenerator::global()->bounded(200,HEIGHT);
        QPoint p(x_cor,y_cor);
        vect[i] = p;
    }

    update();
    file.close();
}
void GraphWidget::save()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    QSaveFile file(fileName);
    if (fileName.isEmpty())
            return;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);

    QVector<QVector<int>> str;
    str.resize(g.size(),QVector<int>( g.size() ));
    for (int i = 0 ; i < edge.size();i++)
    {
        if (edge[i].z() == -1){
            if (edge[i].w() == 0)
            {
                str[edge[i].x()][edge[i].y()] = 1;
                str[edge[i].y()][edge[i].x()] = 1;
            }
            else
            {
                str[edge[i].x()][edge[i].y()] = edge[i].w();
                str[edge[i].y()][edge[i].x()] = edge[i].w();
            }
        }
        if (edge[i].z() == 1)
            {
                if (edge[i].w() == 0)
                    str[edge[i].x()][edge[i].y()] = 1;
                else
                    str[edge[i].x()][edge[i].y()] = edge[i].w();
        }

    }

    for(int i = 0; i < g.size();i++)
        for(int j = 0; j < g.size();j++)
        {

            out<<str[i][j];
            out<<" ";

            if (j == g.size()-1)
            {
               out <<'\n';
            }

        }

    file.commit();
}

void GraphWidget::clear()
 {
     vect.clear();
     edge.clear();
     g.clear();
     l.clear();
     l_b.clear();
     update();

}


void GraphWidget::cleardrawn()
{
    l.clear();
    l_b.clear();
    display->setText("");
    update();
}
