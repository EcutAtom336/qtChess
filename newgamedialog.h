#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>

#include <qcontainerfwd.h>
#include <qwindowdefs.h>

#include "chessboard.h"

namespace Ui
{

class newGameDialog;

}

namespace qtchess
{

class NewGameDialog : public QDialog
{
    Q_OBJECT

  public:
    enum class GameRole
    {
        kWhite,
        kBlack,
    };

    enum class GameDifficulty
    {
        kLevel1 = 1,
        kLevel2,
        kLevel3,
        kLevel4,
        kLevel5,
        kLevel6,
        kLevel7,
        kLevel8,
        kLevel9,
        kLevel10,
    };

    typedef struct
    {
        GameRole game_role;
        Chessboard::Mode game_mode;
        GameDifficulty difficulty;
    } NewGameInfo;

    explicit NewGameDialog(QWidget *parent = nullptr);
    ~NewGameDialog();

  private:
    Ui::newGameDialog *ui_;

  private slots:
    void on_pushButton_start_as_white_released();
    void on_pushButton_start_as_random_released();
    void on_pushButton_start_as_black_released();

  signals:
    void on_new_game_info_confirm(const qtchess::NewGameDialog::NewGameInfo &info);
};

} // namespace qtchess

#endif // NEWGAMEDIALOG_H
