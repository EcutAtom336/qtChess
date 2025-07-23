#include "chessboard.h"
#include "chess.h"
#include <cstddef>
#include <qlogging.h>

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
        addChess(chessboard::cell::a1, chess::type::WHITE_ROOK);
        addChess(chessboard::cell::b1, chess::type::WHITE_KNIGHT);
        addChess(chessboard::cell::c1, chess::type::WHITE_BISHOP);
        addChess(chessboard::cell::d1, chess::type::WHITE_QUEEN);
        addChess(chessboard::cell::e1, chess::type::WHITE_KING);
        addChess(chessboard::cell::f1, chess::type::WHITE_BISHOP);
        addChess(chessboard::cell::g1, chess::type::WHITE_KNIGHT);
        addChess(chessboard::cell::h1, chess::type::WHITE_ROOK);

        addChess(chessboard::cell::a2, chess::type::WHITE_PAWN);
        addChess(chessboard::cell::b2, chess::type::WHITE_PAWN);
        addChess(chessboard::cell::c2, chess::type::WHITE_PAWN);
        addChess(chessboard::cell::d2, chess::type::WHITE_PAWN);
        addChess(chessboard::cell::e2, chess::type::WHITE_PAWN);
        addChess(chessboard::cell::f2, chess::type::WHITE_PAWN);
        addChess(chessboard::cell::g2, chess::type::WHITE_PAWN);
        addChess(chessboard::cell::h2, chess::type::WHITE_PAWN);

        addChess(chessboard::cell::a7, chess::type::BLACK_PAWN);
        addChess(chessboard::cell::b7, chess::type::BLACK_PAWN);
        addChess(chessboard::cell::c7, chess::type::BLACK_PAWN);
        addChess(chessboard::cell::d7, chess::type::BLACK_PAWN);
        addChess(chessboard::cell::e7, chess::type::BLACK_PAWN);
        addChess(chessboard::cell::f7, chess::type::BLACK_PAWN);
        addChess(chessboard::cell::g7, chess::type::BLACK_PAWN);
        addChess(chessboard::cell::h7, chess::type::BLACK_PAWN);

        addChess(chessboard::cell::a8, chess::type::BLACK_ROOK);
        addChess(chessboard::cell::b8, chess::type::BLACK_KNIGHT);
        addChess(chessboard::cell::c8, chess::type::BLACK_BISHOP);
        addChess(chessboard::cell::d8, chess::type::BLACK_QUEEN);
        addChess(chessboard::cell::e8, chess::type::BLACK_KING);
        addChess(chessboard::cell::f8, chess::type::BLACK_BISHOP);
        addChess(chessboard::cell::g8, chess::type::BLACK_KNIGHT);
        addChess(chessboard::cell::h8, chess::type::BLACK_ROOK);
    }
}

bool chessboard::addChess(cell cell, enum chess::type type)
{
    quint8 row_in_chessboard = static_cast<size_t>(cell) / 8 + 1;
    quint8 col_in_chessboard = static_cast<size_t>(cell) % 8 + 1;

    return addChess(row_in_chessboard, col_in_chessboard, type);
}

bool chessboard::removeChess(cell cell)
{
    quint8 row_in_chessboard = static_cast<size_t>(cell) / 8 + 1;
    quint8 col_in_chessboard = static_cast<size_t>(cell) % 8 + 1;

    return removeChess(row_in_chessboard, col_in_chessboard);
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

chess *chessboard::getChess(quint8 row_in_chessboard, quint8 col_in_chessboard)
{
    if (row_in_chessboard > 8 || col_in_chessboard > 8)
    {
        qErrnoWarning("out of chessboard.");
        return nullptr;
    }

    return board[row_in_chessboard - 1][col_in_chessboard - 1];
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

bool chessboard::addChess(quint8 row_in_chessboard, quint8 col_in_chessboard, enum chess::type t)
{
    if (row_in_chessboard > 8 || col_in_chessboard > 8)
    {
        qErrnoWarning("out of chessboard.");
        return false;
    }
    if (board[row_in_chessboard - 1][col_in_chessboard - 1] != nullptr)
    {
        return false;
    }
    board[row_in_chessboard - 1][col_in_chessboard - 1] = new chess(t);
    return true;
}

bool chessboard::removeChess(quint8 row_in_chessboard, quint8 col_in_chessboard)
{
    if (row_in_chessboard > 8 || col_in_chessboard > 8)
    {
        qErrnoWarning("out of chessboard.");
        return false;
    }
    if (board[row_in_chessboard - 1][col_in_chessboard - 1] == nullptr)
    {
        return false;
    }
    delete board[row_in_chessboard - 1][col_in_chessboard - 1];
    return true;
}
