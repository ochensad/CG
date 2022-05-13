#include "request.h"
#include <QMessageBox>

error_code_t switch_action(request_t &request)
{
    error_code_t er = OK;

    switch (request.action)
    {
    case ADD_POINT:
        er = add_point_alg(request.new_point, request.lines, request.last_point, request.canvas, request.color_line);
    case NO_ALG:
        break;
    }
    return er;
}
