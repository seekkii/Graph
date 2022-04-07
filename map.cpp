#include "map.h"

ground::ground()
{}

ground::ground(float x, float y)
{
    QPixmap pixmap(":/images/map.jpg");
    ground_img = pixmap;
    type = "brick";

    QSize size(40,40);
    this->size = size;
    this->x = x;
    this->y = y;
}

QPointF ground::get_ground_pos() const
{
    QPointF pos(x,y);
    return pos;
}

void ground::set_ground_pos(float x, float y)
{
    this->x = x;
    this->y = y;
}

QPixmap ground::getpixmap() const
{
    return ground_img;
}

void ground::setpixmap(QPixmap pm)
{
    ground_img = pm;
}

bool ground::isGround()
{
    if (ground_img.isNull())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void ground::set_size(float h, float w)
{
    QSize size(h,w);
    this->size = size;
}

QSize ground::get_size()
{
    return size;
}

void ground::set_type(QString type)
{
   this->type = type;
}

QString ground::get_type()
{
   return type;
}



bool ground::isStair()
{
   if (type == "stair")
       return true;
   else
       return false;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//map
map::map()
{
    current_lv = 1;
    current_map = board[current_lv];
}

QVector<QVector<ground>> map::get_map(int lv)
{
   return board[lv];
}

QSize map::get_block_size()
{
    QSize size(block_Height,block_Width);
    return size;
}

int map::ratio_between_width()
{
    return Width/block_Width;
}// return the corresponding ratio between position on board and on screen of the width

int map::ratio_between_height()
{
    return Width/block_Width;
}// return the corresponding ratio between position on board and on screen of the height

void map::setup_brick(int i, int j)
{
    ground brick(block_Width*i,block_Height*j);
   current_map[i][j] = brick;
}

void map::setup_stair(int i, int j)
{
    stair stair(block_Width*i,block_Height*j);
    current_map[i][j] = stair;
}




void map::setup_map()
{
    current_map.resize(Width/block_Width, QVector<ground>(Height/block_Height));
    setup_brick(2,2);
    for (int i = 0;i < 10; i++)
    {
             setup_brick(i,3);
    }
    for (int j = 0;j < 20; j++)
    {
             setup_stair(11,j);
    }

    for (int i = 12;i < 20; i++)
    {

             setup_brick(i,10);
              setup_brick(i-2,14);
    }




    board[1] = current_map;

}
