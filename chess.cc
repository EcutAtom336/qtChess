#include "chess.h"

#include <cstddef>

#include <QList>
#include <QString>

#include <qassert.h>
#include <qcontainerfwd.h>

const QStringList qtchess::Chess::kPieceNames = {
    "wK", "wQ", "wB", "wN", "wR", "wP", "bK", "bQ", "bB", "bN", "bR", "bP",
};

qtchess::Chess::Chess(enum Type type)
{
    Q_ASSERT(static_cast<size_t>(type) >= 0 && static_cast<size_t>(type) <= 11);
    type_ = type;
}

void qtchess::Chess::setType(enum Type new_type)
{
    type_ = new_type;
}

enum qtchess::Chess::Type qtchess::Chess::getType()
{
    return type_;
}

QString qtchess::Chess::getName()
{
    return kPieceNames[static_cast<size_t>(this->type_)];
}

void qtchess::Chess::setMoved()
{
    moved_ = true;
}

bool qtchess::Chess::isMoved()
{
    return moved_;
}

bool qtchess::Chess::isSameTeam(const Chess &chess)
{
    if (((type_ == Type::kWhiteKing || type_ == Type::kWhiteQueen || type_ == Type::kWhiteBishop ||
          type_ == Type::kWhiteKnight || type_ == Type::kWhiteRook || type_ == Type::kWhitePawn) &&
         (chess.type_ == Type::kWhiteKing || chess.type_ == Type::kWhiteQueen || chess.type_ == Type::kWhiteBishop ||
          chess.type_ == Type::kWhiteKnight || chess.type_ == Type::kWhiteRook || chess.type_ == Type::kWhitePawn)) ||
        ((type_ == Type::kBlackKing || type_ == Type::kBlackQueen || type_ == Type::kBlackBishop ||
          type_ == Type::kBlackKnight || type_ == Type::kBlackRook || type_ == Type::kBlackPawn) &&
         (chess.type_ == Type::kBlackKing || chess.type_ == Type::kBlackQueen || chess.type_ == Type::kBlackBishop ||
          chess.type_ == Type::kBlackKnight || chess.type_ == Type::kBlackRook || chess.type_ == Type::kBlackPawn)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
