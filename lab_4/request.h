#ifndef REQUEST_H
#define REQUEST_H

#include "circle_alg.h"
#include "ellipse_alg.h"

#include <QMainWindow>

using namespace std;

enum action
{
    CANON,
    PARAM,
    BRESENHAM,
    MIDPOINT,
    ORDINARY,
    NO_ALG
};

enum type
{
    CIRCLE,
    ELLIPSE,
    NO_TYPE
};

struct request{
    enum action action;
    enum type type;
    point_t center;
    int a;
    int b;
    int radius;
    QString color;
    canvas_t canvas;
    float k;
    int pix_size;
    int flag;
};

using request_t = struct request;

ret_data_t switch_action_circle(request_t &request);
ret_data_t switch_action_ellipse(request_t &request);
#endif // REQUEST_H
