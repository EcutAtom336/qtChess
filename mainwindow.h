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

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  protected:
  private slots:
    void on_action_open_triggered();
    void on_action_new_triggered();
    void on_action_setting_triggered();
    void on_action_undo_triggered();
    void on_action_save_triggered();

  private:
    Ui::MainWindow *ui;
    chessboardWidget *chess_board;

    void on_menu_new_clicked();
};
#endif // MAINWINDOW_H
