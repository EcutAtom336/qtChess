#include "chessboard.h"

#include <cstddef>

#include <memory>
#include <qassert.h>
#include <qcontainerfwd.h>
#include <qimage.h>
#include <qlist.h>
#include <qlogging.h>
#include <qpoint.h>
#include <qscopedpointer.h>
#include <qtypes.h>

#include "chess.h"
#include "coordinate.h"

namespace qtchess
{

Chessboard::Chessboard()
{
}

void Chessboard::init(Mode mode)
{
    clear();

    if (mode == Mode::kStandard)
    {

        for (size_t col = 1; col <= 8; col++)
        {
            addChess(2, col, Chess::Side::kWhite, Chess::Type::kPawn);
            addChess(7, col, Chess::Side::kBlack, Chess::Type::kPawn);
        }

        addChess(1, 1, Chess::Side::kWhite, Chess::Type::kRook);
        addChess(1, 2, Chess::Side::kWhite, Chess::Type::kKnight);
        addChess(1, 3, Chess::Side::kWhite, Chess::Type::kBishop);
        addChess(1, 4, Chess::Side::kWhite, Chess::Type::kQueen);
        addChess(1, 5, Chess::Side::kWhite, Chess::Type::kKing);
        addChess(1, 6, Chess::Side::kWhite, Chess::Type::kBishop);
        addChess(1, 7, Chess::Side::kWhite, Chess::Type::kKnight);
        addChess(1, 8, Chess::Side::kWhite, Chess::Type::kRook);

        addChess(8, 1, Chess::Side::kBlack, Chess::Type::kRook);
        addChess(8, 2, Chess::Side::kBlack, Chess::Type::kKnight);
        addChess(8, 3, Chess::Side::kBlack, Chess::Type::kBishop);
        addChess(8, 4, Chess::Side::kBlack, Chess::Type::kQueen);
        addChess(8, 5, Chess::Side::kBlack, Chess::Type::kKing);
        addChess(8, 6, Chess::Side::kBlack, Chess::Type::kBishop);
        addChess(8, 7, Chess::Side::kBlack, Chess::Type::kKnight);
        addChess(8, 8, Chess::Side::kBlack, Chess::Type::kRook);
    }
}

void Chessboard::clear()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            board_[i][j].reset();
        }
    }
}

quint8 Chessboard::count()
{
    quint8 cnt = 0;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board_[i][j] != nullptr)
            {
                cnt++;
            }
        }
    }
    return cnt;
}

void Chessboard::addChess(const quint8 row, const quint8 col, const Chess::Side side, const Chess::Type type)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    Q_ASSERT(cellIsEmpty(row, col));
    board_[row - 1][col - 1].reset(new Chess(side, type));
}

void Chessboard::addChess(const Coordinate &coordinate, const Chess::Side side, const Chess::Type t)
{
    addChess(coordinate.getRow(), coordinate.getCol(), side, t);
}

void Chessboard::removeChess(const Coordinate &coordinate)
{
    removeChess(coordinate.getRow(), coordinate.getCol());
}

void Chessboard::removeChess(const quint8 row, const quint8 col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    Q_ASSERT(!cellIsEmpty(row, col));
    board_[row - 1][col - 1].reset();
}

const Chess &Chessboard::getChess(const quint8 row, const quint8 col) const
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    return *board_[row - 1][col - 1];
}

const Chess &Chessboard::getChess(const Coordinate &coordinate) const
{
    return getChess(coordinate.getRow(), coordinate.getCol());
}

void Chessboard::moveChess(const Coordinate &from, const Coordinate &to)
{
    moveChess(from.getRow(), from.getCol(), to.getRow(), to.getCol());
}

void Chessboard::moveChess(const quint8 from_row, const quint8 from_col, const quint8 to_row, const quint8 to_col)
{
    Q_ASSERT(from_row >= 1 && from_row <= 8 && from_col >= 1 && from_col <= 8 && to_row >= 1 && to_row <= 8 &&
             to_col >= 1 && to_col <= 8);
    Q_ASSERT(!cellIsEmpty(from_row, from_col));
    board_[to_row - 1][to_col - 1] = std::move(board_[from_row - 1][from_col - 1]);
    board_[to_row - 1][to_col - 1]->setMoved();
}

