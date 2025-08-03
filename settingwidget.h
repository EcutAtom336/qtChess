#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QDialog>

#include <qaction.h>
#include <qlist.h>
#include <qpushbutton.h>
#include <qsettings.h>
#include <qstandarditemmodel.h>

#include "ui_settingwidget.h"

namespace Ui
{

class SettingWidget;

}

namespace qtchess
{

class SettingWidget : public QDialog
{
    Q_OBJECT

  public:
    explicit SettingWidget(QSettings &settings, QWidget *parent = nullptr);
    ~SettingWidget();

  private:
    Ui::SettingWidget *ui_;
    QSettings &settings_;

  signals:
    void renew();
};

} // namespace qtchess

#endif // SETTINGWIDGET_H
