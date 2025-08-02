#include "chessboardwidget.h"

#include <array>
#include <cmath>
#include <cstddef>

#include <QWidget>

#include <qassert.h>
#include <qcolor.h>
#include <qcontainerfwd.h>
#include <qdebug.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qimage.h>
#include <qlogging.h>
#include <qminmax.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpen.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qtransform.h>
#include <qtypes.h>
#include <qwidget.h>

#include "chess.h"
#include "chessboard.h"
#include "chessboardwidget.h"

qtchess::ChessboardWidget::ChessboardWidget(QWidget *parent, const QString &board_style_name,
                                            const QString &chess_style_name)
    : QWidget(parent)
{

    if (board_style_name.isEmpty())
    {
        setBoardStyle(getBoardStyleNames().at(0));
    }
    else
    {
        setBoardStyle(board_style_name);
    }

    if (chess_style_name.isEmpty())
    {
        setPieceStyle(getPieceStyleNames().at(1));
    }
    else
    {
        setPieceStyle(chess_style_name);
    }
}

void qtchess::ChessboardWidget::setBoardStyle(QString style_name)
{
    QString file_name = ":/res/board/" + style_name;

    const QStringList kMAYBE_SUFFIX = {".jpg", ".jpeg", ".png"};

    for (const QString &suffix : kMAYBE_SUFFIX)
    {
        if (board_img_.load(file_name + suffix) == true)
        {
            break;
        }
    }

    Q_ASSERT(!board_img_.isNull());

    update();
}

void qtchess::ChessboardWidget::setPieceStyle(QString style_name)
{
    for (int i = 0; i < static_cast<size_t>(Chess::Type::kCount); i++)
    {
        const QString &piece_name = Chess::kPieceNames[i];
        QString svg_file = ":/res/piece/" + style_name + "/" + piece_name + ".svg";
        piece_svgs_[i].load(svg_file);
        Q_ASSERT(piece_svgs_[i].isValid());
    }

    renderPieceImg();

    update();
}

void qtchess::ChessboardWidget::setDirection(Direction direction)
{
    direction_ = direction;
}

QStringList qtchess::ChessboardWidget::getBoardStyleNames()
{
    QStringList names = QStringList();
    auto placeholder = QDir(":/res/board/").entryList(QDir::Filter::Files, QDir::SortFlag::Name);
    for (const QString &name : std::as_const(placeholder))
    {
        if (name.contains("thumbnail"))
        {
            continue;
        }
        names.append(QFileInfo(name).completeBaseName());
    }
    Q_ASSERT(!names.isEmpty());
    return names;
}

QStringList qtchess::ChessboardWidget::getPieceStyleNames()
{
    return QDir(":/res/piece/").entryList(QDir::Filter::Dirs, QDir::SortFlag::Name);
}

void qtchess::ChessboardWidget::clear()
{
    chessboard_.clear();
    update();
}

void qtchess::ChessboardWidget::addChess(const quint8 row, const quint8 col, const enum Chess::Type type)
{
    chessboard_.addChess(row, col, type);
    update();
}

void qtchess::ChessboardWidget::removeChess(const quint8 row, const quint8 col)
{
    chessboard_.removeChess(row, col);
    update();
}

void qtchess::ChessboardWidget::init(Chessboard::Mode mode)
{
    chessboard_.init(mode);
    update();
}

void qtchess::ChessboardWidget::addChess(const Chessboard::Coordinate &coor, const enum Chess::Type t)
{
    addChess(coor.row(), coor.col(), t);
}

void qtchess::ChessboardWidget::removeChess(const Chessboard::Coordinate &coor)
{
    removeChess(coor.row(), coor.col());
}

void qtchess::ChessboardWidget::renderPieceImg()
{
    QPainter painter;

    quint16 piece_size = width() > height() ? (height() * 0.125) : (width() * 0.125);

    for (int i = 0; i < static_cast<size_t>(Chess::Type::kCount); i++)
    {
        piece_imgs_[i] = std::make_unique<QImage>(piece_size, piece_size, QImage::Format_ARGB32);
        piece_imgs_[i]->fill(Qt::transparent); // 填充透明背景，否则是垃圾值
        painter.begin(piece_imgs_[i].get());
        piece_svgs_[i].render(&painter, QRectF(0, 0, piece_size, piece_size));
        painter.end();
    }
}

qtchess::Chessboard::Coordinate qtchess::ChessboardWidget::getCoordinate(const QPoint pos)
{
    return direction_ == Direction::kForward
               ? Chessboard::Coordinate(8 - pos.y() / (height() * .125) + 1, pos.x() / (width() * .125) + 1)
               : Chessboard::Coordinate(pos.y() / (height() * .125) + 1, 8 - pos.x() / (width() * .125) + 1);
}

