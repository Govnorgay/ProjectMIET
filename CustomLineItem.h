#pragma once

#include <QGraphicsLineItem>
#include "Scene.h"

class CustomLineItem : public QGraphicsLineItem
{
public:
    explicit CustomLineItem(QLineF line, QGraphicsItem *parent = Q_NULLPTR);
};
