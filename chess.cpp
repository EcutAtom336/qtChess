#include "chess.h"

#include <QList>
#include <QString>
#include <cstddef>
#include <qassert.h>
#include <qcontainerfwd.h>
#include <stdexcept>

const QStringList chess::PIECE_NAMES = {
    "wK", "wQ", "wB", "wN", "wR", "wP", "bK", "bQ", "bB", "bN", "bR", "bP",
};

chess::chess(enum type t)
{
    Q_ASSERT(static_cast<size_t>(t) >= 0 && static_cast<size_t>(t) <= 11);
    type = t;
}

void chess::setType(enum type t)
{
    type = t;
}

enum chess::type chess::getType()
{
    return type;
}

QString chess::getName()
{
    return PIECE_NAMES[static_cast<size_t>(this->type)];
}

void chess::setMoved()
{
    m_moved = true;
}

bool chess::isMoved()
{
    return m_moved;
}

bool chess::isSameTeam(const chess &chess)
{
    if (((type == type::WHITE_KING || type == type::WHITE_QUEEN || type == type::WHITE_BISHOP ||
          type == type::WHITE_KNIGHT || type == type::WHITE_ROOK || type == type::WHITE_PAWN) &&
         (chess.type == type::WHITE_KING || chess.type == type::WHITE_QUEEN || chess.type == type::WHITE_BISHOP ||
          chess.type == type::WHITE_KNIGHT || chess.type == type::WHITE_ROOK || chess.type == type::WHITE_PAWN)) ||
        ((type == type::BLACK_KING || type == type::BLACK_QUEEN || type == type::BLACK_BISHOP ||
          type == type::BLACK_KNIGHT || type == type::BLACK_ROOK || type == type::BLACK_PAWN) &&
         (chess.type == type::BLACK_KING || chess.type == type::BLACK_QUEEN || chess.type == type::BLACK_BISHOP ||
          chess.type == type::BLACK_KNIGHT || chess.type == type::BLACK_ROOK || chess.type == type::BLACK_PAWN)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
