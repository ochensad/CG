#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "error_code.h"
#include <QMainWindow>
#include "point.h"
#include <QGraphicsView>

#define PI 3.14159265

struct canvas
{
    QGraphicsScene *scene;
    double width;
    double height;
};

using canvas_t = struct canvas;

struct ret_data
{
    int steps;
    float a;
};

using ret_data_t = struct ret_data;

int RoundToInt(double d);
point_t get_point(point_t point, const canvas_t &canvas);
error_code_t clear_canvas(const canvas_t &canvas);
ret_data_t line_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size);
ret_data_t DDA_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size);
ret_data_t BresenhamReal_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size);
ret_data_t BresenhamInt_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size);
ret_data_t Wu(canvas_t canvas ,QString &color, point_t start, point_t end, float k, int pix_size);
ret_data_t BresenhanWS(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size, int level);
#endif // ALGORITHMS_H
