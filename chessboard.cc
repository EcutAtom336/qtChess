#include "chessboard.h"

#include <cstddef>

#include <qassert.h>
#include <qcontainerfwd.h>
#include <qimage.h>
#include <qlist.h>
#include <qlogging.h>
#include <qpoint.h>
#include <qtypes.h>

#include "chess.h"

qtchess::Chessboard::Chessboard()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            board_[i][j] = nullptr;
        }
    }
}

void qtchess::Chessboard::init(Mode mode)
{
    clear();

    if (mode == Mode::kStandard)
    {

        for (size_t col = 1; col <= 8; col++)
        {
            addChess(2, col, Chess::Type::kWhitePawn);
            addChess(7, col, Chess::Type::kBlackPawn);
        }

        addChess(1, 1, Chess::Type::kWhiteRook);
        addChess(1, 2, Chess::Type::kWhiteKnight);
        addChess(1, 3, Chess::Type::kWhiteBishop);
        addChess(1, 4, Chess::Type::kWhiteQueen);
        addChess(1, 5, Chess::Type::kWhiteKing);
        addChess(1, 6, Chess::Type::kWhiteBishop);
        addChess(1, 7, Chess::Type::kWhiteKnight);
        addChess(1, 8, Chess::Type::kWhiteRook);

        addChess(8, 1, Chess::Type::kBlackRook);
        addChess(8, 2, Chess::Type::kBlackKnight);
        addChess(8, 3, Chess::Type::kBlackBishop);
        addChess(8, 4, Chess::Type::kBlackQueen);
        addChess(8, 5, Chess::Type::kBlackKing);
        addChess(8, 6, Chess::Type::kBlackBishop);
        addChess(8, 7, Chess::Type::kBlackKnight);
        addChess(8, 8, Chess::Type::kBlackRook);
    }
}

void qtchess::Chessboard::clear()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board_[i][j] != nullptr)
            {
                delete board_[i][j];
                board_[i][j] = nullptr;
            }
        }
    }
}

quint8 qtchess::Chessboard::count()
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

void qtchess::Chessboard::addChess(const Coordinate &coor, const enum Chess::Type t)
{
    addChess(coor.row(), coor.col(), t);
}

void qtchess::Chessboard::addChess(const quint8 row, const quint8 col, enum Chess::Type type)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    Q_ASSERT(getChess(row, col) == nullptr);
    board_[row - 1][col - 1] = new Chess(type);
}

void qtchess::Chessboard::removeChess(const Coordinate &coor)
{
    removeChess(coor.row(), coor.col());
}

void qtchess::Chessboard::removeChess(const quint8 row, const quint8 col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    Q_ASSERT(getChess(row, col) != nullptr);
    delete board_[row - 1][col - 1];
    board_[row - 1][col - 1] = nullptr;
}

qtchess::Chess *qtchess::Chessboard::getChess(const Coordinate &coor)
{
    return getChess(coor.row(), coor.col());
}

qtchess::Chess *qtchess::Chessboard::getChess(const quint8 row, const quint8 col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    return board_[row - 1][col - 1];
}

void qtchess::Chessboard::moveChess(const Coordinate &old_coor, const Coordinate &new_coor)
{
    moveChess(old_coor.row(), old_coor.col(), new_coor.row(), new_coor.col());
}

void qtchess::Chessboard::moveChess(const quint8 old_row, const quint8 old_col, const quint8 new_row,
                                    const quint8 new_col)
{
    Q_ASSERT(old_row >= 1 && old_row <= 8 && old_col >= 1 && old_col <= 8 && new_row >= 1 && new_row <= 8 &&
             new_col >= 1 && new_col <= 8);
    Q_ASSERT(getChess(old_row, old_col) != nullptr);
    if (getChess(new_row, new_col))
    {
        removeChess(new_row, new_col);
    }
    board_[new_row - 1][new_col - 1] = board_[old_row - 1][old_col - 1];
    board_[old_row - 1][old_col - 1] = nullptr;
    board_[new_row - 1][new_col - 1]->setMoved();
}

