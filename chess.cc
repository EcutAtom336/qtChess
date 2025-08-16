#include "chess.h"

#include <cstddef>
#include <iostream>

#include <QList>
#include <QString>

#include <qassert.h>
#include <qcontainerfwd.h>
#include <qhashfunctions.h>
#include <qlogging.h>
#include <qtypes.h>

namespace qtchess
{

const QStringList Chess::kName = {
    "wK", "wQ", "wB", "wN", "wR", "wP", "bK", "bQ", "bB", "bN", "bR", "bP",
};

Chess::Chess(Side side, Type type) : side_(side), type_(type)
{
}

void Chess::setType(Type new_type)
{
    type_ = new_type;
}

Chess::Side Chess::getSide() const noexcept
{
    return side_;
}

Chess::Type Chess::getType() const
{
    return type_;
}

QString Chess::getName() const
{
    return getName(side_, type_);
}

QString Chess::getName(Side side, Type type) noexcept
{
    const char side_char = (side == Side::kWhite) ? 'w' : 'b';
    switch (type)
    {
    case Type::kKing:
        return QString("%1K").arg(side_char);
    case Type::kQueen:
        return QString("%1Q").arg(side_char);
    case Type::kBishop:
        return QString("%1B").arg(side_char);
    case Type::kKnight:
        return QString("%1N").arg(side_char);
    case Type::kRook:
        return QString("%1R").arg(side_char);
    case Type::kPawn:
        return QString("%1P").arg(side_char);
    }
    Q_UNREACHABLE();
}

void Chess::setMoved()
{
    moved_ = true;
}

bool Chess::isMoved() const
{
    return moved_;
}

bool Chess::isSameTeam(const Chess &chess) const
{
    if (side_ == chess.getSide())
    {
        return true;
    }
    else
    {
        return false;
    }
}

} // namespace qtchess
