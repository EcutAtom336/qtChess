#include "mainwindow.h"

#include <QStyle>

#include <qaction.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qtypes.h>
#include <qwidget.h>

#include "ui_mainwindow.h"

#include "chessboard.h"
#include "chessboardwidget.h"
#include "newgamedialog.h"

qtchess::MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    ui_->verticalLayoutWidget->resize(width(), height());
    chess_board_ = new ChessboardWidget(ui_->verticalLayoutWidget, ChessboardWidget::BoardStyle::kWood,
                                        ChessboardWidget::ChessStyle::kCalifornia);
    ui_->verticalLayout->addWidget(chess_board_);

    this->setCentralWidget(ui_->verticalLayoutWidget);
}

qtchess::MainWindow::~MainWindow()
{
    delete ui_;
}

void qtchess::MainWindow::on_action_open_triggered()
{
    qInfo("action open triggered.");
}

void qtchess::MainWindow::on_action_new_triggered()
{
    NewGameDialog new_game_dialog(this);

    connect(&new_game_dialog, &NewGameDialog::on_new_game_info_confirm, this,
            [this](const NewGameDialog::NewGameInfo &info) -> void {
                chess_board_->init(Chessboard::Mode::kStandard);
                if (info.game_role == NewGameDialog::GameRole::kWhite)
                {
                    chess_board_->setDirection(ChessboardWidget::Direction::kForward);
                }
                else
                {
                    chess_board_->setDirection(ChessboardWidget::Direction::kBackword);
                }
            });

    new_game_dialog.exec();
}

void qtchess::MainWindow::on_action_setting_triggered()
{
    qInfo("action setting triggered.");
}

void qtchess::MainWindow::on_action_undo_triggered()
{
    qInfo("action undo triggered.");
}

void qtchess::MainWindow::on_action_save_triggered()
{
    qInfo("action save triggered.");
}
