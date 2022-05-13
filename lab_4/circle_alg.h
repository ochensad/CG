#ifndef CIRCLE_ALG_H
#define CIRCLE_ALG_H

#include "algorithms.h"

ret_data_t Circle_Ordinary(canvas_t canvas ,QString &color, point_t &center, int radius, float k, int pix_size, int flag);
ret_data_t Circle_Canon(canvas_t canvas ,QString &color, point_t &center, int radius, float k, int pix_size, int flag);
ret_data_t Circle_Param(canvas_t canvas ,QString &color, point_t &center, int radius, float k, int pix_size, int flag);
ret_data_t Circle_Bresenham(canvas_t canvas ,QString &color, point_t &center, int radius, float k, int pix_size, int flag);
ret_data_t Circle_MidPoint(canvas_t canvas ,QString &color, point_t &center, int radius, float k, int pix_size, int flag);
#endif // CIRCLE_ALG_H
