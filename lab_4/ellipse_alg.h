#ifndef ELLIPSE_ALG_H
#define ELLIPSE_ALG_H

#include "algorithms.h"

ret_data_t Ellipse_Ordinary(canvas_t canvas ,QString &color, point_t &center, int a, int b, float k, int pix_size, int flag);
ret_data_t Ellipse_Canon(canvas_t canvas ,QString &color, point_t &center, int a, int b, float k, int pix_size, int flag);
ret_data_t Ellipse_Param(canvas_t canvas ,QString &color, point_t &center, int a, int b, float k, int pix_size, int flag);
ret_data_t Ellipse_Bresenham(canvas_t canvas ,QString &color, point_t &center, int a, int b, float k, int pix_size, int flag);
ret_data_t Ellipse_MidPoint(canvas_t canvas ,QString &color, point_t &center, int a, int b, float k, int pix_size, int flag);
#endif // ELLIPSE_ALG_H
