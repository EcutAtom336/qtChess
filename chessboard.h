#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chess.h"
#include <QtTypes>
#include <qcompare.h>
#include <qcontainerfwd.h>
#include <qlist.h>
#include <qpoint.h>
#include <qtypes.h>

class chessboard
{
  public:
    enum class mode
    {
        STANDAR,
    };

    class coordinate
    {
      public:
        coordinate(quint8 row, quint8 col);
        coordinate(const chessboard::coordinate &base, qint8 d_row, qint8 d_col);

        quint8 row() const;
        quint8 col() const;

        void setRow(const quint8 new_row);
        void setCol(const quint8 new_col);

        bool operateIsValid(const qint8 d_row, const qint8 d_col) const;

        bool operator==(const coordinate &other) const;
        bool operator!=(const coordinate &other) const;
        coordinate operator+(const coordinate &other) const;
        coordinate operator-(const coordinate &other) const;
        coordinate &operator+=(const coordinate &other);
        coordinate &operator-=(const coordinate &other);

      private:
        QPoint m_point = QPoint();
    };

    chessboard();
    virtual void init(const enum mode mode);
    virtual void clear();
    quint8 count();

    virtual void addChess(const coordinate &coor, const enum chess::type t);
    virtual void addChess(const quint8 row, const quint8 col, const enum chess::type t);

    virtual void removeChess(const coordinate &coor);
    virtual void removeChess(const quint8 row, const quint8 col);

    chess *getChess(const coordinate &coor);
    chess *getChess(const quint8 row, const quint8 col);

    virtual void moveChess(const coordinate &old_coor, const coordinate &new_coor);
    virtual void moveChess(const quint8 old_row, const quint8 old_col, const quint8 new_row, const quint8 new_col);

    QList<chessboard::coordinate> getReachable(const coordinate &coor);

    static QString getCellName(const coordinate &coor);
    static QString getCellName(const quint8 row, const quint8 col);

  protected:
  private:
    chess *board[8][8];

    void tryAddDest(QList<chessboard::coordinate> &list, const chessboard::coordinate &base, const qint8 d_row,
                    const qint8 d_col, bool *p_blocked = nullptr);

};

#endif // CHESSBOARD_H
