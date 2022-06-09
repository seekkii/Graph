#include "graph.h"
#include "UI.h"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char ** argv)
{
   Q_INIT_RESOURCE(Resources);
   QApplication app{argc, argv};
   GraphWidget w;

   w.setMinimumSize(500,700);
   w.show();

   return app.exec();
}
