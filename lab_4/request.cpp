#include "request.h"
#include <QMessageBox>

ret_data_t switch_action_circle(request_t &request)
{
    ret_data_t er;
    er.radius = 20;

    switch (request.action)
    {
    case ORDINARY:
        er = Circle_Ordinary(request.canvas, request.color, request.center, request.radius, request.k, request.pix_size, request.flag);
        break;
    case CANON:
        er = Circle_Canon(request.canvas, request.color, request.center, request.radius, request.k, request.pix_size, request.flag);
        break;
    case PARAM:
        er = Circle_Param(request.canvas, request.color, request.center, request.radius, request.k, request.pix_size, request.flag);
        break;
    case BRESENHAM:
        er = Circle_Bresenham(request.canvas, request.color, request.center, request.radius, request.k, request.pix_size, request.flag);
        break;
    case MIDPOINT:
        er = Circle_MidPoint(request.canvas, request.color, request.center, request.radius, request.k, request.pix_size, request.flag);
        break;
    case NO_ALG:
        break;
    }
    return er;
}


ret_data_t switch_action_ellipse(request_t &request)
{
    ret_data_t er;
    er.radius = 0;

    switch (request.action)
    {
    case ORDINARY:
        er = Ellipse_Ordinary(request.canvas, request.color, request.center, request.a, request.b, request.k, request.pix_size, request.flag);
        break;
    case CANON:
        er = Ellipse_Canon(request.canvas, request.color, request.center, request.a, request.b, request.k, request.pix_size, request.flag);
        break;
    case PARAM:
        er = Ellipse_Param(request.canvas, request.color, request.center, request.a, request.b, request.k, request.pix_size, request.flag);
        break;
    case BRESENHAM:
        er = Ellipse_Bresenham(request.canvas, request.color, request.center, request.a, request.b, request.k, request.pix_size, request.flag);
        break;
    case MIDPOINT:
        er = Ellipse_MidPoint(request.canvas, request.color, request.center, request.a, request.b, request.k, request.pix_size, request.flag);
        break;
    case NO_ALG:
        break;
    }
    return er;
}
