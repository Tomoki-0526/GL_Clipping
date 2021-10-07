#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bufferPoints.clear();
    mainPolygon.clear();
    windowPolygon.clear();
    intersects.clear();
    clippedPolygon.clear();
    mainPointsByLink.clear();
    windowPointsByLink.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_main_polygon_triggered()
{
    mode = 1;
    bufferPoints.clear();
}

void MainWindow::on_action_window_polygon_triggered()
{
    mode = 0;
    bufferPoints.clear();
}

bool MainWindow::isInside(const Point& p, const Link& link)
{
    int i, j, c = 0;
    int n = link.size();
    for (i = 0, j = n - 1; i < n; j = i++) {
        if (((link.at(i).y() > p.y()) != (link.at(j).y() > p.y())) &&
                (p.x() < (link.at(j).x() - link.at(i).x()) * (p.y() - link.at(i).y()) / (link.at(j).y() - link.at(i).y()) + link.at(i).x())) {
            c = !c;
        }
    }
    return c;
}

bool MainWindow::isClockwise(const Link& link)
{
    int i, res = 0;
    for (i = 0; i < link.size() - 1; ++i) {
        res += link.at(i).x() * link.at(i + 1).y() -
                link.at(i).y() * link.at(i + 1).x();
    }
    res += link.at(i).x() * link.at(0).y() - link.at(i).y() * link.at(0).x();
    return res < 0;
}

void MainWindow::finishDrawingPolygon()
{
    // 当前绘制的是窗口多边形
    if (mode == 0) {
        if (windowLinkNum == 0) {
            for (int i = 0; i < bufferPoints.size(); ++i) {
                bufferPoints[i].setLink(windowLinkNum);
            }
            windowPolygon.push_back(bufferPoints);
            windowLinkNum++;
        }
        else {
            for (int i = 0; i < bufferPoints.size(); ++i) {
                bufferPoints[i].setLink(windowLinkNum);
            }
            reverse(bufferPoints.begin(), bufferPoints.end());
            windowPolygon.push_back(bufferPoints);
        }
    }
    // 当前绘制的是主多边形
    else {
        if (mainLinkNum == 0) {
            for (int i = 0; i < bufferPoints.size(); ++i) {
                bufferPoints[i].setLink(mainLinkNum);
            }
            mainPolygon.push_back(bufferPoints);
            mainLinkNum++;
        }
        else {
            for (int i = 0; i < bufferPoints.size(); ++i) {
                bufferPoints[i].setLink(mainLinkNum);
            }
            reverse(bufferPoints.begin(), bufferPoints.end());
            mainPolygon.push_back(bufferPoints);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QPoint cur = e->pos();
    Point p(cur.x(), cur.y());

    if (mode == 0 || mode == 1) {
        if (e->button() == Qt::LeftButton) {
            bufferPoints.push_back(p);
            update();
        }
        else if(e->button() == Qt::RightButton) {
            if (bufferPoints.size() < 3) {
                bufferPoints.clear();
                update();
                return;
            }
            finishDrawingPolygon();
            bufferPoints.clear();
            update();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    // 主多边形用蓝色，窗口多边形用黑色，裁剪结果用红色
    QPainter painter(this);

    // 绘制bufferPoints
    if (!bufferPoints.empty()) {
        // 当前绘制的是主多边形的点
        if (mode == 1) {
            painter.setPen(QPen(Qt::blue, 6, Qt::SolidLine, Qt::RoundCap));
        }
        // 当前绘制的是窗口多边形的点
        else {
            painter.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap));
        }
        for (auto& point: bufferPoints) {
            painter.drawPoint(point.x(), point.y());
        }
    }

    // 绘制主多边形
    if (!mainPolygon.isEmpty()) {
        for (auto& link: mainPolygon) {
            // 绘制点
            painter.setPen(QPen(Qt::blue, 6, Qt::SolidLine, Qt::RoundCap));
            for (auto& point: link) {
                painter.drawPoint(point.x(), point.y());
            }

            // 绘制边
            painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap));
            Point front, back;
            for (int i = 1; i < link.size(); ++i) {
                front = link.at(i);
                back = link.at(i - 1);
                painter.drawLine(front.x(), front.y(), back.x(), back.y());
            }
            front = link.at(0);
            back = link.at(link.size() - 1);
            painter.drawLine(front.x(), front.y(), back.x(), back.y());
        }
    }

    // 绘制窗口多边形
    if (!windowPolygon.isEmpty()) {
        for (auto& link: windowPolygon) {
            // 绘制点
            painter.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap));
            for (auto& point: link) {
                painter.drawPoint(point.x(), point.y());
            }

            // 绘制边
            painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
            Point front, back;
            for (int i = 1; i < link.size(); ++i) {
                front = link.at(i);
                back = link.at(i - 1);
                painter.drawLine(front.x(), front.y(), back.x(), back.y());
            }
            front = link.at(0);
            back = link.at(link.size() - 1);
            painter.drawLine(front.x(), front.y(), back.x(), back.y());
        }
    }

    // 绘制交点
    if (!intersects.isEmpty()) {
        painter.setPen(QPen(Qt::red, 6, Qt::SolidLine, Qt::RoundCap));
        for(auto& point: intersects) {
            painter.drawPoint(point.x(), point.y());
        }
    }

    // 绘制裁剪结果
    // 顶点
    if (!clippedPolygon.isEmpty()) {
        painter.setPen(QPen(Qt::red, 6, Qt::SolidLine, Qt::RoundCap));
        for(auto& link: clippedPolygon) {
            for(auto& point: link) {
                painter.drawPoint(point.x(), point.y());
            }
        }
    }
    // 线段
    if (!clippedPolygon.isEmpty()) {
        painter.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap));
        for (auto& link: clippedPolygon) {
            Point front, back;
            for (int i = 1; i < link.size(); ++i) {
                front = link.at(i);
                back = link.at(i - 1);
                painter.drawLine(front.x(), front.y(), back.x(), back.y());
            }
            front = link.at(0);
            back = link.at(link.size() - 1);
            painter.drawLine(front.x(), front.y(), back.x(), back.y());
        }
    }
}

