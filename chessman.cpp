#include "chessman.h"

Chessman::Chessman(chessType_t type)
{
    this->chess_type = type;
}

Chessman::chessType_t Chessman::getChess_type() const
{
    return chess_type;
}
