#ifndef POINTS_H
#define POINTS_H

#include <vector>
#include "point.h"
using namespace std;

struct line
{
    point_t start;
    point_t end;
};

using line_t = struct line;

struct line_list
{
    vector<line_t> lines;
};

using line_list_t = struct line_list;
#endif // POINTS_H
