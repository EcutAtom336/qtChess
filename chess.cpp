#include "chess.h"

#include <QList>
#include <QString>
#include <qcontainerfwd.h>

const QStringList chess::PIECE_NAMES = {
    "wK", "wQ", "wB", "wN", "wR", "wP", "bK", "bQ", "bB", "bN", "bR", "bP",
};

chess::chess(enum type t)
{
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
