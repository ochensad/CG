#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "error_code.h"
#include <QMainWindow>
#include "points.h"
#include <QGraphicsView>

#define PI 3.14159265
#define SEC 23000

#define WINDOW_WIDTH 970
#define WINDOW_HEIGHT 630

struct canvas
{
    QGraphicsScene *scene;
    QPixmap map;
    QImage im;
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
error_code_t add_point_alg(point_t &new_point, line_list_t &lines, point_t &last, canvas_t canvas ,QString &color);
void draw_lines(line_list_t lines, canvas_t canvas ,QString &color);

#endif // ALGORITHMS_H
