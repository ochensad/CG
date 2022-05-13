#ifndef ERROR_CODE_H
#define ERROR_CODE_H

enum return_code
{
    OK,
    ERROR_NO_POINTS,
    ERROR_NO_COLOR,
    SAME_POINT,
    NO_LINES,
    ERROR_SCENE,
    ERROR_NO_TYPE
};

using error_code_t = enum return_code;

void error_message(error_code_t error);
#endif // ERROR_CODE_H
