#include "chessboardwidget.h"
#include "chess.h"
#include "chessboard.h"

#include <QWidget>
#include <array>
#include <cmath>
#include <cstddef>
#include <memory>
#include <qcolor.h>
#include <qcontainerfwd.h>
#include <qdebug.h>
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

const std::array<QString, static_cast<size_t>(chessboardWidget::boardStyle::COUNT)>
    chessboardWidget::BOARD_STYLE_FILE_NAMES = []() {
        std::array<QString, static_cast<size_t>(chessboardWidget::boardStyle::COUNT)> array;
        array[static_cast<size_t>(chessboardWidget::boardStyle::BLUE)] = "blue.png";
        array[static_cast<size_t>(chessboardWidget::boardStyle::BLUE2)] = "blue2.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::BLUE3)] = "blue3.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::BLUE_MARBLLE)] = "blue-marble.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::BROWN)] = "brown.png";
        array[static_cast<size_t>(chessboardWidget::boardStyle::CANVAS2)] = "canvas2.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::GREEN)] = "green.png";
        array[static_cast<size_t>(chessboardWidget::boardStyle::GREEN_PLASTIC)] = "green-plastic.png";
        array[static_cast<size_t>(chessboardWidget::boardStyle::GREY)] = "grey.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::HORSEY)] = "horsey.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::IC)] = "ic.png";
        array[static_cast<size_t>(chessboardWidget::boardStyle::LEATHER)] = "leather.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::MAPLE)] = "maple.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::MAPLE2)] = "maple2.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::MARBLE)] = "marble.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::METAL)] = "metal.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::OLIVE)] = "olive.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::PINK_PYRAMID)] = "pink-pyramid.png";
        array[static_cast<size_t>(chessboardWidget::boardStyle::PURPLE)] = "purple.png";
        array[static_cast<size_t>(chessboardWidget::boardStyle::PURPLE_DIAG)] = "purple-diag.png";
        array[static_cast<size_t>(chessboardWidget::boardStyle::WOOD)] = "wood.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::WOOD2)] = "wood2.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::WOOD3)] = "wood3.jpg";
        array[static_cast<size_t>(chessboardWidget::boardStyle::WOOD4)] = "wood4.jpg";
        return array;
    }();

const std::array<QString, static_cast<size_t>(chessboardWidget::chessStyle::COUNT)>
    chessboardWidget::PIECE_STYLE_FLODER_NAMES = []() {
        std::array<QString, static_cast<size_t>(chessboardWidget::chessStyle::COUNT)> array;
        array[static_cast<size_t>(chessboardWidget::chessStyle::ALPHA)] = "alpha/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::ANARCANDY)] = "anarcandy/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::CALIENTE)] = "caliente/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::CALIFORNIA)] = "california/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::CARDINAL)] = "cardinal/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::CBURNETT)] = "cburnett/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::CELTIC)] = "celtic/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::CHESS7)] = "chess7/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::CHESSNUT)] = "chessnut/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::COMPANION)] = "companion/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::COOKE)] = "cooke/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::DUBROVNY)] = "dubrovny/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::FANTASY)] = "fantasy/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::FIRI)] = "firi/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::FRESCA)] = "fresca/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::GIOCO)] = "gioco/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::GOVERNOR)] = "governor/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::HORSEY)] = "horsey/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::ICPIECES)] = "icpieces/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::KIWEN_SUWI)] = "kiwen-suwi/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::KOSAL)] = "kosal/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::LEIPZIG)] = "leipzig/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::LETTER)] = "letter/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::MAESTRO)] = "maestro/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::MERIDA)] = "merida/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::MONARCHY)] = "monarchy/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::MPCHESS)] = "mpchess/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::PIROUETTI)] = "pirouetti/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::PIXEL)] = "pixel/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::REILLYCRAIG)] = "reillycraig/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::RHOSGFX)] = "rhosgfx/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::RIOHACHA)] = "riohacha/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::SHAPES)] = "shapes/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::SPATIAL)] = "spatial/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::STAUNTY)] = "staunty/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::TATIANA)] = "tatiana/";
        array[static_cast<size_t>(chessboardWidget::chessStyle::XKCDM)] = "xkcd/";
        return array;
    }();

chessboardWidget::chessboardWidget(QWidget *parent, boardStyle board_style, chessStyle chess_style)
{
    this->setBoardStyle(board_style);
    this->setPieceStyle(chess_style);
}

void chessboardWidget::setBoardStyle(boardStyle style)
{
    const QString BOARD_RES_PREFIX = "/";
    const QString BOARD_RES_PATH = "res/board/";

    if (style >= boardStyle::COUNT)
    {
        qWarning("invalid board style.");
        return;
    }

    QString file = ":" + BOARD_RES_PREFIX + BOARD_RES_PATH + BOARD_STYLE_FILE_NAMES[static_cast<size_t>(style)];

    if (board_img.load(file) == false)
    {
        qWarning("load chessboard image fail.");
    }

    update();
}

void chessboardWidget::setPieceStyle(chessStyle style)
{
    const QString PIECE_RES_PREFIX = "/";
    const QString PIECE_RES_PATH = "res/piece/";

    if (style >= chessStyle::COUNT)
    {
        qWarning("invalid piece style.");
        return;
    }

    QString path = ":" + PIECE_RES_PREFIX + PIECE_RES_PATH + PIECE_STYLE_FLODER_NAMES[static_cast<size_t>(style)];

    reloadPieceSvg(path);
    renderPieceImg();

    update();
}

