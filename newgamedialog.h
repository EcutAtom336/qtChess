#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include "chessboard.h"
#include <QDialog>
#include <qcontainerfwd.h>
#include <qwindowdefs.h>

namespace Ui
{

class newGameDialog;
}

class newGameDialog : public QDialog
{
    Q_OBJECT

  public:
    enum class gameRole
    {
        WHITE,
        BLACK,
    };
    enum class gameDifficulty
    {
        LEVEL1 = 1,
        LEVEL2,
        LEVEL3,
        LEVEL4,
        LEVEL5,
        LEVEL6,
        LEVEL7,
        LEVEL8,
        LEVEL9,
        LEVEL10,
    };

    typedef struct
    {
        gameRole game_role;
        chessboard::mode game_mode;
        gameDifficulty difficulty;
    } newGameInfo;

    explicit newGameDialog(QWidget *parent = nullptr);
    ~newGameDialog();

  private:
    Ui::newGameDialog *ui;

  private slots:
    void on_pushButton_start_as_white_released();
    void on_pushButton_start_as_random_released();
    void on_pushButton_start_as_black_released();

  signals:
    void on_new_game_info_confirm(const newGameDialog::newGameInfo &info);
};

#endif // NEWGAMEDIALOG_H
