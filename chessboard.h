#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QtTypes>

#include <qassert.h>
#include <qcompare.h>
#include <qcontainerfwd.h>
#include <qlist.h>
#include <qpoint.h>
#include <qsharedpointer.h>
#include <qtypes.h>

#include "chess.h"
#include "coordinate.h"

namespace qtchess
{

class Chessboard
{
  public:
    enum class Mode
    {
        kStandard,
    };

    Chessboard();

    virtual void init(const Mode mode);
    virtual void clear();
    quint8 count();

    virtual void addChess(const quint8 row, const quint8 col, const Chess::Side side, const Chess::Type t);
    virtual void addChess(const Coordinate &coordinate, const Chess::Side side, const Chess::Type t);

    virtual void removeChess(const quint8 row, const quint8 col);
    virtual void removeChess(const Coordinate &coordinate);

    const Chess &getChess(const quint8 row, const quint8 col) const;
    const Chess &getChess(const Coordinate &coordinate) const;

    virtual void moveChess(const Coordinate &from, const Coordinate &to);
    virtual void moveChess(const quint8 from_row, const quint8 from_col, const quint8 to_row, const quint8 to_col);

    Coordinates getReachable(const Coordinate &from);

    bool cellIsEmpty(const quint8 row, const quint8 col) const;
    bool cellIsEmpty(const Coordinate coordinate) const;

    static QString getCellName(const Coordinate &coordinate);
    static QString getCellName(const quint8 row, const quint8 col);

  private:
    std::unique_ptr<Chess> board_[8][8];

    void tryAddDest(Coordinates &coordinates, const Coordinate &base, const qint8 d_row, const qint8 d_col,
                    bool *p_blocked = nullptr);
};

} // namespace qtchess

#endif // CHESSBOARD_H