QRectF qtchess::ChessboardWidget::getCellRectF(Chessboard::Coordinate coor)
{
    qreal board_size = qMin(width(), height());
    qreal cell_size = board_size * .125;

    if (direction_ == Direction::kForward)
    {
        return QRectF((coor.col() - 1) * board_size * .125, (8 - coor.row()) * board_size * .125, cell_size, cell_size);
    }
    else
    {
        return QRectF((8 - coor.col()) * board_size * .125, (coor.row() - 1) * board_size * .125, cell_size, cell_size);
    }
}

void qtchess::ChessboardWidget::paintEvent(QPaintEvent *)
{
    quint32 board_size = height() > width() ? width() : height();
    quint32 cell_size = board_size * .125;
    QImage buffer = QImage(board_size, board_size, QImage::Format_ARGB32);
    QPainter painter = QPainter(&buffer);

    // 绘制棋盘到缓冲区
    painter.drawImage(rect(), board_img_);

    if (selected_)
    {
        // 绘制选择棋子效果到缓冲区
        painter.fillRect(getCellRectF(selected_coordinate_), QColor(0, 255, 0, 64));

        // 绘制棋子可达棋格指示
        if (!reachable_coordinates_.isEmpty())
        {
            for (Chessboard::Coordinate dest_coor : reachable_coordinates_)
            {
                if (chessboard_.getChess(dest_coor))
                {
                    painter.fillRect(getCellRectF(dest_coor), QColor(0, 255, 0, 127));
                }
                else
                {
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QColor(0, 255, 0, 127));
                    painter.drawEllipse(getCellRectF(dest_coor).center(), cell_size * .1, cell_size * .1);
                }
            }
        }
    }

    // 绘制棋子到缓冲区
    for (int row_in_chessboard = 1; row_in_chessboard <= 8; ++row_in_chessboard)
        for (int col_in_chessboard = 1; col_in_chessboard <= 8; ++col_in_chessboard)
        {
            Chess *p_chess = chessboard_.getChess(row_in_chessboard, col_in_chessboard);
            if (p_chess == nullptr)
            {
                continue;
            }
            painter.drawImage(getCellRectF(Chessboard::Coordinate(row_in_chessboard, col_in_chessboard)),
                              *piece_imgs_[static_cast<size_t>(p_chess->getType())].get());
        }
    painter.end();

    // 绘制缓冲区到屏幕
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawImage(0, 0, buffer);
}

void qtchess::ChessboardWidget::resizeEvent(QResizeEvent *event)
{
    // 保持widget为正方形
    QWidget::resizeEvent(event);
    qInfo() << "widget size:" << event->size();
    if (event->size().height() != event->size().width())
    {
        resize(qMin(event->size().width(), event->size().height()),
               qMin(event->size().width(), event->size().height()));
    }
    else
    {
        // 重新渲染棋子
        renderPieceImg();
    }
}

void qtchess::ChessboardWidget::mousePressEvent(QMouseEvent *event)
{
    // 记录鼠标按下棋格
    mouse_press_coordinate_ = getCoordinate(event->pos());
}

void qtchess::ChessboardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    // 释放鼠标时鼠标移出widget，直接返回
    if (event->pos().x() < 0 || event->pos().x() > width() || event->pos().y() < 0 || event->pos().y() > height())
    {
        return;
    }

    // 鼠标按下与释放不是同一棋格，直接返回
    if (getCoordinate(event->pos()) != mouse_press_coordinate_)
    {
        return;
    }

    // 鼠标按下与释放是同一棋格
    Chessboard::Coordinate current_coor = getCoordinate(event->pos());
    Chess *p_current_chess = chessboard_.getChess(current_coor);

    // 已经选择一个棋子
    if (selected_)
    {
        // 点击坐标在可达列表中
        if (reachable_coordinates_.contains(current_coor))
        {
            chessboard_.moveChess(selected_coordinate_, current_coor);
            reachable_coordinates_.clear();
            selected_ = false;
        }
        // 点击坐标不在可达列表中，且有棋子，选中新棋子
        else if (p_current_chess)
        {
            selected_coordinate_ = current_coor;
            reachable_coordinates_ = chessboard_.getReachable(selected_coordinate_);
        }
        // 点击坐标不在可达列表中，也没有棋子，取消选择
        else
        {
            selected_ = false;
        }
    }
    // 未选择棋子
    else
    {
        // 点按的棋格为空，直接返回
        if (p_current_chess == nullptr)
        {
            return;
        }

        // 点按的棋格不为空，选择该棋子
        selected_ = true;
        selected_coordinate_ = current_coor;
        reachable_coordinates_ = chessboard_.getReachable(selected_coordinate_);
    }
    update();
}

void qtchess::ChessboardWidget::showEvent(QShowEvent *event)
{
    renderPieceImg();
}
