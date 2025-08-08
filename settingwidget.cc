#include "settingwidget.h"

#include <QPushButton>

#include <qabstractitemmodel.h>
#include <qaction.h>
#include <qcontainerfwd.h>
#include <qdebug.h>
#include <qdir.h>
#include <qicon.h>
#include <qimage.h>
#include <qlistview.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qsettings.h>
#include <qsize.h>
#include <qstandarditemmodel.h>
#include <qtypes.h>

#include "ui_settingwidget.h"

#include "chessboardwidget.h"

namespace qtchess
{

SettingWidget::SettingWidget(QSettings &settings, QWidget *parent)
    : QDialog(parent), ui_(new Ui::SettingWidget), settings_(settings)
{
    ui_->setupUi(this);
    setWindowTitle("设置");

    connect(ui_->pushButton_confirm, &QPushButton::clicked, this, [this](bool checked) -> void {
        qDebug() << "confirm";

        QModelIndex index = ui_->listView_chessboard_style->currentIndex();
        QString board_style_name = index.data().toString();
        if (!board_style_name.isEmpty() && settings_.value("style/board").toString() != board_style_name)
        {
            settings_.setValue("style/board", board_style_name);
        }

        index = ui_->listView_piece_style->currentIndex();
        QString piece_style_name = index.data().toString();
        if (!piece_style_name.isEmpty())
        {
            settings_.setValue("style/piece", piece_style_name);
        }

        emit renew();
        close();
    });

    connect(ui_->pushButton_apply, &QPushButton::clicked, this, [this](bool checked) -> void {
        qDebug() << "apply";

        QModelIndex index = ui_->listView_chessboard_style->currentIndex();
        QString board_style_name = index.data().toString();
        if (!board_style_name.isEmpty())
        {
            settings_.setValue("style/board", board_style_name);
        }

        index = ui_->listView_piece_style->currentIndex();
        QString piece_style_name = index.data().toString();
        if (!piece_style_name.isEmpty())
        {
            settings_.setValue("style/piece", piece_style_name);
        }

        emit renew();
    });

    connect(ui_->pushButton_cancel, &QPushButton::clicked, this, [this](bool checked) -> void {
        qDebug() << "cancel";
        close();
    });

    // 填充棋盘样式listview

    // 获取棋盘样式名
    const QStringList kBoardStyleNames = ChessboardWidget::getBoardStyleNames();
    // 原棋盘样式名
    QString style_name = settings_.value("style/board", kBoardStyleNames[0]).toString();
    QModelIndex current_index;
    quint8 i = 1;
    QStandardItemModel *board_style_name_items_model = new QStandardItemModel(this);
    for (const QString &name : kBoardStyleNames)
    {
        QStandardItem *item =
            new QStandardItem(QIcon(QPixmap::fromImage(ChessboardWidget::getBoardStylePreviewImage(name))), name);
        item->setSizeHint(QSize(150, 75));
        item->setEditable(false);
        board_style_name_items_model->setItem(i++, item);
        if (style_name == name || i == 1)
        {
            current_index = board_style_name_items_model->indexFromItem(item);
        }
    }
    ui_->listView_chessboard_style->setModel(board_style_name_items_model);
    ui_->listView_chessboard_style->setViewMode(QListView::ViewMode::IconMode);
    ui_->listView_chessboard_style->setCurrentIndex(current_index);

    // 填充棋子样式listview

    // 获取棋子样式名
    const QStringList kPieceStyleNames = ChessboardWidget::getPieceStyleNames();
    // 原棋子样式名
    style_name = settings_.value("style/piece", kPieceStyleNames[0]).toString();
    i = 1;
    QStandardItemModel *piece_style_name_item_model = new QStandardItemModel(this);
    for (const QString &name : kPieceStyleNames)
    {
        QStandardItem *item =
            new QStandardItem(QIcon(QPixmap::fromImage(ChessboardWidget::getPieceStylePreviewImage(name, 50))), name);
        item->setSizeHint(QSize(150, 75));
        item->setEditable(false);
        piece_style_name_item_model->setItem(i++, item);
        if (style_name == name || i == 1)
        {
            current_index = piece_style_name_item_model->indexFromItem(item);
        }
    }
    ui_->listView_piece_style->setModel(piece_style_name_item_model);
    ui_->listView_piece_style->setViewMode(QListView::ViewMode::IconMode);
    ui_->listView_piece_style->setCurrentIndex(current_index);
}

SettingWidget::~SettingWidget()
{
    delete ui_;
}

} // namespace qtchess