Point MainWindow::getIntersection(const Point& u1, const Point& v1, const Point& u2, const Point& v2)
{
    // 判断平行
    int a1 = v1.y() - u1.y();
    int b1 = u1.x() - v1.x();
    int c1 = a1 * u1.x() + b1 * u1.y();
    int a2 = v2.y() - u2.y();
    int b2 = u2.x() - v2.x();
    int c2 = a2 * u2.x() + b2 * u2.y();
    int d = a1 * b2 - a2 * b1;
    if (d == 0) {
        return Point(-1, -1, -1);
    }

    // 判断交点是否在线段内部
    int x = (b2 * c1 - b1 * c2) / d;
    int y = (a1 * c2 - a2 * c1) / d;
    int dx_u1 = x - u1.x();
    int dx_v1 = x - v1.x();
    int dx_u2 = x - u2.x();
    int dx_v2 = x - v2.x();
    if (dx_u1 * dx_v1 > 0 || dx_u2 * dx_v2 > 0) {
        return Point(-1, -1, -1);
    }

    // 判断出入点
    if (d > 0) {
        return Point(x, y, 1);
    }
    else {
        return Point(x, y, 2);
    }
}

int MainWindow::index(const Point &p, const Link &link)
{
    for(int i = 0; i < link.size(); ++i) {
        if (p.coincide(link.at(i))) {
            return i;
        }
    }
    return -1;
}

void MainWindow::getIntersects()
{
    for (int i = 0; i < mainPolygon.size(); ++i) {  // 对主多边形的一个环
        for (int j = 0; j < windowPolygon.size(); ++j) {    // 对窗口多边形的一个环
            for(int p = 0; p < mainPolygon.at(i).size(); ++p) { // 对主多边形的一条边
                Point u1 = mainPolygon.at(i).at(p);
                Point v1;
                if (p == mainPolygon.at(i).size() - 1) {
                    v1 = mainPolygon.at(i).at(0);
                }
                else {
                    v1 = mainPolygon.at(i).at(p + 1);
                }
                for(int q = 0; q < windowPolygon.at(j).size(); ++q) {   // 对窗口多边形的一条边
                    Point u2 = windowPolygon.at(j).at(q);
                    Point v2;
                    if (q == windowPolygon.at(j).size() - 1) {
                        v2 = windowPolygon.at(j).at(0);
                    }
                    else {
                        v2 = windowPolygon.at(j).at(q + 1);
                    }
                    // 求交点
                    Point intersect = getIntersection(u1, v1, u2, v2);
                    if (intersect.type() == -1) {
                        continue;
                    }
                    // 插入主多边形表
                    int index_u1 = index(u1, mainPointsByLink.at(i));
                    int index_v1 = index(v1, mainPointsByLink.at(i));
                    if (index_v1 == 0) {
                        index_v1 = mainPointsByLink.at(i).size();
                    }
                    int index_insert_main = index_v1;
                    for (int k = index_u1; k < index_v1 - 1; ++k) {
                        if ((intersect.x() - mainPointsByLink.at(i).at(k).x()) *
                            (intersect.x() - mainPointsByLink.at(i).at(k + 1).x()) < 0) {
                            index_insert_main = k + 1;
                            break;
                        }
                    }
                    intersect.setMainLink(i);
                    // 插入窗口多边形表
                    int index_u2 = index(u2, windowPointsByLink.at(j));
                    int index_v2 = index(v2, windowPointsByLink.at(j));
                    if (index_v2 == 0) {
                        index_v2 = windowPointsByLink.at(j).size();
                    }
                    int index_insert_window = index_v2;
                    for (int k = index_u2; k < index_v2 - 1; ++k) {
                        if ((intersect.x() - windowPointsByLink.at(j).at(k).x()) *
                            (intersect.x() - windowPointsByLink.at(j).at(k + 1).x()) < 0) {
                            index_insert_window = k + 1;
                            break;
                        }
                    }
                    intersect.setWindowLink(j);

                    intersects.append(intersect);
                    mainPointsByLink[i].insert(index_insert_main, intersect);
                    windowPointsByLink[i].insert(index_insert_window, intersect);
                }
            }
        }
    }
    qDebug() << "----------------";
}

