#ifndef POINT_H
#define POINT_H

class Point
{
protected:
    int _x;
    int _y;
    int _type;          // -1-不存在 0-顶点 1-入点 2-出点
    bool _vis;
    int _link;          // 环数
    int _mainLink;      // 交点在主多边形上的环数
    int _windowLink;    // 交点在窗口多边形上的环数

public:
    Point() {}
    Point(int x, int y, int type = 0, bool vis = false, int link = 0):
        _x(x),
        _y(y),
        _type(type),
        _vis(vis),
        _link(link) {}

    int x() const;
    int y() const;
    int type() const;
    bool visited() const;
    void visit(bool vis);
    int link() const;
    void setLink(int link);
    bool coincide(const Point& p) const;
    int mainLink() const;
    void setMainLink(int mainLink);
    int windowLink() const;
    void setWindowLink(int windowLink);
};

#endif // POINT_H
