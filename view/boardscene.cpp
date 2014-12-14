#include "boardscene.h"
#include "boardcell.h"
#include <iostream>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QWidget>
#include "../controller/blockingqueue.h"
#include "../common/events/streetfieldaddedevent.h"
#include "../common/events/streetfieldremovedevent.h"

namespace Ui {
    BoardScene::BoardScene() : QGraphicsScene()
    {
        borderSize = 300;
    }

    void BoardScene::updateBoardSize(int size) {
        this->clear();
        this->boardSize = size;
        QPen noPen(Qt::NoPen);
        QBrush noBrush(Qt::NoBrush);

        this->addRect(0, 0, borderSize, borderSize, noPen, noBrush);
        shiftSize = std::min(width(), height()) / size;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                BoardCell* boardCell = new BoardCell(0, 0, shiftSize, shiftSize);
                boardCell->setCoordinates(i, j);
                boardCell->setPos(i * shiftSize, j * shiftSize);
                this->addItem(boardCell);
            }
        }
    }

    void BoardScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
        BoardCell *item = (BoardCell *)this->itemAt(event->scenePos(), QTransform());
        if (item)
        {
            if (event->button() == Qt::LeftButton) {
                item->setChecked(true);
                BlockingEventQueue::getInstance().push(new StreetFieldAddedEvent(item->getCoordinates()));
            } else {
                item->setChecked(false);
                BlockingEventQueue::getInstance().push(new StreetFieldRemovedEvent(item->getCoordinates()));
            }
            item->update();
        }
    }

    void BoardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    }

    void BoardScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    }
}
