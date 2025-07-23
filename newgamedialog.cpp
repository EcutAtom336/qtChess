#include "newgamedialog.h"
#include "chessboard.h"
#include "ui_newgamedialog.h"
#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qlogging.h>
#include <qpushbutton.h>
#include <qrandom.h>

newGameDialog::newGameDialog(QWidget *parent) : QDialog(parent), ui(new Ui::newGameDialog)
{
    ui->setupUi(this);
}

newGameDialog::~newGameDialog()
{
    delete ui;
}

void newGameDialog::on_pushButton_start_as_white_released()
{
    newGameInfo info = {
        .game_role = gameRole::WHITE,
        .game_mode = chessboard::mode::STANDAR,
        .difficulty = static_cast<gameDifficulty>(ui->spinBox_difficulty->value()),
    };
    emit on_new_game_info_confirm(info);
    qInfo() << "start as white role.";
    this->close();
}

void newGameDialog::on_pushButton_start_as_random_released()
{
    newGameInfo info = {
        .game_role = static_cast<gameRole>(QRandomGenerator::global()->bounded(2)),
        .game_mode = chessboard::mode::STANDAR,
        .difficulty = static_cast<gameDifficulty>(ui->spinBox_difficulty->value()),
    };
    emit on_new_game_info_confirm(info);
    qInfo() << "start as random role:" << (info.game_role == gameRole::WHITE ? "WHITE" : "BLACK");
    this->close();
}

void newGameDialog::on_pushButton_start_as_black_released()
{
    newGameInfo info = {
        .game_role = gameRole::BLACK,
        .game_mode = chessboard::mode::STANDAR,
        .difficulty = static_cast<gameDifficulty>(ui->spinBox_difficulty->value()),
    };
    emit on_new_game_info_confirm(info);
    qInfo() << "start as black role.";
    this->close();
}
