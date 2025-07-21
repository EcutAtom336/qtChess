#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "chessboard.h"
#include "chessboardwidget.h"
#include <QStyle>
#include <QTimer>
#include <qmainwindow.h>
#include <qpushbutton.h>
#include <qtypes.h>
#include <qwidget.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->verticalLayoutWidget->resize(width(), height());
    chess_board = new chessboardWidget(ui->verticalLayoutWidget, chessboardWidget::boardStyle::WOOD,
                                       chessboardWidget::chessStyle::CALIFORNIA);
    chess_board->init(chessboard::mode::STANDAR);
    ui->verticalLayout->addWidget(chess_board);

    this->setCentralWidget(ui->verticalLayoutWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
