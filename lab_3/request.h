#ifndef REQUEST_H
#define REQUEST_H

#include "algorithms.h"

#include <QMainWindow>

using namespace std;

enum action
{
    DDA,
    ORDINARYLINE,
    NO_ALG,
    B_REAL,
    B_INT,
    WU,
    B_WS,
    QUIT
};

struct request{
    enum action action;
    point_t start;
    point_t end;
    QString color;
    canvas_t canvas;
    float k;
    int pix_size;
};

using request_t = struct request;

ret_data_t switch_action(request_t &request);
#endif // REQUEST_H