QList<qtchess::Chessboard::Coordinate> qtchess::Chessboard::getReachable(const Coordinate &coor)
{
    QList<Chessboard::Coordinate> dest_list = QList<Chessboard::Coordinate>();

    Chess *p_chess = getChess(coor);
    Q_ASSERT(p_chess);

    enum Chess::Type type = p_chess->getType();

    switch (type)
    {
    case Chess::Type::kWhiteKing:
    case Chess::Type::kBlackKing: {
        // 棋子可能到达的范围
        for (qint8 d_row : {-1, 0, 1})
        {
            for (qint8 d_col : {-1, 0, 1})
            {
                tryAddDest(dest_list, coor, d_row, d_col);
            }
        }

        // TODO: 特殊情况：王车易位

        // TODO: 删除送将的情况
        break;
    }
    case qtchess::Chess::Type::kWhiteQueen:
    case qtchess::Chess::Type::kBlackQueen: {
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
            tryAddDest(dest_list, coor, d, 0, &add_row_blocked);
            // sub row
            tryAddDest(dest_list, coor, -d, 0, &sub_row_blocked);
            // add col
            tryAddDest(dest_list, coor, 0, d, &add_col_blocked);
            // sub row
            tryAddDest(dest_list, coor, 0, -d, &sub_col_blocked);

            // 斜走
            // add row add col
            tryAddDest(dest_list, coor, d, d, &add_row_add_col_blocked);
            // add row sub col
            tryAddDest(dest_list, coor, d, -d, &add_row_sub_col_blocked);
            // sub row add col
            tryAddDest(dest_list, coor, -d, d, &sub_row_add_col_blocked);
            // sub row sub col
            tryAddDest(dest_list, coor, -d, -d, &sub_row_sub_col_blocked);
        }
        break;
    }
    case Chess::Type::kWhiteBishop:
    case Chess::Type::kBlackBishop: {
        bool add_row_add_col_blocked = false;
        bool add_row_sub_col_blocked = false;
        bool sub_row_add_col_blocked = false;
        bool sub_row_sub_col_blocked = false;
        for (quint8 d = 1; d <= 7; ++d)
        {
            // 斜走
            // add row add col
            tryAddDest(dest_list, coor, d, d, &add_row_add_col_blocked);
            // add row sub col
            tryAddDest(dest_list, coor, d, -d, &add_row_sub_col_blocked);
            // sub row add col
            tryAddDest(dest_list, coor, -d, d, &sub_row_add_col_blocked);
            // sub row sub col
            tryAddDest(dest_list, coor, -d, -d, &sub_row_sub_col_blocked);
        }
        break;
    }
    case Chess::Type::kWhiteKnight:
    case Chess::Type::kBlackKnight: {

        tryAddDest(dest_list, coor, 2, 1);
        tryAddDest(dest_list, coor, 2, -1);
        tryAddDest(dest_list, coor, -2, 1);
        tryAddDest(dest_list, coor, -2, -1);

        tryAddDest(dest_list, coor, 1, 2);
        tryAddDest(dest_list, coor, -1, 2);
        tryAddDest(dest_list, coor, 1, -2);
        tryAddDest(dest_list, coor, -1, -2);

        break;
    }
    case Chess::Type::kWhiteRook:
    case Chess::Type::kBlackRook: {
        // 棋子可能到达的范围
        bool add_row_blocked = false;
        bool sub_row_blocked = false;
        bool add_col_blocked = false;
        bool sub_col_blocked = false;
        for (quint8 d = 1; d <= 7; ++d)
        {
            // 直走
            // add row
            tryAddDest(dest_list, coor, d, 0, &add_row_blocked);
            // sub row
            tryAddDest(dest_list, coor, -d, 0, &sub_row_blocked);
            // add col
            tryAddDest(dest_list, coor, 0, d, &add_col_blocked);
            // sub row
            tryAddDest(dest_list, coor, 0, -d, &sub_col_blocked);
        }
        break;
    }
    case Chess::Type::kWhitePawn:
    case Chess::Type::kBlackPawn: {
        qint8 direction = type == Chess::Type::kWhitePawn ? 1 : -1;

        // 一般情况
        if (coor.operateIsValid(direction * 1, 0) && getChess(Coordinate(coor, direction * 1, 0)) == nullptr)
        {
            tryAddDest(dest_list, coor, direction * 1, 0);
        }

        // 未移动过
        if (!getChess(coor)->isMoved() && coor.operateIsValid(direction * 2, 0) &&
            getChess(Coordinate(coor, direction * 1, 0)) == nullptr &&
            getChess(Coordinate(coor, direction * 2, 0)) == nullptr)
        {
            tryAddDest(dest_list, coor, direction * 2, 0);
        }

        // 吃棋情况
        if (coor.operateIsValid(direction * 1, -1) && getChess(Coordinate(coor, direction * 1, -1)) != nullptr)
        {
            tryAddDest(dest_list, coor, direction * 1, -1);
        }
        if (coor.operateIsValid(direction * 1, 1) && getChess(Coordinate(coor, direction * 1, 1)) != nullptr)
        {
            tryAddDest(dest_list, coor, direction * 1, 1);
        }

        break;
    }
    default: {
        Q_ASSERT(0);
        break;
    }
    }

    return dest_list;
}

