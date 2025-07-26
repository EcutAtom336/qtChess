#include "chessboard.h"
#include "chess.h"
#include <cstddef>
#include <qassert.h>
#include <qcontainerfwd.h>
#include <qimage.h>
#include <qlist.h>
#include <qlogging.h>
#include <qpoint.h>
#include <qtypes.h>

chessboard::chessboard()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            board[i][j] = nullptr;
        }
    }
}

void chessboard::init(mode mode)
{
    clear();

    if (mode == mode::STANDAR)
    {

        for (size_t col = 1; col <= 8; col++)
        {
            addChess(2, col, chess::type::WHITE_PAWN);
            addChess(7, col, chess::type::BLACK_PAWN);
        }

        addChess(1, 1, chess::type::WHITE_ROOK);
        addChess(1, 2, chess::type::WHITE_KNIGHT);
        addChess(1, 3, chess::type::WHITE_BISHOP);
        addChess(1, 4, chess::type::WHITE_QUEEN);
        addChess(1, 5, chess::type::WHITE_KING);
        addChess(1, 6, chess::type::WHITE_BISHOP);
        addChess(1, 7, chess::type::WHITE_KNIGHT);
        addChess(1, 8, chess::type::WHITE_ROOK);

        addChess(8, 1, chess::type::BLACK_ROOK);
        addChess(8, 2, chess::type::BLACK_KNIGHT);
        addChess(8, 3, chess::type::BLACK_BISHOP);
        addChess(8, 4, chess::type::BLACK_QUEEN);
        addChess(8, 5, chess::type::BLACK_KING);
        addChess(8, 6, chess::type::BLACK_BISHOP);
        addChess(8, 7, chess::type::BLACK_KNIGHT);
        addChess(8, 8, chess::type::BLACK_ROOK);
    }
}

void chessboard::clear()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] != nullptr)
            {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
}

quint8 chessboard::count()
{
    quint8 cnt = 0;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] != nullptr)
            {
                cnt++;
            }
        }
    }
    return cnt;
}

void chessboard::addChess(const coordinate &coor, const enum chess::type t)
{
    addChess(coor.row(), coor.col(), t);
}

void chessboard::addChess(const quint8 row, const quint8 col, enum chess::type type)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    Q_ASSERT(getChess(row, col) == nullptr);
    board[row - 1][col - 1] = new chess(type);
}

void chessboard::removeChess(const coordinate &coor)
{
    removeChess(coor.row(), coor.col());
}

void chessboard::removeChess(const quint8 row, const quint8 col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    Q_ASSERT(getChess(row, col) != nullptr);
    delete board[row - 1][col - 1];
    board[row - 1][col - 1] = nullptr;
}

chess *chessboard::getChess(const coordinate &coor)
{
    return getChess(coor.row(), coor.col());
}

chess *chessboard::getChess(const quint8 row, const quint8 col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
    return board[row - 1][col - 1];
}

void chessboard::moveChess(const coordinate &old_coor, const coordinate &new_coor)
{
    moveChess(old_coor.row(), old_coor.col(), new_coor.row(), new_coor.col());
}

void chessboard::moveChess(const quint8 old_row, const quint8 old_col, const quint8 new_row, const quint8 new_col)
{
    Q_ASSERT(old_row >= 1 && old_row <= 8 && old_col >= 1 && old_col <= 8 && new_row >= 1 && new_row <= 8 &&
             new_col >= 1 && new_col <= 8);
    Q_ASSERT(getChess(old_row, old_col) != nullptr);
    if (getChess(new_row, new_col))
    {
        removeChess(new_row, new_col);
    }
    board[new_row - 1][new_col - 1] = board[old_row - 1][old_col - 1];
    board[old_row - 1][old_col - 1] = nullptr;
    board[new_row - 1][new_col - 1]->setMoved();
}

