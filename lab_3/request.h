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

error_code_t switch_action(request_t &request);
#endif // REQUEST_H
