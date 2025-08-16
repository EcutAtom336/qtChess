#ifndef CHESS_H
#define CHESS_H

#include <QList>
#include <QString>

#include <qcontainerfwd.h>
#include <qhashfunctions.h>
#include <qtypes.h>

namespace qtchess
{

class Chess
{
  public:
    enum class Side : quint8
    {
        kWhite = 0,
        kBlack,
    };

    enum class Type : quint8
    {
        kKing = 0,
        kQueen,
        kBishop,
        kKnight,
        kRook,
        kPawn,
    };

    static const QStringList kName;

    Chess(Side side, Type t);

    Type getType() const;
    void setType(Type new_type);
    Side getSide() const noexcept;
    QString getName() const;
    static QString getName(Side side, Type type) noexcept;
    void setMoved();
    bool isMoved() const;
    bool isSameTeam(const Chess &chess) const;

  private:
    Side side_;
    Type type_;
    bool moved_ = false;
};

} // namespace qtchess

#endif // CHESS_H
