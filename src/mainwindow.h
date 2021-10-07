#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "point.h"
#include <iostream>
#include <algorithm>
#include <QVector>
#include <QList>
#include <QMouseEvent>
#include <QPainter>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef QList<Point> Link;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 点击右键，完成绘制
    void finishDrawingPolygon();
    // 判断点是否在多边形内部
    bool isInside(const Point& p, const Link& link);
    // 判断多边形点列是否是顺时针
    bool isClockwise(const Link& link);
    // 求所有交点，并加入顶点交点表
    void getIntersects();
    // 求交点
    Point getIntersection(const Point& u1, const Point& v1, const Point& u2, const Point& v2);
    // 求顶点在顶点交点表中的索引
    int index(const Point& p, const Link& link);
    // 顶点交点表合并
    void mergePointsByLink();
    // 裁剪函数
    void clip();
    // 没有交点特判
    void noIntersects(const Link& mainLink, const Link& windowLink);

protected:
    // 鼠标点击事件
    void mousePressEvent(QMouseEvent* e);
    // 绘制事件
    void paintEvent(QPaintEvent* e);

private slots:
    void on_action_main_polygon_triggered();
    void on_action_window_polygon_triggered();
    void on_action_clip_triggered();

private:
    Ui::MainWindow *ui;

    // 图形类型：0为窗口多边形，1为主多边形
    int mode = -1;

    // 点集
    Link bufferPoints;
    QVector<Link> mainPolygon;      // 主多边形
    int mainLinkNum = 0;            // 主多边形环数，0-外环
    QVector<Link> windowPolygon;    // 窗口多边形
    int windowLinkNum = 0;          // 窗口多边形环数
    QList<Point> intersects;        // 交点集
    QList<Link> clippedPolygon;     // 裁剪结果多边形

    // 顶点交点表
    QVector<Link> mainPointsByLink;
    QVector<Link> windowPointsByLink;
    Link mainPoints;
    Link windowPoints;
};
#endif // MAINWINDOW_H
