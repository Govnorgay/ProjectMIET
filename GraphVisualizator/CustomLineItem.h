#pragma once

#include <QGraphicsLineItem>
#include "Scene.h"

class CustomLineItem : public QGraphicsLineItem
{
    QGraphicsTextItem* lineText = nullptr;
public:
    explicit CustomLineItem(QLineF line, QGraphicsItem *parent = Q_NULLPTR);
    void setWieght(int w){ weight = w;}
    void setLineText(QGraphicsTextItem* text){ lineText = text;}
    QGraphicsTextItem* getLineText(){ return lineText;}
private:
    int weight;
};
