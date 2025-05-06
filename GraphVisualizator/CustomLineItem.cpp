#include "CustomLineItem.h"

CustomLineItem::CustomLineItem(QLineF line, QGraphicsItem *parent)
    :QGraphicsLineItem(line, parent)
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    setPen(pen);
}