bool Chessboard::cellIsEmpty(const quint8 row, const quint8 col) const
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    if (board_[row - 1][col - 1] == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Chessboard::cellIsEmpty(const Coordinate coordinate) const
{
    return cellIsEmpty(coordinate.getRow(), coordinate.getCol());
}

Coordinates Chessboard::getReachable(const Coordinate &from)
{
    Coordinates coordinates;

    Q_ASSERT(!cellIsEmpty(from));

    Chess::Type type = getChess(from).getType();
    Chess::Side side = getChess(from).getSide();

    switch (type)
    {
    case Chess::Type::kKing: {
        // 棋子可能到达的范围
        for (qint8 d_row : {-1, 0, 1})
        {
            for (qint8 d_col : {-1, 0, 1})
            {
                tryAddDest(coordinates, from, d_row, d_col);
            }
        }

        // TODO: 特殊情况：王车易位

        // TODO: 删除送将的情况
        break;
    }
    case Chess::Type::kQueen: {
        // 棋子可能到达的范围
        bool add_row_blocked = false;
        bool sub_row_blocked = false;
        bool add_col_blocked = false;
        bool sub_col_blocked = false;
        bool add_row_add_col_blocked = false;
        bool add_row_sub_col_blocked = false;
        bool sub_row_add_col_blocked = false;
        bool sub_row_sub_col_blocked = false;
        for (quint8 d = 1; d <= 7; ++d)
        {
            // 直走
            // add row
            tryAddDest(coordinates, from, d, 0, &add_row_blocked);
            // sub row
            tryAddDest(coordinates, from, -d, 0, &sub_row_blocked);
            // add col
            tryAddDest(coordinates, from, 0, d, &add_col_blocked);
            // sub row
            tryAddDest(coordinates, from, 0, -d, &sub_col_blocked);

            // 斜走
            // add row add col
            tryAddDest(coordinates, from, d, d, &add_row_add_col_blocked);
            // add row sub col
            tryAddDest(coordinates, from, d, -d, &add_row_sub_col_blocked);
            // sub row add col
            tryAddDest(coordinates, from, -d, d, &sub_row_add_col_blocked);
            // sub row sub col
            tryAddDest(coordinates, from, -d, -d, &sub_row_sub_col_blocked);
        }
        break;
    }
    case Chess::Type::kBishop: {
        bool add_row_add_col_blocked = false;
        bool add_row_sub_col_blocked = false;
        bool sub_row_add_col_blocked = false;
        bool sub_row_sub_col_blocked = false;
        for (quint8 d = 1; d <= 7; ++d)
        {
            // 斜走
            // add row add col
            tryAddDest(coordinates, from, d, d, &add_row_add_col_blocked);
            // add row sub col
            tryAddDest(coordinates, from, d, -d, &add_row_sub_col_blocked);
            // sub row add col
            tryAddDest(coordinates, from, -d, d, &sub_row_add_col_blocked);
            // sub row sub col
            tryAddDest(coordinates, from, -d, -d, &sub_row_sub_col_blocked);
        }
        break;
    }
    case Chess::Type::kKnight: {

        tryAddDest(coordinates, from, 2, 1);
        tryAddDest(coordinates, from, 2, -1);
        tryAddDest(coordinates, from, -2, 1);
        tryAddDest(coordinates, from, -2, -1);

        tryAddDest(coordinates, from, 1, 2);
        tryAddDest(coordinates, from, -1, 2);
        tryAddDest(coordinates, from, 1, -2);
        tryAddDest(coordinates, from, -1, -2);

        break;
    }
    case Chess::Type::kRook: {
        // 棋子可能到达的范围
        bool add_row_blocked = false;
        bool sub_row_blocked = false;
        bool add_col_blocked = false;
        bool sub_col_blocked = false;
        for (quint8 d = 1; d <= 7; ++d)
        {
            // 直走
            // add row
            tryAddDest(coordinates, from, d, 0, &add_row_blocked);
            // sub row
            tryAddDest(coordinates, from, -d, 0, &sub_row_blocked);
            // add col
            tryAddDest(coordinates, from, 0, d, &add_col_blocked);
            // sub row
            tryAddDest(coordinates, from, 0, -d, &sub_col_blocked);
        }
        break;
    }
    case Chess::Type::kPawn: {
        qint8 direction = side == Chess::Side::kWhite ? 1 : -1;

        Coordinate target;

        // 一般情况
        target.setCoordinateBaseOn(from, direction * 1, 0);
        if (target.isValid() && cellIsEmpty(target))
        {
            tryAddDest(coordinates, from, direction * 1, 0);
        }

        // 未移动过
        target.setCoordinateBaseOn(from, direction * 2, 0);
        if (!getChess(from).isMoved() && target.isValid() && cellIsEmpty(Coordinate(from, direction * 1, 0)) &&
            cellIsEmpty(target))
        {
            tryAddDest(coordinates, from, direction * 2, 0);
        }

        // 吃棋情况
        target.setCoordinateBaseOn(from, direction * 1, -1);
        if (target.isValid() && !cellIsEmpty(target))
        {
            tryAddDest(coordinates, from, direction * 1, -1);
        }
        target.setCoordinateBaseOn(from, direction * 1, 1);
        if (target.isValid() && !cellIsEmpty(target))
        {
            tryAddDest(coordinates, from, direction * 1, 1);
        }

        break;
    }
    default: {
        Q_ASSERT(0);
        break;
    }
    }

    return coordinates;
}

QString Chessboard::getCellName(const Coordinate &coor)
{
    return getCellName(coor.getRow(), coor.getCol());
}

QString Chessboard::getCellName(const quint8 row, const quint8 col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    const QString CELL_NAMES[8][8] = {
        {"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"}, //
        {"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"}, //
        {"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"}, //
        {"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"}, //
        {"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"}, //
        {"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"}, //
        {"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"}, //
        {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"}, //
    };
    return CELL_NAMES[row - 1][col - 1];
}

void Chessboard::tryAddDest(Coordinates &coordinates, const Coordinate &base, const qint8 d_row, const qint8 d_col,
                            bool *p_blocked)
{
    // 当前棋子自身所在坐标，返回
    if (d_row == 0 && d_col == 0)
    {
        return;
    }

    // 已被其他棋子阻挡，返回
    if (p_blocked != nullptr && *p_blocked == true)
    {
        return;
    }

    // 超出棋盘，返回
    const Coordinate target(base, d_row, d_col);
    if (!target.isValid())
    {
        return;
    }

    // 棋格没有棋子，添加到可达列表
    if (cellIsEmpty(target))
    {
        coordinates.insert(target);
    }
    // 棋格有棋子，但为不同阵营，添加到可达列表，并标记阻挡
    else if (!getChess(base).isSameTeam(getChess(target)))
    {
        coordinates.insert(target);
        if (p_blocked != nullptr)
        {
            *p_blocked = true;
        }
    }
    else if (p_blocked != nullptr)
    {
        *p_blocked = true;
    }
}

} // namespace qtchess
