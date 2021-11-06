#include "UI.h"



void CustomWidget::paintEvent(QPaintEvent *)
{
 for (i = list.begin(); i != list.end(); ++i)
 {
    QPainter painter(this);

   auto r2 = QRect{QPoint(100, 100), QSize(50, 50)};
   r2.moveCenter(*i);
   painter.setPen(QPen{Qt::black, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
   painter.drawEllipse(r2);
 }

}
