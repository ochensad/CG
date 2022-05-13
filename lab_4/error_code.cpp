#include "error_code.h"
#include <QMessageBox>

void error_message(error_code_t error)
{
    switch (error){

    case ERROR_NO_POINTS:
        QMessageBox::critical(NULL, "Ошибка", "Не выбраны точки");
        break;
    case ERROR_NO_COLOR:
        QMessageBox::critical(NULL, "Ошибка", "Не выбран цвет");
        break;
    case ERROR_SCENE:
        QMessageBox::critical(NULL, "Ошибка", "Нечего отменять");
        break;
    case ERROR_NO_ALG:
        QMessageBox::critical(NULL, "Ошибка", "Не выбран алгоритм");
        break;
    case ERROR_NO_TYPE:
        QMessageBox::critical(NULL, "Ошибка", "Не выбран тип");
        break;
    case OK:
        break;
    }

}
