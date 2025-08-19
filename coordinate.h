#ifndef COORDINATE_H
#define COORDINATE_H

#include <qassert.h>
#include <qcontainerfwd.h>
#include <qpoint.h>
#include <qset.h>
#include <qtypes.h>

namespace qtchess
{

class Coordinate
{
  public:
    explicit Coordinate() : point_() {};
    explicit Coordinate(qint8 row, qint8 col) : point_(row, col) {};
    explicit Coordinate(const Coordinate &base, qint8 d_row, qint8 d_col)
        : point_(base.getRow() + d_row, base.getCol() + d_col) {};

    inline qint8 getRow() const noexcept
    {
        return point_.x();
    };
    inline qint8 getCol() const noexcept
    {
        return point_.y();
    };

    inline void setRow(const qint8 new_row) noexcept
    {
        Q_ASSERT(new_row >= 1 && new_row <= 8);
        point_.setX(new_row);
    };
    inline void setCol(const qint8 new_col) noexcept
    {
        Q_ASSERT(new_col >= 1 && new_col <= 8);
        point_.setY(new_col);
    };
    inline void setCoordinate(const qint8 new_row, const qint8 new_col) noexcept
    {
        point_.setX(new_row);
        point_.setY(new_col);
    };
    inline void setCoordinateBaseOn(const Coordinate &base, const qint8 d_row, const qint8 d_col)
    {
        point_.setX(base.getRow() + d_row);
        point_.setY(base.getCol() + d_col);
    };
    inline void reset() noexcept
    {
        point_.setX(0);
        point_.setY(0);
    };

    inline bool isValid() const noexcept
    {
        constexpr qint8 ROW_MIN = 1;
        constexpr qint8 ROW_MAX = 8;
        constexpr qint8 COL_MIN = 1;
        constexpr qint8 COL_MAX = 8;
        return (getRow() >= ROW_MIN && getRow() <= ROW_MAX && getCol() >= COL_MIN && getCol() <= COL_MAX);
    };

    bool isDirectNeighbour(const Coordinate &other) const noexcept
    {
        Q_ASSERT(isValid() && other.isValid());
        return getRow() == other.getRow() || getCol() == other.getCol();
    };
    bool isSlantNeighbour(const Coordinate &other) const noexcept
    {
        Q_ASSERT(isValid() && other.isValid());
        return std::abs(getRow() - other.getRow()) == std::abs(getCol() - other.getCol());
    };

    inline bool operator==(const Coordinate &other) const
    {
        return point_ == other.point_;
    };
    inline bool operator!=(const Coordinate &other) const
    {
        return point_ != other.point_;
    };

    using CoordinateSet = QSet<Coordinate>;

    CoordinateSet getDirectNeighbour() const noexcept;
    CoordinateSet getSlantNeighbour() const noexcept;
    CoordinateSet getAroundNeighbour() const noexcept;

  private:
    QPoint point_ = QPoint();
};

using Coordinates = Coordinate::CoordinateSet;

inline size_t qHash(const Coordinate &coordinate, size_t seed = 0)
{
    return ::qHash(QPoint(coordinate.getRow(), coordinate.getCol()));
}

} // namespace qtchess

#endif // COORDINATE_H
