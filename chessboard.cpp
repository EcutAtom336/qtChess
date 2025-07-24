#include "chessboard.h"
#include "chess.h"
#include <cstddef>
#include <qassert.h>
#include <qcontainerfwd.h>
#include <qimage.h>
#include <qlogging.h>
#include <qtypes.h>

chessboard::chessboard()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            board[i][j] = nullptr;
        }
    }
}

void chessboard::init(mode mode)
{
    clear();

    if (mode == mode::STANDAR)
    {

        for (size_t col = 1; col <= 8; col++)
        {
            addChess(2, col, chess::type::WHITE_PAWN);
            addChess(7, col, chess::type::BLACK_PAWN);
        }

        addChess(1, 1, chess::type::WHITE_ROOK);
        addChess(1, 2, chess::type::WHITE_KNIGHT);
        addChess(1, 3, chess::type::WHITE_BISHOP);
        addChess(1, 4, chess::type::WHITE_QUEEN);
        addChess(1, 5, chess::type::WHITE_KING);
        addChess(1, 6, chess::type::WHITE_BISHOP);
        addChess(1, 7, chess::type::WHITE_KNIGHT);
        addChess(1, 8, chess::type::WHITE_ROOK);

        addChess(8, 1, chess::type::BLACK_ROOK);
        addChess(8, 2, chess::type::BLACK_KNIGHT);
        addChess(8, 3, chess::type::BLACK_BISHOP);
        addChess(8, 4, chess::type::BLACK_QUEEN);
        addChess(8, 5, chess::type::BLACK_KING);
        addChess(8, 6, chess::type::BLACK_BISHOP);
        addChess(8, 7, chess::type::BLACK_KNIGHT);
        addChess(8, 8, chess::type::BLACK_ROOK);
    }
}

void chessboard::clear()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] != nullptr)
            {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
}

chess *chessboard::getChess(const quint8 row, const quint8 col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    return board[row - 1][col - 1];
}

quint8 chessboard::count()
{
    quint8 cnt = 0;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] != nullptr)
            {
                cnt++;
            }
        }
    }
    return cnt;
}

QString chessboard::getCellName(const quint8 row, const quint8 col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    const QString CELL_NAMES[8][8] = {
        {"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"}, //
        {"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"}, //
        {"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"}, //
        {"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"}, //
        {"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"}, //
        {"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"}, //
        {"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"}, //
        {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"}, //
    };
    return CELL_NAMES[row - 1][col - 1];
}

void chessboard::addChess(const quint8 row, const quint8 col, enum chess::type type)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    Q_ASSERT(getChess(row, col) == nullptr);
    board[row - 1][col - 1] = new chess(type);
}

void chessboard::removeChess(const quint8 row, const quint8 col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    Q_ASSERT(getChess(row, col) != nullptr);
    delete board[row - 1][col - 1];
}
