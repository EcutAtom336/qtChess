#include "chessboardwidget.h"
#include "chess.h"
#include "chessboard.h"

#include <QWidget>
#include <array>
#include <cstddef>
#include <qcontainerfwd.h>
#include <qlogging.h>

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

    for (int i = 0; i < static_cast<size_t>(chess::type::COUNT); i++)
    {
        const QString &piece_name = chess::PIECE_NAMES[i];
        QString svg_file = path + piece_name + ".svg";
        if (piece_svg_array[i].load(svg_file) == false)
        {
            qWarning("load chess svg fail");
        }
    }
}

void chessboardWidget::clear()
{
    chessboard::clear();
    update();
}

bool chessboardWidget::addChess(cell cell, enum chess::type type)
{
    bool ret_bool = chessboard::addChess(cell, type);
    if (ret_bool)
    {
        update();
    }
    return ret_bool;
}

bool chessboardWidget::removeChess(cell cell)
{
    bool ret_bool = chessboard::removeChess(cell);
    if (ret_bool)
    {
        update();
    }
    return ret_bool;
}

void chessboardWidget::init(mode mode)
{
    chessboard::init(mode);
    update();
}

void chessboardWidget::paintEvent(QPaintEvent *)
{
    QPainter board_painter(this);

    // 绘制棋盘
    quint32 board_size = height() > width() ? width() : height();

    board_painter.drawImage(0, 0, board_img.scaled(board_size, board_size));

    // 绘制棋子
    for (int row_in_chessboard = 1; row_in_chessboard <= 8; ++row_in_chessboard)
        for (int col_in_chessboard = 1; col_in_chessboard <= 8; ++col_in_chessboard)
        {
            chess *p_chess = getChess(row_in_chessboard, col_in_chessboard);
            if (p_chess == nullptr)
            {
                continue;
            }

            QRectF targetRect((col_in_chessboard - 1) * 0.125 * board_size,
                              (8 - row_in_chessboard) * 0.125 * board_size, board_size * 0.125, board_size * 0.125);
            piece_svg_array[static_cast<size_t>(p_chess->getType())].render(&board_painter, targetRect);
        }
}

// void ChessboardWidget::resizeEvent(QResizeEvent *event)
// {
//     QWidget::resizeEvent(event);

//     // 固定比例宽:高 = 16:9
//     const double ratio = 16.0 / 9.0;

//     // 获取新的宽度
//     int newWidth = event->size().width();
//     int newHeight = static_cast<int>(newWidth / ratio);

//     // 设置新高度
//     this->resize(newWidth, newHeight);
// }
