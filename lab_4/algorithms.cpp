#include "algorithms.h"
#include <math.h>

int RoundToInt(double d)
{
    return (int)round(d);
}

error_code_t clear_canvas(const canvas_t &canvas)
{
    if (!canvas.scene)
        return ERROR_SCENE;
    canvas.scene->clear();
    return OK;
}

point_t get_point(point_t point, const canvas_t &canvas)
{
    //point.x *= -1;
    point.x += (int) (canvas.width / 2);
    point.y *= -1;
    point.y += (int) (canvas.height / 2);
    return point;
}



