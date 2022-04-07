#include "character.h"

Character::Character()
{
    QPixmap pixmap(":/images/yourchar.png");
    char_img = pixmap;
    QSize s(50,50);
    size = s;
    step = 10;
    x = 0;
    y = 0;
}

QPointF Character::get_pos() const
{
    QPointF pos(x,y);
    return pos;
}

void Character::set_pos(float x, float y)
{
    this->x = x;
    this->y = y;
}

QPixmap Character::getpixmap()
{
    return char_img;
}

QSize Character::getSize()
{
    return size;
}

void Character::setSize(int h, int w)
{
    size.setHeight(h);
    size.setWidth(w);
}

int Character::get_walkstepdis()
{
    return step;
}
