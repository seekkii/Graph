#include "ui.h"
#include <QKeyEvent>


ui::ui(QWidget *parent)
    : QWidget(parent)
{
    QUiLoader loader;
    QFile file(":/form.ui");
    file.open(QIODevice::ReadOnly| QIODevice::Text );
    QWidget *formWidget = loader.load(&file, this);
    file.close();

    you = new Character();//your character
    you->set_pos(24,24);
    gamemap = new map();//current map
    row = gamemap->ratio_between_height();
    col = gamemap->ratio_between_width();
    gamemap->setup_map();
    cur_map = gamemap->get_map(1);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(formWidget);





    setLayout(layout);
    QMetaObject::connectSlotsByName(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&ui::fall));
    if (falling())
            timer->start(100);
    update();

}



void ui::paintEvent(QPaintEvent *)
{
 QPainter painter(this);



 for (int i =0; i < row ;i++)
     for (int j =0; j < col;j++)
     {
         float h = i*cur_map[i][j].get_size().width();
         float w = j*cur_map[i][j].get_size().height();
         QSize size_block = cur_map[i][j].get_size();
         auto r = QRect{QPoint(h,w),size_block};
         painter.drawPixmap(r,cur_map[i][j].getpixmap());
     }

 you->setSize(42,42);
 QSize char_size = you->getSize();
 float x = you->get_pos().x();
 float y = you->get_pos().y();
 auto r = QRect{QPoint(x, y), char_size};
 QPixmap you_img = you->getpixmap();
 painter.drawPixmap(r,you_img);


 if (falling())
 {
     timer->start(200);

 }

}

void ui::fall()
{
    const int fall_per_milisec = 30;

    float x = you->get_pos().x();
    float y = you->get_pos().y();
    int j = trunc(y * col/Height);


    if (y+fall_per_milisec < gamemap->get_block_size().height()*(j+1) )
        {
            you->set_pos(x,y+fall_per_milisec);
        }
    else{
        you->set_pos(x,gamemap->get_block_size().height()*(j+1));
    }

    if(!falling())
    {
        timer->stop();
    }


    update();
}

bool ui::falling()
{

    float x = you->get_pos().x();
    float y = you->get_pos().y();
    int i = trunc(x * row/Width);
    int j = trunc(you->get_pos().y() * col/Height);


    if (i>row-1 ||j>col-1)
        return true;
    if(!cur_map[i][j+1].isGround()){
            return true;
        }
    else{
            return false;
        }



}//



void ui::keyPressEvent(QKeyEvent *event)
{
    int dis = you->get_walkstepdis();
    float x = you->get_pos().x();
    float y = you->get_pos().y();
if (!falling())
    {


        if(event->key() == Qt::Key_Up)
        {
            you->set_pos(x,y-dis*5);

        }

        if(event->key() == Qt::Key_Down)
        {
            you->set_pos(x,y+dis);

        }

        if(event->key() == Qt::Key_Right && !face_object_infront() )
        {
            you->set_pos(x+dis,y);



        }


        if(event->key() == Qt::Key_Left&& !face_object_behind() )
        {
            you->set_pos(x-dis,y);

        }
        update();
    }

  if (falling()){
      if(event->key() == Qt::Key_Right && !face_object_infront() )
      {
          you->set_pos(x+dis,y);



      }


      if(event->key() == Qt::Key_Left&& !face_object_behind() )
      {
          you->set_pos(x-dis,y);

      }
      update();

  }


}



bool ui::face_object_infront()
{
    float x = you->get_pos().x();
    float y = you->get_pos().y();
    int i = trunc(x * row/Width);
    int j = trunc(y * col/Height);
    int dis = you->get_walkstepdis();
    QSize size = you->getSize();

    if( cur_map[i+1][j].isGround())
        return true;
    else
        return false;
}

bool ui::face_object_behind()
{
    float x = you->get_pos().x();
    float y = you->get_pos().y();
    int i = trunc(x * row/Width);
    int j = trunc(y * col/Height);
    int dis = you->get_walkstepdis();
    QSize size = you->getSize();

    if (i == 0|| j==0)
        return false;

    if(cur_map[i-1][j].isGround())
        return true;
    else
        return false;
}











