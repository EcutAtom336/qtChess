#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "chess.h"
#include "chessboard.h"
#include "chessboardwidget.h"
#include <QStyle>
#include <QTimer>
#include <qpushbutton.h>
#include <qwidget.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect(ui->action_open_chess);

    chess_board =
        new chessboardWidget(this, chessboardWidget::boardStyle::WOOD, chessboardWidget::chessStyle::CALIFORNIA);

    chess_board->init(chessboard::mode::STANDAR);
    // chess_board->addChess(chessboard::cell::a2, chess::type::WHITE_PAWN);
    // chess_board->addChess(chessboard::cell::a3, chess::type::WHITE_KING);
    // chess_board->addChess(chessboard::cell::b2, chess::type::WHITE_ROOK);
    // chess_board->addChess(chessboard::cell::h7, chess::type::BLACK_PAWN);

    setCentralWidget(chess_board);
}

MainWindow::~MainWindow()
{
    delete ui;
}
