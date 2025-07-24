#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chess.h"
#include <QtTypes>

class chessboard
{
  public:
    enum class cell
    {
        a1,
        b1,
        c1,
        d1,
        e1,
        f1,
        g1,
        h1,
        a2,
        b2,
        c2,
        d2,
        e2,
        f2,
        g2,
        h2,
        a3,
        b3,
        c3,
        d3,
        e3,
        f3,
        g3,
        h3,
        a4,
        b4,
        c4,
        d4,
        e4,
        f4,
        g4,
        h4,
        a5,
        b5,
        c5,
        d5,
        e5,
        f5,
        g5,
        h5,
        a6,
        b6,
        c6,
        d6,
        e6,
        f6,
        g6,
        h6,
        a7,
        b7,
        c7,
        d7,
        e7,
        f7,
        g7,
        h7,
        a8,
        b8,
        c8,
        d8,
        e8,
        f8,
        g8,
        h8,
    };

    enum class mode
    {
        STANDAR,
    };

    chessboard();
    virtual void init(enum mode mode);

    virtual bool addChess(enum cell cell, enum chess::type type);
    virtual bool removeChess(enum cell cell);
    chess *getChess(quint8 row_in_chessboard, quint8 col_in_chessboard);

    virtual void clear();
    quint8 count();

  protected:
  private:
    chess *board[8][8];

    bool addChess(quint8 row_in_chessboard, quint8 col_in_chessboard, enum chess::type t);
    bool removeChess(quint8 row_in_chessboard, quint8 col_in_chessboard);
};

#endif // CHESSBOARD_H
