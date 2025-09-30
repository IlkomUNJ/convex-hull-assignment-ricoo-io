#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>


class DrawingCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingCanvas(QWidget *parent = nullptr);
    void ClearCanvas();
    void CalculateSlowConvex();
    void CalculateConvexHull();


protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int iteration=0;
    QVector<QPoint> points;
    QVector<QPoint> UpperHull;
    QVector<QPoint> LowerHull;
    QVector<QPoint> ConvexHull;
    QVector<QPoint> SlowConvex;
    QVector<QPair<QPoint, QPoint>> Edges;
signals:
};

#endif // DRAWINGCANVAS_H
