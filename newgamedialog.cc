#include "newgamedialog.h"

#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qlogging.h>
#include <qpushbutton.h>
#include <qrandom.h>

#include "ui_newgamedialog.h"

#include "chessboard.h"

qtchess::NewGameDialog::NewGameDialog(QWidget *parent) : QDialog(parent), ui_(new Ui::newGameDialog)
{
    ui_->setupUi(this);
}

qtchess::NewGameDialog::~NewGameDialog()
{
    delete ui_;
}

void qtchess::NewGameDialog::on_pushButton_start_as_white_released()
{
    NewGameInfo info = {
        .game_role = GameRole::kWhite,
        .game_mode = Chessboard::Mode::kStandard,
        .difficulty = static_cast<GameDifficulty>(ui_->spinBox_difficulty->value()),
    };
    emit on_new_game_info_confirm(info);
    qInfo() << "start as white role.";
    this->close();
}

void qtchess::NewGameDialog::on_pushButton_start_as_random_released()
{
    NewGameInfo info = {
        .game_role = static_cast<GameRole>(QRandomGenerator::global()->bounded(2)),
        .game_mode = Chessboard::Mode::kStandard,
        .difficulty = static_cast<GameDifficulty>(ui_->spinBox_difficulty->value()),
    };
    emit on_new_game_info_confirm(info);
    qInfo() << "start as random role:" << (info.game_role == GameRole::kWhite ? "WHITE" : "BLACK");
    this->close();
}

void qtchess::NewGameDialog::on_pushButton_start_as_black_released()
{
    NewGameInfo info = {
        .game_role = GameRole::kBlack,
        .game_mode = Chessboard::Mode::kStandard,
        .difficulty = static_cast<GameDifficulty>(ui_->spinBox_difficulty->value()),
    };
    emit on_new_game_info_confirm(info);
    qInfo() << "start as black role.";
    this->close();
}
