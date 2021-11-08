#ifndef UI_H
#define UI_H

#include <QMouseEvent>
#include <QString>
#include <QtWidgets>
#include <QPainter>



class CustomWidget : public QWidget
{
    Q_OBJECT;
   QPoint m_mousePos;
   QVector<QPoint> vect;
   public:
   explicit CustomWidget(QWidget *parent = nullptr);
      void paintEvent(QPaintEvent *) override;


      void mousePressEvent(QMouseEvent *event) override
      {
          m_mousePos = event->pos();
          vect.append(m_mousePos);
          update();
      }
      const char* toCh_pointer(int i);

    private slots:
      int Edge(int f_node, int s_node);//check whether two nodes are available to be connect
    private:


};

class GraphWidget : public QWidget
{
 Q_OBJECT;
 public:
   explicit GraphWidget(QWidget *parent = nullptr);
   QSpinBox *ui_inputSpinBox1;
   QSpinBox *ui_inputSpinBox2;
 public : signals :
   void yourSignal();

};


#endif // UI_H
