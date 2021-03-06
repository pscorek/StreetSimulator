//Author: Bogdan Shkola
//Interface for handling mouse pressing on the graphics items
#ifndef MOUSEEVENTHANDLER_H
#define MOUSEEVENTHANDLER_H

#include "../boardscene.h"
#include <QGraphicsSceneMouseEvent>
#include "../../controller/blockingqueue.h"

class BoardScene;
class IMovableItem;

class MouseEventHandler
{
public:
    MouseEventHandler() {}

    //Handles mouse pressing on the graphics items
    virtual void handlePress(QGraphicsSceneMouseEvent* event, BoardScene* scene, IMovableItem* item) = 0;
    virtual void handleMove(QGraphicsSceneMouseEvent* event, BoardScene* scene, IMovableItem* item) = 0;
    virtual void handleRelease(QGraphicsSceneMouseEvent* event, BoardScene* scene, IMovableItem* item) = 0;
};

#endif // MOUSEEVENTHANDLER_H