void MainWindow::clip()
{
    Link tmp;
    for (int k = 0; k < intersects.size(); ++k) {
        tmp.append(intersects[k]);
    }
    for (int k = 0; k < intersects.size(); ++k) {
        if (intersects[k].visited()) {
            continue;
        }

        Link link;  // 待加入结果的环
        Point startPoint = tmp[k];
        Point& curr = tmp[k];
        int polygon = 1;    // 从主多边形开始
        int numLink;        // 起始交点在主多边形上的环数
        if (curr.type() == 1) {
            numLink = curr.mainLink();
        }
        else {
            numLink = curr.windowLink();
        }
        int i;
        do {
            link.append(curr);
            curr.visit(true);
            if (curr.type() != 0) {
                int real_index = index(curr, intersects);
                intersects[real_index].visit(true);
            }
            if (curr.type() == 1) {
                numLink = curr.mainLink();
                i = index(curr, mainPointsByLink.at(numLink));
                i = (i == mainPointsByLink.at(numLink).size() - 1) ? 0 : i + 1;
                curr = mainPointsByLink.at(numLink).at(i);
                polygon = 1;
            }
            else if (curr.type() == 2) {
                numLink = curr.windowLink();
                i = index(curr, windowPointsByLink.at(numLink));
                i = (i == windowPointsByLink.at(numLink).size() - 1) ? 0 : i + 1;
                curr = windowPointsByLink.at(numLink).at(i);
                polygon = 0;
            }
            else {
                if (polygon == 1) {
                    i = (i == mainPointsByLink.at(numLink).size() - 1) ? 0 : i + 1;
                    curr = mainPointsByLink.at(numLink).at(i);
                }
                else {
                    i = (i == windowPointsByLink.at(numLink).size() - 1) ? 0 : i + 1;
                    curr = windowPointsByLink.at(numLink).at(i);
                }
            }
        } while (!curr.coincide(startPoint));
        clippedPolygon.append(link);
    }
}

void MainWindow::on_action_clip_triggered()
{
    mode = -1;

    for (int i = 0; i < mainPolygon.size(); ++i) {
        Link to_link;
        for (int j = 0; j < mainPolygon[i].size(); ++j) {
            to_link.append(mainPolygon[i][j]);
        }
        mainPointsByLink.append(to_link);
    }
    for (int i = 0; i < windowPolygon.size(); ++i) {
        Link to_link;
        for (int j = 0; j < windowPolygon[i].size(); ++j) {
            to_link.append(windowPolygon[i][j]);
        }
        windowPointsByLink.append(to_link);
    }

    // 求所有交点并加入顶点交点表
    getIntersects();
    update();

    // 裁剪
    // 如果没有交点，特判
    if (intersects.isEmpty()) {
        noIntersects(mainPolygon.at(0), windowPolygon.at(0));
    }
    else {
        clip();
    }
    update();
}

void MainWindow::noIntersects(const Link &mainLink, const Link &windowLink)
{
    // 主多边形在窗口外
    if (isInside(windowLink.at(0), mainLink)) {
        for (int i = 0; i < windowPolygon.size(); ++i) {
            clippedPolygon.append(windowPolygon.at(i));
        }
    }
    // 主多边形在窗口内
    else {
        for (int i = 0; i < mainPolygon.size(); ++i) {
            clippedPolygon.append(mainPolygon.at(i));
        }
    }
}
