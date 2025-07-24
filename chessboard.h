#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chess.h"
#include <QtTypes>
#include <qcontainerfwd.h>
#include <qtypes.h>

class chessboard
{
  public:
    enum class mode
    {
        STANDAR,
    };

    chessboard();
    virtual void init(const enum mode mode);
    virtual void addChess(const quint8 row, const quint8 col, const enum chess::type t);
    virtual void removeChess(const quint8 row, const quint8 col);
    chess *getChess(const quint8 row, const quint8 col);
    virtual void clear();
    quint8 count();

  protected:
  private:
    chess *board[8][8];
};

#endif // CHESSBOARD_H
