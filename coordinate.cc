#include "coordinate.h"

namespace qtchess
{

Coordinate::CoordinateSet Coordinate::getDirectNeighbour() const noexcept
{
    Q_ASSERT(isValid());
    CoordinateSet neighbours;
    Coordinate neighbour;
    for (size_t d = 1; d <= 8; d++)
    {
        neighbour.setCoordinate(d, 0);
        if (neighbour.isValid())
        {
            neighbours.insert(neighbour);
        }
        neighbour.setCoordinate(-d, 0);
        if (neighbour.isValid())
        {
            neighbours.insert(neighbour);
        }
        neighbour.setCoordinate(0, d);
        if (neighbour.isValid())
        {
            neighbours.insert(neighbour);
        }
        neighbour.setCoordinate(0, -d);
        if (neighbour.isValid())
        {
            neighbours.insert(neighbour);
        }
    }
    return neighbours;
}

Coordinate::CoordinateSet Coordinate::getSlantNeighbour() const noexcept
{
    Q_ASSERT(isValid());
    CoordinateSet neighbours;
    Coordinate neighbour;
    for (size_t d = 1; d <= 8; d++)
    {
        neighbour.setCoordinate(d, d);
        if (neighbour.isValid())
        {
            neighbours.insert(neighbour);
        }
        neighbour.setCoordinate(-d, d);
        if (neighbour.isValid())
        {
            neighbours.insert(neighbour);
        }
        neighbour.setCoordinate(d, -d);
        if (neighbour.isValid())
        {
            neighbours.insert(neighbour);
        }
        neighbour.setCoordinate(-d, -d);
        if (neighbour.isValid())
        {
            neighbours.insert(neighbour);
        }
    }
    return neighbours;
}

Coordinate::CoordinateSet Coordinate::getAroundNeighbour() const noexcept
{
    Q_ASSERT(isValid());
    CoordinateSet neighbours;
    Coordinate neighbour;
    neighbour.setCoordinate(-1, -1);
    if (neighbour.isValid())
    {
        neighbours.insert(neighbour);
    }
    neighbour.setCoordinate(-1, 0);
    if (neighbour.isValid())
    {
        neighbours.insert(neighbour);
    }
    neighbour.setCoordinate(-1, 1);
    if (neighbour.isValid())
    {
        neighbours.insert(neighbour);
    }
    neighbour.setCoordinate(0, -1);
    if (neighbour.isValid())
    {
        neighbours.insert(neighbour);
    }
    neighbour.setCoordinate(0, 1);
    if (neighbour.isValid())
    {
        neighbours.insert(neighbour);
    }
    neighbour.setCoordinate(1, -1);
    if (neighbour.isValid())
    {
        neighbours.insert(neighbour);
    }
    neighbour.setCoordinate(1, 0);
    if (neighbour.isValid())
    {
        neighbours.insert(neighbour);
    }
    neighbour.setCoordinate(1, 1);
    if (neighbour.isValid())
    {
        neighbours.insert(neighbour);
    }

    return neighbours;
}

} // namespace qtchess
