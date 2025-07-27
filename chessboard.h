#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QtTypes>

#include <qcompare.h>
#include <qcontainerfwd.h>
#include <qlist.h>
#include <qpoint.h>
#include <qtypes.h>

#include "chess.h"

namespace qtchess
{

class Chessboard
{
  public:
    enum class Mode
    {
        kStandard,
    };

    class Coordinate
    {
      public:
        Coordinate(quint8 row, quint8 col);
        Coordinate(const Chessboard::Coordinate &base, qint8 d_row, qint8 d_col);

        quint8 row() const;
        quint8 col() const;

        void setRow(const quint8 new_row);
        void setCol(const quint8 new_col);

        bool operateIsValid(const qint8 d_row, const qint8 d_col) const;

        bool operator==(const Coordinate &other) const;
        bool operator!=(const Coordinate &other) const;
        Coordinate operator+(const Coordinate &other) const;
        Coordinate operator-(const Coordinate &other) const;
        Coordinate &operator+=(const Coordinate &other);
        Coordinate &operator-=(const Coordinate &other);

      private:
        QPoint point_ = QPoint();
    };

    Chessboard();

    virtual void init(const enum Mode mode);
    virtual void clear();
    quint8 count();

    virtual void addChess(const Coordinate &coor, const enum Chess::Type t);
    virtual void addChess(const quint8 row, const quint8 col, const enum Chess::Type t);

    virtual void removeChess(const Coordinate &coor);
    virtual void removeChess(const quint8 row, const quint8 col);

    Chess *getChess(const Coordinate &coor);
    Chess *getChess(const quint8 row, const quint8 col);

    virtual void moveChess(const Coordinate &old_coor, const Coordinate &new_coor);
    virtual void moveChess(const quint8 old_row, const quint8 old_col, const quint8 new_row, const quint8 new_col);

    QList<Chessboard::Coordinate> getReachable(const Coordinate &coor);

    static QString getCellName(const Coordinate &coor);
    static QString getCellName(const quint8 row, const quint8 col);

  private:
    Chess *board_[8][8];

    void tryAddDest(QList<Chessboard::Coordinate> &list, const Chessboard::Coordinate &base, const qint8 d_row,
                    const qint8 d_col, bool *p_blocked = nullptr);
};

} // namespace qtchess

#endif // CHESSBOARD_H
