#include "mainwindow.h"

#include <QStyle>

#include <qaction.h>
#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qsettings.h>
#include <qtypes.h>
#include <qvariant.h>
#include <qwidget.h>

#include "settingwidget.h"
#include "ui_mainwindow.h"

#include "chessboard.h"
#include "chessboardwidget.h"
#include "newgamedialog.h"

namespace qtchess
{

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui_(new Ui::MainWindow), settings_("Atom336", "qtchess")
{
    ui_->setupUi(this);

    ui_->verticalLayoutWidget->resize(width(), height());

    QStringList board_style_names = ChessboardWidget::getBoardStyleNames();
    QStringList piece_style_names = ChessboardWidget::getPieceStyleNames();
    QString board_style_name = settings_.value("style/board", board_style_names.at(0)).toString();
    QString piece_style_name = settings_.value("style/piece", piece_style_names.at(0)).toString();

    chess_board_ = new ChessboardWidget(ui_->verticalLayoutWidget, board_style_name, piece_style_name);
    ui_->verticalLayout->addWidget(chess_board_);
    this->setCentralWidget(ui_->verticalLayoutWidget);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::on_action_open_triggered()
{
    qInfo("action open triggered.");
}

void MainWindow::on_action_new_triggered()
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

void MainWindow::on_action_setting_triggered()
{
    qInfo("action setting triggered.");
    SettingWidget setting_widget(settings_, this);
    connect(&setting_widget, &SettingWidget::renew, this, [this]() -> void {
        chess_board_->setBoardStyle(settings_.value("style/board").toString());
        chess_board_->setPieceStyle(settings_.value("style/piece").toString());
    });
    setting_widget.exec();
}

void MainWindow::on_action_undo_triggered()
{
    qInfo("action undo triggered.");
}

void MainWindow::on_action_save_triggered()
{
    qInfo("action save triggered.");
}

} // namespace qtchess
