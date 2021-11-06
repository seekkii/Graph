#include "graph.h"
#include "UI.h"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char ** argv) {
   QApplication app{argc, argv};



   CustomWidget *testArea = new CustomWidget;
   testArea->setMinimumSize(500, 500);
   testArea->setContextMenuPolicy(Qt::NoContextMenu);

   QPushButton *Button1 = new QPushButton("DFS");
   QObject::connect(Button1, &QPushButton::clicked, qApp, &QCoreApplication::quit);

   QPushButton *Button2 = new QPushButton("BFS");
   QObject::connect(Button2, &QPushButton::clicked, qApp, &QCoreApplication::quit);

   QPushButton *Button3 = new QPushButton("Load graph");
   QObject::connect(Button2, &QPushButton::clicked, qApp, &QCoreApplication::quit);

   QPushButton *Button4 = new QPushButton("Save graph");
   QObject::connect(Button2, &QPushButton::clicked, qApp, &QCoreApplication::quit);

   QVBoxLayout *layout = new QVBoxLayout;


   layout->addWidget(Button1);
   layout->addWidget(Button2);
   layout->addWidget(Button3);
   layout->addWidget(Button4);
   layout->addWidget(testArea);


   QWidget w;
   w.setLayout(layout);
   w.show();


   return app.exec();
}
