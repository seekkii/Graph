#include "graph.h"
#include "UI.h"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char ** argv)
{
   Q_INIT_RESOURCE(Resources);
   QApplication app{argc, argv};



   CustomWidget *testArea = new CustomWidget;
   testArea->setMinimumSize(500,500);
   GraphWidget *graph = new GraphWidget;
   QGridLayout *layout = new QGridLayout;
   layout->addWidget(graph);
   layout->addWidget(testArea);





   CustomWidget w;
   w.setLayout(layout);

   w.show();


   return app.exec();
}
