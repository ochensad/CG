#include "algorithms.h"
#include <math.h>

static int RoundToInt(double d)
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

error_code_t line_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end)
{
    start = get_point(start, canvas);
    end = get_point(end, canvas);

    QPen pen(color);
    pen.setWidth(2);

    canvas.scene->addLine(start.x, start.y, end.x, end.y, pen);
    return OK;
}

error_code_t DDA_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size)
{
    static int steps_DDA = 0;

    start = get_point(start, canvas);
    end = get_point(end, canvas);

    float x = start.x, y = start.y;

    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);

    if (start.x == end.x && start.y == end.y && start.x >= 0 && start.x <= canvas.width
            && start.y >= 0 && start.y <= canvas.height)
    {
        steps_DDA = 0;
        x = (int) (k * x + (1 - k) * (canvas.width / 2));
        y = (int) (k * y + (1 - k) * (canvas.height / 2));
        canvas.scene->addRect(x, y, pix_size, pix_size, pen ,brush);
        return OK;
    }

    int l = abs(end.x - start.x) >= abs(end.y - start.y) ? abs(end.x - start.x): abs(end.y - start.y);

    float dx = (float)(end.x - start.x) / l;
    float dy = (float)(end.y - start.y) / l;

    int x_prev = RoundToInt(x);
    int y_prev = RoundToInt(y);

    for(int i = 0; i <= l; i++)
    {
        int x_r = RoundToInt(x), y_r = RoundToInt(y);

        if (abs(x_r - x_prev) == 1 && abs(y_r - y_prev) == 1)
            steps_DDA++;

        x_prev = x_r;
        y_prev = y_r;

        if (x_r >= 0 && x_r <= canvas.width && y_r >= 0 && y_r <= canvas.height)
        {
            x_r = (int) (k * x_r + (1 - k) * (canvas.width / 2));
            y_r = (int) (k * y_r + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_r, y_r, pix_size, pix_size, pen ,brush);
        }

        x += dx;
        y += dy;
    }
    return OK;
}

static void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

error_code_t BresenhamReal_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size)
{
    static int steps_BReal = 0;

    start = get_point(start, canvas);
    end = get_point(end, canvas);

    int x_m = 0;
    int y_m = 0;

    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    pen.setBrush(brush);

    if (start.x == end.x && start.y == end.y && start.x >= 0 && start.x <= canvas.width
            && start.y >= 0 && start.y <= canvas.height)
    {
        steps_BReal = 0;
        x_m = (int) (k * start.x + (1 - k) * (canvas.width / 2));
        y_m = (int) (k * start.y + (1 - k) * (canvas.height / 2));
        canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        return OK;
    }
    int swap_f = 0;
    int dx = end.x - start.x;
    int dy = end.y - start.y;

    int sx = 1, sy = 1;
    if (dx < 0)
        sx = -1;
    else if (dx == 0)
        sx = 0;
    if (dy < 0)
        sy = -1;
    else if (dy == 0)
        sy = 0;

    dx = abs(dx);
    dy = abs(dy);

    float m = (float)dy/dx;
    if (m > 1)
    {
        swap(dx, dy);
        m = 1/m;
        swap_f = 1;
    }

    float error = m - 0.5f;
    int x = start.x, y = start.y;
    int prev_x = x;
    int prev_y = y;

    for(int i = 0; i <= dx; i++)
    {
        if (x >= 0 && x < canvas.width && y >= 0 && y < canvas.height)
        {
            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * y + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen, brush);
        }

        if (abs(x - prev_x) == 1 && abs(y - prev_y) == 1)
            steps_BReal++;

        prev_x = x;
        prev_y = y;

        if (error >= 0)
        {
            if (swap_f == 1)
                x += sx;
            else
                y += sy;
            error -= 1;
        }

        if (error < 0)
        {
            if (swap_f == 1)
                y += sy;
            else
                x += sx;
        }

        error += m;
    }
    return OK;
}


error_code_t BresenhamInt_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size)
{
    static int steps_BInt = 0;

    start = get_point(start, canvas);
    end = get_point(end, canvas);

    int x_m = 0;
    int y_m = 0;

    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    pen.setBrush(brush);

    if (start.x == end.x && start.y == end.y && start.x >= 0 && start.x <= canvas.width
            && start.y >= 0 && start.y <= canvas.height)
    {
        steps_BInt = 0;
        x_m = (int) (k * start.x + (1 - k) * (canvas.width / 2));
        y_m = (int) (k * start.y + (1 - k) * (canvas.height / 2));
        canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        return OK;
    }
    int swap_f = 0;
    int dx = end.x - start.x;
    int dy = end.y - start.y;

    int sx = 1, sy = 1;
    if (dx < 0)
        sx = -1;
    else if (dx == 0)
        sx = 0;
    if (dy < 0)
        sy = -1;
    else if (dy == 0)
        sy = 0;

    dx = abs(dx);
    dy = abs(dy);

    float m = (float)dy/dx;
    if (m > 1)
    {
        swap(dx, dy);
        m = 1/m;
        swap_f = 1;
    }

    float error = 2 * dy - dx;
    int x = start.x, y = start.y;
    int prev_x = x;
    int prev_y = y;

    for(int i = 0; i <= dx; i++)
    {
        if (x >= 0 && x < canvas.width && y >= 0 && y < canvas.height)
        {
            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * y + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen, brush);
        }

        if (abs(x - prev_x) == 1 && abs(y - prev_y) == 1)
            steps_BInt++;

        prev_x = x;
        prev_y = y;

        if (error >= 0)
        {
            if (swap_f == 1)
                x += sx;
            else
                y += sy;
            error -= 2 * dx;
        }

        if (error < 0)
        {
            if (swap_f == 1)
                y += sy;
            else
                x += sx;
        }

        error += 2 * dy;
    }
    return OK;
}
