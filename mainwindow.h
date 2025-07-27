#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chessboardwidget.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{

class MainWindow;

}
QT_END_NAMESPACE

namespace qtchess
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow *ui_;
    ChessboardWidget *chess_board_;

    void on_menu_new_clicked();

  private slots:
    void on_action_open_triggered();
    void on_action_new_triggered();
    void on_action_setting_triggered();
    void on_action_undo_triggered();
    void on_action_save_triggered();
};

}; // namespace qtchess

#endif // MAINWINDOW_H
