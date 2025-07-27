#include "mainwindow.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QLocale>
#include <QMenu>
#include <QTranslator>
#include <QVBoxLayout>

#include <qboxlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qnamespace.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "qtChess_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            app.installTranslator(&translator);
            break;
        }
    }

    qtchess::MainWindow w;
    w.show();

    return app.exec();
}
