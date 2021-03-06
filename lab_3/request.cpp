#include "request.h"
#include <QMessageBox>

ret_data_t switch_action(request_t &request)
{
    ret_data_t er;
    er.a = 0;
    er.steps = 0;

    switch (request.action)
    {
    case DDA:
        er = DDA_algorithm(request.canvas, request.color, request.start, request.end, request.k, request.pix_size);
        break;
    case ORDINARYLINE:
        er = line_algorithm(request.canvas, request.color, request.start, request.end, request.k, request.pix_size);
        break;
    case B_REAL:
        er = BresenhamReal_algorithm(request.canvas, request.color, request.start, request.end, request.k, request.pix_size);
        break;
    case B_INT:
        er = BresenhamInt_algorithm(request.canvas, request.color, request.start, request.end, request.k, request.pix_size);
        break;
    case WU:
        er = Wu(request.canvas, request.color, request.start, request.end, request.k, request.pix_size);
        break;
    case B_WS:
        er = BresenhanWS(request.canvas, request.color, request.start, request.end, request.k, request.pix_size, 10);
        break;
    case QUIT:
        QMessageBox::critical(NULL, "Пока", "пока пока");
        break;
    case NO_ALG:
        break;
    }
    return er;
}
