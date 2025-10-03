#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget{parent}
{}

void DrawingCanvas::ClearCanvas()
{
    points.clear();
    UpperHull.clear();
    LowerHull.clear();
    ConvexHull.clear();
    SlowConvex.clear();
    Edges.clear();
    iteration=0;
    update();
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        points.append(event->pos());
        ConvexHull.clear();
        SlowConvex.clear();
        Edges.clear();
        iteration=0;
        update();
    }
}

void DrawingCanvas::CalculateSlowConvex()
{
    Edges.clear();
    SlowConvex.clear();
    ConvexHull.clear();
    iteration=0;

    for (int i = 0; i < points.size(); i++){
        for (int j = 0; j< points.size(); j++){
            if (i == j) continue;

            iteration++;

            QPoint p = points[i];
            QPoint q = points[j];

            bool valid = true;

            for (int k = 0; k < points.size(); ++k) {

                if (k == i || k == j) continue;
                QPoint r = points[k];

                iteration++;

                if (((q.x() - p.x()) * (r.y() - p.y()) - (q.y() - p.y()) * (r.x() - p.x()))>0){
                    valid = false;
                    break;
                }
            }
            if (valid)
                Edges.append(qMakePair(p, q));
        }
    }

    if (!Edges.isEmpty()) {
        QPoint start = Edges[0].first;
        for (const auto &edge : Edges) {
            if (edge.first.x() < start.x() || (edge.first.x() == start.x() && edge.first.y() < start.y())) {
                start = edge.first;
            }
        }

        SlowConvex.append(start);
        QPoint current = start;

        while (true) {

            bool foundNext = false;
            QPoint nextPoint;

            for (const auto &edge : Edges) {
                if (edge.first == current) {
                    nextPoint = edge.second;
                    foundNext = true;
                    break;
                }
            }

            if (!foundNext || nextPoint == start)
                break;

            SlowConvex.append(nextPoint);
            current = nextPoint;
        }
    }
    update();
}

void DrawingCanvas::CalculateConvexHull(){

    UpperHull.clear();
    LowerHull.clear();
    Edges.clear();
    ConvexHull.clear();
    SlowConvex.clear();
    iteration = 0;

    if (points.isEmpty() || points.size()<2){
        return;
    }
    std::sort(points.begin(), points.end(), [](const QPoint &a, const QPoint &b){
         return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
    });

    UpperHull.append(points[0]);
    UpperHull.append(points[1]);

    for (int i = 2; i < points.size(); i++) {
        UpperHull.append(points[i]);

        while (UpperHull.size() > 2) {

            iteration++;

            int n = UpperHull.size();
            QPoint a = UpperHull[n - 3];
            QPoint b = UpperHull[n - 2];
            QPoint c = UpperHull[n - 1];

            double cross = (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());


            if (cross <= 0) {
                UpperHull.remove(n - 2);
            } else {
                break;
            }
        }
    }

    LowerHull.append(points[points.size() - 1]);
    LowerHull.append(points[points.size() - 2]);

    for (int i = points.size() - 3; i >= 0; i--) {
        LowerHull.append(points[i]);

        while (LowerHull.size() > 2) {

            iteration++;

            int n = LowerHull.size();
            QPoint a = LowerHull[n - 3];
            QPoint b = LowerHull[n - 2];
            QPoint c = LowerHull[n - 1];

            double cross = (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());

            if (cross <= 0) {
                LowerHull.remove(n - 2);
            } else {
                break;
            }
        }
    }

    for (const QPoint &p : UpperHull)
        ConvexHull.append(p);

    for (int i = 1; i < LowerHull.size() - 1; ++i)
        ConvexHull.append(LowerHull[i]);

    update();
}


void DrawingCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QPen pen(Qt::blue, 5, Qt::SolidLine);
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);
    font.setBold(true);

    painter.drawText(10, 20, "Number of points: " + QString::number(points.size()));
    painter.drawText(10, 40, "Number of Iterations: " + QString::number(iteration));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    if (!ConvexHull.isEmpty()){
        pen.setColor(Qt::blue);
        painter.setPen(pen);
        for (int i = 0; i < ConvexHull.size(); i++){
            painter.drawLine(ConvexHull[i],ConvexHull[(i+1)% ConvexHull.size()]);
        }
    }

    if (!SlowConvex.isEmpty()) {
        pen.setColor(Qt::green);
        painter.setPen(pen);
        for (int i = 0; i < SlowConvex.size(); i++){
            painter.drawLine(SlowConvex[i],SlowConvex[(i+1)% SlowConvex.size()]);
        }
    }

    QPen dotPen(Qt::red, 8, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(dotPen);
    for (const QPoint &dot : points) {
        painter.drawPoint(dot);
    }
}
