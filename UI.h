#ifndef UI_H
#define UI_H

#include <QTextEdit>
#include <QMouseEvent>
#include <QString>
#include <QtWidgets>

class CustomWidget : public QWidget
{
   QPoint m_mousePos;
   QList<QPoint> list;
   QList<QPoint>::iterator i;


public:
   explicit CustomWidget(QWidget *parent = nullptr) : QWidget{parent} {}
   void paintEvent(QPaintEvent *) override;
   int keyByNum(const Qt::MouseButton key);

   void mousePressEvent(QMouseEvent *event) override
   {
       m_mousePos = event->pos();

       list.append(m_mousePos);
       update();
   }



   void mouseMoveEvent(QMouseEvent *event) override
   {
       m_mousePos = event->pos();
       update();
   }

};

#endif // UI_H
