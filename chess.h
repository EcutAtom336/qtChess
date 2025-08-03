#ifndef CHESS_H
#define CHESS_H

#include <QList>
#include <QString>

namespace qtchess
{

class Chess
{
  public:
    enum class Type
    {
        kWhiteKing = 0, // 白王
        kWhiteQueen,    // 白后
        kWhiteBishop,   // 白象
        kWhiteKnight,   // 白马
        kWhiteRook,     // 白车
        kWhitePawn,     // 白兵
        kBlackKing,     // 黑王
        kBlackQueen,    // 黑后
        kBlackBishop,   // 黑象
        kBlackKnight,   // 黑马
        kBlackRook,     // 黑车
        kBlackPawn,     // 黑兵
        kCount,
    };

    static const QStringList kPieceNames;

    Chess(enum Type t);

    enum Type getType() const;
    void setType(enum Type new_type);
    QString getName() const;
    void setMoved();
    bool isMoved() const;
    bool isSameTeam(const Chess &chess) const;

  private:
    enum Type type_;
    bool moved_ = false;
};

} // namespace qtchess

#endif // CHESS_H
