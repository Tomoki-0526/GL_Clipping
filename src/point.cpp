#include "point.h"

int Point::x() const
{
    return _x;
}

int Point::y() const
{
    return _y;
}

int Point::type() const
{
    return _type;
}

bool Point::visited() const
{
    return _vis;
}

bool Point::coincide(const Point &p) const
{
    return (_x == p.x()) && (_y == p.y());
}

void Point::visit(bool vis)
{
    _vis = vis;
}

int Point::link() const
{
    return _link;
}

void Point::setLink(int link)
{
    _link = link;
}

int Point::mainLink() const
{
    return _mainLink;
}

void Point::setMainLink(int mainLink)
{
    _mainLink = mainLink;
}

int Point::windowLink() const
{
    return _windowLink;
}

void Point::setWindowLink(int windowLink)
{
    _windowLink = windowLink;
}
