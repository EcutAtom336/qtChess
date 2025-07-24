#ifndef CHESS_H
#define CHESS_H

#include <QList>
#include <QString>
#include <qcontainerfwd.h>

class chess
{
  public:
    enum class type
    {
        WHITE_KING = 0, // 白王
        WHITE_QUEEN,    // 白后
        WHITE_BISHOP,   // 白象
        WHITE_KNIGHT,   // 白马
        WHITE_ROOK,     // 白车
        WHITE_PAWN,     // 白兵
        BLACK_KING,     // 黑王
        BLACK_QUEEN,    // 黑后
        BLACK_BISHOP,   // 黑象
        BLACK_KNIGHT,   // 黑马
        BLACK_ROOK,     // 黑车
        BLACK_PAWN,     // 黑兵
        COUNT,
    };

    static const QStringList PIECE_NAMES;

    chess(enum type t);
    enum type getType();
    void setType(enum type t);
    QString getName();

  private:
    enum type type;
};

#endif // CHESS_H
