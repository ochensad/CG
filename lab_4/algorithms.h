#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "error_code.h"
#include <QMainWindow>
#include "point.h"
#include <QGraphicsView>

#define PI 3.14159265
#define SEC 23000

struct canvas
{
    QGraphicsScene *scene;
    double width;
    double height;
};

using canvas_t = struct canvas;

struct ret_data
{
    float time;
    int radius;
};

using ret_data_t = struct ret_data;

int RoundToInt(double d);
point_t get_point(point_t point, const canvas_t &canvas);
error_code_t clear_canvas(const canvas_t &canvas);

#endif // ALGORITHMS_H