QList<chessboard::coordinate> chessboard::getReachable(const coordinate &coor)
{
    QList<chessboard::coordinate> dest_list = QList<chessboard::coordinate>();

    chess *p_chess = getChess(coor);
    Q_ASSERT(p_chess);

    enum chess::type type = p_chess->getType();

    switch (type)
    {
    case chess::type::WHITE_KING:
    case chess::type::BLACK_KING: {
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
    case chess::type::WHITE_QUEEN:
    case chess::type::BLACK_QUEEN: {
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
    case chess::type::WHITE_BISHOP:
    case chess::type::BLACK_BISHOP: {
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
    case chess::type::WHITE_KNIGHT:
    case chess::type::BLACK_KNIGHT: {

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
    case chess::type::WHITE_ROOK:
    case chess::type::BLACK_ROOK: {
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
    case chess::type::WHITE_PAWN:
    case chess::type::BLACK_PAWN: {
        qint8 direction = type == chess::type::WHITE_PAWN ? 1 : -1;

        // 一般情况
        if (coor.operateIsValid(direction * 1, 0) && getChess(coordinate(coor, direction * 1, 0)) == nullptr)
        {
            tryAddDest(dest_list, coor, direction * 1, 0);
        }

        // 未移动过
        if (!getChess(coor)->isMoved() && coor.operateIsValid(direction * 2, 0) &&
            getChess(coordinate(coor, direction * 2, 0)) == nullptr)
        {
            tryAddDest(dest_list, coor, direction * 2, 0);
        }

        // 吃棋情况
        if (coor.operateIsValid(direction * 1, -1) && getChess(coordinate(coor, direction * 1, -1)) != nullptr)
        {
            tryAddDest(dest_list, coor, direction * 1, -1);
        }
        if (coor.operateIsValid(direction * 1, 1) && getChess(coordinate(coor, direction * 1, 1)) != nullptr)
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

QString chessboard::getCellName(const coordinate &coor)
{
    return getCellName(coor.row(), coor.col());
}

QString chessboard::getCellName(const quint8 row, const quint8 col)
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

void chessboard::tryAddDest(QList<chessboard::coordinate> &list, const chessboard::coordinate &base, const qint8 d_row,
                            const qint8 d_col, bool *p_blocked)
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

    chessboard::coordinate dest_coor = coordinate(base, d_row, d_col);
    chess *dest_chess = getChess(dest_coor);

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

chessboard::coordinate::coordinate(quint8 row, quint8 col) : m_point(row, col)
{
    Q_ASSERT(row >= 1 && row <= 8 && col >= 1 && col <= 8);
}

chessboard::coordinate::coordinate(const chessboard::coordinate &base, qint8 d_row, qint8 d_col)
    : m_point(base.row() + d_row, base.col() + d_col)
{
    Q_ASSERT(base.row() + d_row >= 1 && base.row() + d_row <= 8 && base.col() + d_col >= 1 && base.col() + d_col <= 8);
}

quint8 chessboard::coordinate::row() const
{
    return m_point.x();
}

quint8 chessboard::coordinate::col() const
{
    return m_point.y();
}

void chessboard::coordinate::setRow(const quint8 new_row)
{
    Q_ASSERT(new_row >= 1 && new_row <= 8);
    m_point.setX(new_row);
}

void chessboard::coordinate::setCol(const quint8 new_col)
{
    Q_ASSERT(new_col >= 1 && new_col <= 8);
    m_point.setX(new_col);
}

bool chessboard::coordinate::operateIsValid(const qint8 d_row, const qint8 d_col) const
{
    qint8 new_row = row() + d_row;
    qint8 new_col = col() + d_col;
    return (new_row >= 1 && new_row <= 8 && new_col >= 1 && new_col <= 8) ? true : false;
}

bool chessboard::coordinate::operator==(const coordinate &other) const
{
    return m_point == other.m_point;
}

bool chessboard::coordinate::operator!=(const coordinate &other) const
{
    return m_point != other.m_point;
}

chessboard::coordinate chessboard::coordinate::operator+(const coordinate &other) const
{
    return coordinate(row() + other.row(), col() + other.col());
}

chessboard::coordinate chessboard::coordinate::operator-(const coordinate &other) const
{
    return coordinate(row() - other.row(), col() - other.col());
}

chessboard::coordinate &chessboard::coordinate::operator+=(const coordinate &other)
{
    m_point += other.m_point;
    return *this;
}

chessboard::coordinate &chessboard::coordinate::operator-=(const coordinate &other)
{
    m_point -= other.m_point;
    return *this;
}
