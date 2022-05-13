#ifndef REQUEST_H
#define REQUEST_H

#include "algorithms.h"

#include <QMainWindow>
#include <QListWidgetItem>

using namespace std;

enum action
{
    ADD_POINT,
    RED_POINT,
    DRAW,
    DRAW_WITH_DELAY,
    NO_ALG
};

struct request{
    enum action action;
    point_t new_point;
    line_list_t lines;
    point_t last_point;
    QString color_fill;
    QString color_line;
    QString color_bg;
    vector<QListWidgetItem> items;
    canvas_t canvas;
};

using request_t = struct request;

error_code_t switch_action(request_t &request);
#endif // REQUEST_H
