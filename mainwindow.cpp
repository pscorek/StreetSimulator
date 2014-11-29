#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "view/boardscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    boardScene = new BoardScene();
    ui->graphicsView->setScene(boardScene);
    this->setWindowTitle("Editor");
    this->showMaximized();

    updateBoardSize();

    // initialize signals-slots
    buttons.append(ui->streetButton);
    buttons.append(ui->removeStreetButton);
    buttons.append(ui->movableObjectButton);
    buttons.append(ui->cameraButton);

    connect(ui->sizeButton, SIGNAL(clicked()), this, SLOT(updateButtons()));
    connect(ui->sizeButton, SIGNAL(pressed()), this, SLOT(updateBoardSize()));

    connect(ui->streetButton, SIGNAL(pressed()), this, SLOT(updateButtons()));
    connect(ui->removeStreetButton, SIGNAL(pressed()), this, SLOT(updateButtons()));
    connect(ui->movableObjectButton, SIGNAL(pressed()), this, SLOT(updateButtons()));
    connect(ui->cameraButton, SIGNAL(pressed()), this, SLOT(updateButtons()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBoardSize() {
    boardScene->updateBoardSize(ui->boardSizeSpinBox->value());
}

void MainWindow::updateButtons() {
    for (QPushButton* button : buttons) {
        button->setChecked(false);
    }
}

//void MainWindow::setBoardSize() {
//    boardScene = new BoardScene();

//    boardScene->addRect(QRect(QPoint(0, 0), sceneSize));

//    int shiftsNumber = ui->boardSizeSpinBox->value();
//    float shiftSize = boardScene->width() / shiftsNumber;
//    for(int i = 1; i < shiftsNumber; ++i) {
//        boardScene->addLine(i * shiftSize, 0, i * shiftSize, 600);
//        boardScene->addLine(0, i * shiftSize, 600, i * shiftSize);
//    }

//    ui->graphicsView->setScene(boardScene);
//}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    boardScene->setSceneRect(boardScene->sceneRect());
    ui->graphicsView->fitInView(boardScene->sceneRect(), Qt::KeepAspectRatio);
}
