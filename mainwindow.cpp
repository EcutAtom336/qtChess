#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "chessboard.h"
#include "chessboardwidget.h"
#include "newgamedialog.h"
#include <QStyle>
#include <QTimer>
#include <qaction.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qtypes.h>
#include <qwidget.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->verticalLayoutWidget->resize(width(), height());
    chess_board = new chessboardWidget(ui->verticalLayoutWidget, chessboardWidget::boardStyle::WOOD,
                                       chessboardWidget::chessStyle::CALIFORNIA);
    ui->verticalLayout->addWidget(chess_board);

    this->setCentralWidget(ui->verticalLayoutWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered()
{
    qInfo("action open triggered.");
}

void MainWindow::on_action_new_triggered()
{
    newGameDialog new_game_dialog(this);

    connect(&new_game_dialog, &newGameDialog::on_new_game_info_confirm, this,
            [this](const newGameDialog::newGameInfo &info) -> void {
                chess_board->init(chessboard::mode::STANDAR);
                if (info.game_role == newGameDialog::gameRole::BLACK)
                {
                    chess_board->setRollback(true);
                }
                else
                {
                    chess_board->setRollback(false);
                }
            });

    new_game_dialog.exec();
}

void MainWindow::on_action_setting_triggered()
{
    qInfo("action setting triggered.");
}

void MainWindow::on_action_undo_triggered()
{
    qInfo("action undo triggered.");
}

void MainWindow::on_action_save_triggered()
{
    qInfo("action save triggered.");
}
