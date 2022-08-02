#include"Bullet.h"
#include"Enemy.h"
#include<QTimer>
#include<QGraphicsScene>

#include "Game.h"

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent):QObject(),QGraphicsPixmapItem(parent)
{

setPixmap(QPixmap(":/images/bullet.png"));
    QTimer * timer =new QTimer();
    //connecting signal and slot

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Bullet::move()
{
    // if bullet collides with enemy, destroy both
       QList<QGraphicsItem *> colliding_items = collidingItems();
       for (int i = 0, n = colliding_items.size(); i < n; ++i){
           if (typeid(*(colliding_items[i])) == typeid(Enemy)){
                game->score->increase();
               // remove them both
               scene()->removeItem(colliding_items[i]);
               scene()->removeItem(this);
               // delete them both
               delete colliding_items[i];
               delete this;
               return;
           }
       }
setPos(x(),y()-10);

    if(pos().y() <0)
    {
        scene()->removeItem(this);
        delete this;

    }
}