QString qtchess::Chessboard::getCellName(const Coordinate &coor)
{
    return getCellName(coor.row(), coor.col());
}

QString qtchess::Chessboard::getCellName(const quint8 row, const quint8 col)
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

void qtchess::Chessboard::tryAddDest(QList<Chessboard::Coordinate> &list, const Chessboard::Coordinate &base,
                                     const qint8 d_row, const qint8 d_col, bool *p_blocked)
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
    if (!base.operateIsValid(d_row, d_col))
    {
        return;
    }

    Chessboard::Coordinate dest_coor = Coordinate(base, d_row, d_col);
    Chess *dest_chess = getChess(dest_coor);

    // 棋格没有棋子，添加到可达列表
    if (dest_chess == nullptr)
    {
        list.append(dest_coor);
    }
    // 棋格有棋子，但为不同阵营，添加到可达列表，并标记阻挡
    else if (!getChess(base)->isSameTeam(*dest_chess))
    {
        list.append(dest_coor);
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

qtchess::Chessboard::Coordinate::Coordinate(quint8 row, quint8 col) : point_(row, col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
}

qtchess::Chessboard::Coordinate::Coordinate(const Chessboard::Coordinate &base, qint8 d_row, qint8 d_col)
    : point_(base.row() + d_row, base.col() + d_col)
{
    Q_ASSERT(base.row() + d_row >= 1 && base.row() + d_row <= 8 && base.col() + d_col >= 1 && base.col() + d_col <= 8);
}

quint8 qtchess::Chessboard::Coordinate::row() const
{
    return point_.x();
}

quint8 qtchess::Chessboard::Coordinate::col() const
{
    return point_.y();
}

void qtchess::Chessboard::Coordinate::setRow(const quint8 new_row)
{
    Q_ASSERT(new_row >= 1 && new_row <= 8);
    point_.setX(new_row);
}

void qtchess::Chessboard::Coordinate::setCol(const quint8 new_col)
{
    Q_ASSERT(new_col >= 1 && new_col <= 8);
    point_.setX(new_col);
}

bool qtchess::Chessboard::Coordinate::operateIsValid(const qint8 d_row, const qint8 d_col) const
{
    qint8 new_row = row() + d_row;
    qint8 new_col = col() + d_col;
    return (new_row >= 1 && new_row <= 8 && new_col >= 1 && new_col <= 8) ? true : false;
}

bool qtchess::Chessboard::Coordinate::operator==(const Coordinate &other) const
{
    return point_ == other.point_;
}

bool qtchess::Chessboard::Coordinate::operator!=(const Coordinate &other) const
{
    return point_ != other.point_;
}

qtchess::Chessboard::Coordinate qtchess::Chessboard::Coordinate::operator+(const Coordinate &other) const
{
    return Coordinate(row() + other.row(), col() + other.col());
}

qtchess::Chessboard::Coordinate qtchess::Chessboard::Coordinate::operator-(const Coordinate &other) const
{
    return Coordinate(row() - other.row(), col() - other.col());
}

qtchess::Chessboard::Coordinate &qtchess::Chessboard::Coordinate::operator+=(const Coordinate &other)
{
    point_ += other.point_;
    return *this;
}

qtchess::Chessboard::Coordinate &qtchess::Chessboard::Coordinate::operator-=(const Coordinate &other)
{
    point_ -= other.point_;
    return *this;
}
