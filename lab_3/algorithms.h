#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "error_code.h"
#include <QMainWindow>
#include "point.h"
#include <QGraphicsView>

struct canvas
{
    QGraphicsScene *scene;
    double width;
    double height;
};

using canvas_t = struct canvas;

point_t get_point(point_t point, const canvas_t &canvas);
error_code_t clear_canvas(const canvas_t &canvas);
error_code_t line_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size);
error_code_t DDA_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size);
error_code_t BresenhamReal_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size);
error_code_t BresenhamInt_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size);
error_code_t Wu(canvas_t canvas ,QString &color, point_t start, point_t end, float k, int pix_size);
error_code_t BresenhanWS(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size, int level);
#endif // ALGORITHMS_H
