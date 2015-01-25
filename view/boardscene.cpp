#include "../view/boardscene.h"
#include "boardcell.h"
#include "items/truckcaritem.h"
#include "items/passengercaritem.h"
#include "items/destinationitem.h"
#include "items/cameraitem.h"
#include <iostream>
#include <vector>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QWidget>
#include "../controller/blockingqueue.h"
#include "../common/events/streetfieldaddedevent.h"
#include "../common/events/streetfieldremovedevent.h"

BoardScene::BoardScene() : QGraphicsScene()
{
    std::cout << "BoardScene()" << std::endl;
    boardSizeInPixels = 300;
    activeMenuItem_ = NULL;
    lastSelectedItem_ = NULL;
}

BoardScene::~BoardScene() {
    std::cout << "~BoardScene()" << std::endl;
}

void BoardScene::updateBoardSize(int size) {
    this->clear();
    this->boardSize = size;
    QPen noPen(Qt::NoPen);
    QBrush noBrush(Qt::NoBrush);

    this->addRect(0, 0, boardSizeInPixels + 50, boardSizeInPixels, noPen, noBrush); // change 50 to a variable
    shiftSize = std::min(width(), height()) / size;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            BoardCell* boardCell = new BoardCell(0, 0, shiftSize, shiftSize);
            boardCell->setCoordinates(i, j);
            boardCell->setPos(i * shiftSize, j * shiftSize);
            this->addItem(boardCell);
        }
    }

    std::vector<IMovableItem*> menuItems;
    menuItems.push_back(new TruckCarItem(QRectF(shiftSize / 4, shiftSize / 4, shiftSize / 2, shiftSize / 2)));
    menuItems.push_back(new PassengerCarItem(QRectF(shiftSize / 4, shiftSize / 4, shiftSize / 2, shiftSize / 2)));
    menuItems.push_back(new CameraItem(QRectF(shiftSize * 3 / 8, shiftSize * 3 / 8, shiftSize / 8, shiftSize / 8)));

    foreach(IMovableItem* availableItem, menuItems) {
        this->addItem(availableItem);
        availableItem->setPos(QPointF(boardSizeInPixels, shiftSize * availableItem->getTrafficObjectType()));
        availableItem->setFlag(QGraphicsItem::ItemIsMovable);
    }
}

void BoardScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem *item = this->itemAt(event->scenePos(), QTransform());
    if (item) {
        if(item->flags().testFlag(QGraphicsItem::ItemIsMovable)) {
            if (isInsideBoard(event->scenePos())) {
                activeMenuItem_ = (IMovableItem*)item;
            } else {
                activeMenuItem_ = ((IMovableItem*)item)->clone();
                this->addItem(activeMenuItem_);
                activeMenuItem_->setPos(QPointF(boardSizeInPixels, shiftSize * activeMenuItem_->getTrafficObjectType()));
                activeMenuItem_->setFlag(QGraphicsItem::ItemIsMovable);
                std::cout << "Created" << std::endl;
            }
        }
        else {
            if (event->button() == Qt::LeftButton) {
                ((BoardCell*)item)->setChecked(true);
                BlockingEventQueue::getInstance().push(new StreetFieldAddedEvent(((BoardCell*)item)->getCoordinates()));
            } else {
                ((BoardCell*)item)->setChecked(false);
                BlockingEventQueue::getInstance().push(new StreetFieldRemovedEvent(((BoardCell*)item)->getCoordinates()));
            }
            item->update();
        }
    }
}

void BoardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (activeMenuItem_ && activeMenuItem_->flags().testFlag(QGraphicsItem::ItemIsMovable)) {
        activeMenuItem_->getMouseEventHandler()->handleMove(event, this, activeMenuItem_);
    }
}

void BoardScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (activeMenuItem_ && activeMenuItem_->flags().testFlag(QGraphicsItem::ItemIsMovable)) {
        activeMenuItem_->getMouseEventHandler()->handleRelease(event, this, activeMenuItem_); //TODO check for left/right click
        if (isInsideBoard(event->scenePos())) {
            activeMenuItem_->setSelected(true);
            if (activeMenuItem_ != lastSelectedItem_) {
                if (lastSelectedItem_ != NULL) {
                    lastSelectedItem_->setSelected(false);
                }
            }
        } else {
            if (lastSelectedItem_ != NULL) {
                lastSelectedItem_->setSelected(false);
            }
        }
        lastSelectedItem_ = activeMenuItem_;
        activeMenuItem_ = NULL;
    }
}


bool BoardScene::isInsideBoard(const QPointF& pos) {
    if (pos.x() >= 0 && pos.x() < boardSizeInPixels && pos.y() >= 0 && pos.y() < boardSizeInPixels) {
        return true;
    }
    return false;
}

bool BoardScene::isInsideScene(const QPointF& pos) {
    if (pos.x() >= 0 && pos.x() < boardSizeInPixels + 1.5 * shiftSize &&
            pos.y() >= 0 && pos.y() < boardSizeInPixels) {
        return true;
    }
    return false;
}

QPointF BoardScene::getDiscretePosition(const QPointF& point) {
    int indexX = point.x() / shiftSize;
    int indexY = point.y() / shiftSize;
    return QPointF(indexX * shiftSize, indexY * shiftSize);
}

Position BoardScene::getDiscreteCoordinates(const QPointF& point) {
    return Position(point.x() / shiftSize, point.y() / shiftSize);
}

int BoardScene::getActiveCameraId() {
    CameraItem* selectedCamera = dynamic_cast<CameraItem*>(lastSelectedItem_);
    if (selectedCamera != NULL) {
        return selectedCamera->getId();
    }
    return -1;
}
