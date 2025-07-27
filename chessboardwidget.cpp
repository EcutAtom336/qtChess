#include "chessboardwidget.h"

#include <array>
#include <cmath>
#include <cstddef>

#include <QWidget>

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

#include "chess.h"
#include "chessboard.h"
#include "chessboardwidget.h"

const std::array<QString, static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kCount)>
    qtchess::ChessboardWidget::kBoardStyleFileNames = []() {
        std::array<QString, static_cast<size_t>(ChessboardWidget::BoardStyle::kCount)> array;
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kBlue)] = "blue.png";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kBlue2)] = "blue2.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kBlue3)] = "blue3.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kBlueMarblle)] = "blue-marble.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kBrown)] = "brown.png";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kCanvas2)] = "canvas2.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kGreen)] = "green.png";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kGreenPlastic)] = "green-plastic.png";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kGrey)] = "grey.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kHorsey)] = "horsey.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kIc)] = "ic.png";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kLeather)] = "leather.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kMaple)] = "maple.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kMaple2)] = "maple2.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kMarble)] = "marble.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kMetal)] = "metal.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kOlive)] = "olive.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kPinkPyramid)] = "pink-pyramid.png";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kPurple)] = "purple.png";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kPurpleDiag)] = "purple-diag.png";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kWood)] = "wood.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kWood2)] = "wood2.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kWood3)] = "wood3.jpg";
        array[static_cast<size_t>(qtchess::ChessboardWidget::BoardStyle::kWood4)] = "wood4.jpg";
        return array;
    }();

const std::array<QString, static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kCount)>
    qtchess::ChessboardWidget::kPieceStyleFloderNames = []() {
        std::array<QString, static_cast<size_t>(ChessboardWidget::ChessStyle::kCount)> array;
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kAlpha)] = "alpha/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kAnarcandy)] = "anarcandy/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kCaliente)] = "caliente/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kCalifornia)] = "california/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kCardinal)] = "cardinal/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kCburnett)] = "cburnett/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kCeltic)] = "celtic/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kChess7)] = "chess7/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kChessnut)] = "chessnut/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kCompanion)] = "companion/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kCooke)] = "cooke/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kDubrovny)] = "dubrovny/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kFantasy)] = "fantasy/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kFiri)] = "firi/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kFresca)] = "fresca/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kGioco)] = "gioco/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kGovernor)] = "governor/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kHorsey)] = "horsey/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kIcpieces)] = "icpieces/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kKiwenSuwi)] = "kiwen-suwi/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kKosal)] = "kosal/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kLeipzig)] = "leipzig/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kLetter)] = "letter/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kMaestro)] = "maestro/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kMerida)] = "merida/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kMonarchy)] = "monarchy/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kMpchess)] = "mpchess/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kPirouetti)] = "pirouetti/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kPixel)] = "pixel/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kReillycraig)] = "reillycraig/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kRhosgfx)] = "rhosgfx/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kRiohacha)] = "riohacha/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kShapes)] = "shapes/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kSpatial)] = "spatial/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kStaunty)] = "staunty/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kTatiana)] = "tatiana/";
        array[static_cast<size_t>(qtchess::ChessboardWidget::ChessStyle::kXkcdm)] = "xkcd/";
        return array;
    }();

qtchess::ChessboardWidget::ChessboardWidget(QWidget *parent, BoardStyle board_style, ChessStyle chess_style)
{
    this->setBoardStyle(board_style);
    this->setPieceStyle(chess_style);
}

void qtchess::ChessboardWidget::setBoardStyle(BoardStyle style)
{
    const QString kBoardResPrefix = "/";
    const QString kBoardResPath = "res/board/";

    if (style >= BoardStyle::kCount)
    {
        qWarning("invalid board style.");
        return;
    }

    QString file = ":" + kBoardResPrefix + kBoardResPath + kBoardStyleFileNames[static_cast<size_t>(style)];

    if (board_img_.load(file) == false)
    {
        qWarning("load chessboard image fail.");
    }

    update();
}

void qtchess::ChessboardWidget::setPieceStyle(ChessStyle style)
{
    const QString kPieceResPrefix = "/";
    const QString kPieceResPath = "res/piece/";

    if (style >= ChessStyle::kCount)
    {
        qWarning("invalid piece style.");
        return;
    }

    QString path = ":" + kPieceResPrefix + kPieceResPath + kPieceStyleFloderNames[static_cast<size_t>(style)];

    reloadPieceSvg(path);
    renderPieceImg();

    update();
}

void qtchess::ChessboardWidget::clear()
{
    Chessboard::clear();
    update();
}

void qtchess::ChessboardWidget::addChess(const quint8 row, const quint8 col, const enum Chess::Type type)
{
    Chessboard::addChess(row, col, type);
    update();
}

void qtchess::ChessboardWidget::removeChess(const quint8 row, const quint8 col)
{
    Chessboard::removeChess(row, col);
    update();
}

void qtchess::ChessboardWidget::init(Mode mode)
{
    Chessboard::init(mode);
    update();
}

void qtchess::ChessboardWidget::setRollback(bool new_state)
{
    rollback_ = new_state;
}

void qtchess::ChessboardWidget::addChess(const Coordinate &coor, const enum Chess::Type t)
{
    addChess(coor.row(), coor.col(), t);
}

void qtchess::ChessboardWidget::removeChess(const Coordinate &coor)
{
    removeChess(coor.row(), coor.col());
}

void qtchess::ChessboardWidget::reloadPieceSvg(QString path)
{
    for (int i = 0; i < static_cast<size_t>(Chess::Type::kCount); i++)
    {
        const QString &piece_name = Chess::kPieceNames[i];
        QString svg_file = path + piece_name + ".svg";
        piece_svgs_[i].load(svg_file);
        Q_ASSERT(piece_svgs_[i].isValid());
    }
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
    return rollback_ ? Chessboard::Coordinate(pos.y() / (height() * .125) + 1, 8 - pos.x() / (width() * .125) + 1)
                     : Chessboard::Coordinate(8 - pos.y() / (height() * .125) + 1, pos.x() / (width() * .125) + 1);
}

QRectF qtchess::ChessboardWidget::getCellRectF(Chessboard::Coordinate coor)
{
    qreal board_size = qMin(width(), height());
    qreal cell_size = board_size * .125;
    if (rollback_)
    {
        return QRectF((8 - coor.col()) * board_size * .125, (coor.row() - 1) * board_size * .125, cell_size, cell_size);
    }
    else
    {
        return QRectF((coor.col() - 1) * board_size * .125, (8 - coor.row()) * board_size * .125, cell_size, cell_size);
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
            Chess *p_chess = getChess(row_in_chessboard, col_in_chessboard);
            if (p_chess == nullptr)
            {
                continue;
            }
            painter.drawImage(getCellRectF(Coordinate(row_in_chessboard, col_in_chessboard)),
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
    Chess *p_current_chess = getChess(current_coor);

    // 已经选择一个棋子
    if (selected_)
    {
        // 点击坐标在可达列表中
        if (reachable_coordinates_.contains(current_coor))
        {
            moveChess(selected_coordinate_, current_coor);
            reachable_coordinates_.clear();
            selected_ = false;
        }
        // 点击坐标不在可达列表中，且有棋子，选中新棋子
        else if (p_current_chess)
        {
            selected_coordinate_ = current_coor;
            reachable_coordinates_ = getReachable(selected_coordinate_);
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
        reachable_coordinates_ = getReachable(selected_coordinate_);
    }
    update();
}