void chessboardWidget::clear()
{
    chessboard::clear();
    update();
}

void chessboardWidget::addChess(const quint8 row, const quint8 col, const enum chess::type type)
{
    chessboard::addChess(row, col, type);
    update();
}

void chessboardWidget::removeChess(const quint8 row, const quint8 col)
{
    chessboard::removeChess(row, col);
    update();
}

void chessboardWidget::init(mode mode)
{
    chessboard::init(mode);
    update();
}

void chessboardWidget::setRollback(bool new_state)
{
    rollback = new_state;
}

void chessboardWidget::addChess(const coordinate &coor, const enum chess::type t)
{
    addChess(coor.row(), coor.col(), t);
}

void chessboardWidget::removeChess(const coordinate &coor)
{
    removeChess(coor.row(), coor.col());
}

void chessboardWidget::reloadPieceSvg(QString path)
{
    for (int i = 0; i < static_cast<size_t>(chess::type::COUNT); i++)
    {
        const QString &piece_name = chess::PIECE_NAMES[i];
        QString svg_file = path + piece_name + ".svg";
        piece_svg_array[i].load(svg_file);
        Q_ASSERT(piece_svg_array[i].isValid());
    }
}

void chessboardWidget::renderPieceImg()
{
    QPainter painter;

    quint16 piece_size = width() > height() ? (height() * 0.125) : (width() * 0.125);

    for (int i = 0; i < static_cast<size_t>(chess::type::COUNT); i++)
    {
        piece_img_array[i] = std::make_unique<QImage>(piece_size, piece_size, QImage::Format_ARGB32);
        piece_img_array[i]->fill(Qt::transparent); // 填充透明背景，否则是垃圾值
        painter.begin(piece_img_array[i].get());
        piece_svg_array[i].render(&painter, QRectF(0, 0, piece_size, piece_size));
        painter.end();
    }
}

chessboard::coordinate chessboardWidget::getCoordinate(const QPoint pos)
{
    return rollback ? chessboard::coordinate(pos.y() / (height() * .125) + 1, 8 - pos.x() / (width() * .125) + 1)
                    : chessboard::coordinate(8 - pos.y() / (height() * .125) + 1, pos.x() / (width() * .125) + 1);
}

QRectF chessboardWidget::getCellRectF(chessboard::coordinate coor)
{
    qreal board_size = qMin(width(), height());
    qreal cell_size = board_size * .125;
    if (rollback)
    {
        return QRectF((8 - coor.col()) * board_size * .125, (coor.row() - 1) * board_size * .125, cell_size, cell_size);
    }
    else
    {
        return QRectF((coor.col() - 1) * board_size * .125, (8 - coor.row()) * board_size * .125, cell_size, cell_size);
    }
}

void chessboardWidget::paintEvent(QPaintEvent *)
{
    quint32 board_size = height() > width() ? width() : height();
    quint32 cell_size = board_size * .125;
    QImage buffer = QImage(board_size, board_size, QImage::Format_ARGB32);
    QPainter painter = QPainter(&buffer);

    // 绘制棋盘到缓冲区
    painter.drawImage(rect(), board_img);

    if (selected)
    {
        // 绘制选择棋子效果到缓冲区
        painter.fillRect(getCellRectF(selected_coor), QColor(0, 255, 0, 64));

        // 绘制棋子可达棋格指示
        if (!dest_list.isEmpty())
        {
            for (chessboard::coordinate dest_coor : dest_list)
            {
                if (getChess(dest_coor))
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
            chess *p_chess = getChess(row_in_chessboard, col_in_chessboard);
            if (p_chess == nullptr)
            {
                continue;
            }
            painter.drawImage(getCellRectF(coordinate(row_in_chessboard, col_in_chessboard)),
                              *piece_img_array[static_cast<size_t>(p_chess->getType())].get());
        }
    painter.end();

    // 绘制缓冲区到屏幕
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawImage(0, 0, buffer);
}

void chessboardWidget::resizeEvent(QResizeEvent *event)
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

void chessboardWidget::mousePressEvent(QMouseEvent *event)
{
    // 记录鼠标按下棋格
    mouse_press_coordinate = getCoordinate(event->pos());
}

void chessboardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    // 释放鼠标时鼠标移出widget，直接返回
    if (event->pos().x() < 0 || event->pos().x() > width() || event->pos().y() < 0 || event->pos().y() > height())
    {
        return;
    }

    // 鼠标按下与释放不是同一棋格，直接返回
    if (getCoordinate(event->pos()) != mouse_press_coordinate)
    {
        return;
    }

    // 鼠标按下与释放是同一棋格
    chessboard::coordinate current_coor = getCoordinate(event->pos());
    chess *p_current_chess = getChess(current_coor);

    // 已经选择一个棋子
    if (selected)
    {
        // 点击坐标在可达列表中
        if (dest_list.contains(current_coor))
        {
            moveChess(selected_coor, current_coor);
            dest_list.clear();
            selected = false;
        }
        // 点击坐标不在可达列表中，且有棋子，选中新棋子
        else if (p_current_chess)
        {
            selected_coor = current_coor;
            dest_list = getReachable(selected_coor);
        }
        // 点击坐标不在可达列表中，也没有棋子，取消选择
        else
        {
            selected = false;
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
        selected = true;
        selected_coor = current_coor;
        dest_list = getReachable(selected_coor);
    }
    update();
}
