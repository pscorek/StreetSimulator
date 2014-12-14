#ifndef BOARDSCENE_H
#define BOARDSCENE_H

#include <QGraphicsScene>

namespace Ui {
    class BoardScene : public QGraphicsScene
    {
        Q_OBJECT
    public:
        explicit BoardScene();

        void updateBoardSize(int size);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    protected:

    signals:

    public slots:

    private:
        int borderSize;
        float shiftSize;
        int boardSize;

    };
}
#endif // BOARDSCENE_H