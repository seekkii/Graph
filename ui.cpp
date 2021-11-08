#include "UI.h"
GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent)
{

    QPushButton *Button1 = new QPushButton("DFS");
    QObject::connect(Button1, &QPushButton::clicked, qApp, &QCoreApplication::quit);


    QPushButton *Button2 = new QPushButton("BFS");
    QObject::connect(Button2, &QPushButton::clicked, qApp, &QCoreApplication::quit);

    QPushButton *Button3 = new QPushButton("Load graph");
    QObject::connect(Button2, &QPushButton::clicked, qApp, &QCoreApplication::quit);

    QPushButton *Button4 = new QPushButton("Save graph");
    QObject::connect(Button2, &QPushButton::clicked, qApp, &QCoreApplication::quit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(Button1,0,0);
    layout->addWidget(Button2,0,1);
    layout->addWidget(Button3,1,0);
    layout->addWidget(Button4,1,1);

    ui_inputSpinBox1 = new QSpinBox(this);
    layout->addWidget(ui_inputSpinBox1,2,0);

    ui_inputSpinBox2 = new QSpinBox(this);
    layout->addWidget(ui_inputSpinBox2,2,1);
    setLayout(layout);

}


CustomWidget::CustomWidget(QWidget *parent)
    : QWidget(parent)
{}

const char* CustomWidget::toCh_pointer(int i)
{
    QString str1 = QString::number(i);
    QByteArray ba = str1.toLocal8Bit();
    const char *c_str2 = ba.data();

    return c_str2;
}// converting int to const char* for draw text


void CustomWidget::paintEvent(QPaintEvent *)
{

 QPainter painter(this);
 auto r = QRect{QPoint(100, 100), QSize(50, 50)};
 QImage image(":/images/blue.png");

 int f_node = 3;
 int s_node = 5;
 for (int i = 0; i < vect.size(); i++)
 {
   r.moveCenter(vect[i]);
   painter.setPen(QPen{Qt::black, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
   painter.drawEllipse(r);
   const char *c_str2 = toCh_pointer(i);
   painter.drawImage(r,image);
   painter.drawText(r, Qt::AlignCenter, tr(c_str2));

   //in the event of connecting two nodes

   if (i>=5 )
   {
    painter.drawLine(vect[f_node], vect[s_node]);

    r.moveCenter(vect[f_node]);
    painter.drawImage(r,image);
    const char *c_str = toCh_pointer(f_node);
    painter.drawText(r, Qt::AlignCenter, tr(c_str));

    r.moveCenter(vect[s_node]);
    painter.drawImage(r,image);
    c_str = toCh_pointer(s_node);
    painter.drawText(r, Qt::AlignCenter, tr(c_str));
   }
 }
}



int CustomWidget::Edge(int f_node, int s_node)
{
}




