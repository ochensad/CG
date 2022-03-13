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

error_code_t line_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size)
{
    start = get_point(start, canvas);
    end = get_point(end, canvas);

    QPen pen(color);
    pen.setWidth(pix_size);

    int x_m = 0;
    int y_m = 0;

    x_m = (int) (k * start.x + (1 - k) * (canvas.width / 2));
    y_m = (int) (k * start.y + (1 - k) * (canvas.height / 2));

    canvas.scene->addLine(x_m, y_m, end.x, end.y, pen);
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


error_code_t BresenhanWS(canvas_t canvas ,QString &color, point_t &start, point_t &end, float k, int pix_size, int level)
{
    static int steps_BWS = 0;

    start = get_point(start, canvas);
    end = get_point(end, canvas);

    int x_m = 0;
    int y_m = 0;

    float intensity = 1.0;
    QColor color_i(color);
    color_i.toRgb();
    color_i.setAlpha(intensity * 255);
    QPen pen(color_i);
    pen.setWidth(0);
    QBrush brush(color_i, Qt::SolidPattern);
    pen.setBrush(brush);

    if (start.x == end.x && start.y == end.y && start.x >= 0 && start.x <= canvas.width
            && start.y >= 0 && start.y <= canvas.height)
    {
        steps_BWS = 0;
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

    float error = 1.0;
    if (abs(m - 0) < 1e-6)
    {
        error = level;
    }
    else
        error = 2.0;
    int x = start.x;
    int y = start.y;

    m *= level;

    float W = level - m;

    QColor color_1(color);
    color_1.toRgb();
    color_1.setAlpha(error * (255.0 / level));

    if (x >= 0 && x < canvas.width && y >= 0 && y < canvas.height)
    {
        pen.setColor(color_1);
        brush.setColor(color_1);
        x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
        y_m = (int) (k * y + (1 - k) * (canvas.height / 2));
        canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen, brush);
    }

    for (int i = 0; i < dx; i++)
    {
        if (error <= W)
        {
            if (swap_f == 1)
            {
                y += sy;
            }
            else
                x += sx;
            error += m;
        }
        else if (error > W)
        {
            y += sy;
            x += sx;
            error -= W;
            steps_BWS ++;
        }

        color_1.setAlpha(error * (255.0 / level));
        if (x >= 0 && x < canvas.width && y >= 0 && y < canvas.height)
        {
            pen.setColor(color_1);
            brush.setColor(color_1);
            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * y + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen, brush);
        }

    }

    return OK;
}

error_code_t Wu(canvas_t canvas ,QString &color, point_t start, point_t end, float k, int pix_size)
{
    start = get_point(start, canvas);
    end = get_point(end, canvas);
    bool swap_f = abs(end.y - start.y) > abs(end.x - start.y);

    if (swap_f)
    {
        swap(start.x, start.y);
        swap(end.x, end.y);
    }

    if (end.x < start.x)
    {
        swap(start.x, end.x);
        swap(start.y, end.y);
    }

    int dx = end.x - start.x;
    int dy = end.y - start.y;

    float intensity = 1.0;
    QColor color_i(color);
    color_i.toRgb();
    color_i.setAlpha(intensity * 255);
    QPen pen(color_i);
    pen.setWidth(0);
    QBrush brush(color_i, Qt::SolidPattern);
    pen.setBrush(brush);
    float grad = (float)dy/dx;

    int x_m = 0;
    int y_m = 0;

    if (!swap_f)
    {
        x_m = (int) (k * start.x + (1 - k) * (canvas.width / 2));
        y_m = (int) (k * start.y + (1 - k) * (canvas.height / 2));
        canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        x_m = (int) (k * end.x + (1 - k) * (canvas.width / 2));
        y_m = (int) (k * end.y + (1 - k) * (canvas.height / 2));
        canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
    }
    else
    {
        x_m = (int) (k * start.x + (1 - k) * (canvas.width / 2));
        y_m = (int) (k * start.y + (1 - k) * (canvas.height / 2));
        canvas.scene->addRect(y_m, x_m, pix_size, pix_size, pen ,brush);
        x_m = (int) (k * end.x + (1 - k) * (canvas.width / 2));
        y_m = (int) (k * end.y + (1 - k) * (canvas.height / 2));
        canvas.scene->addRect(y_m, x_m, pix_size, pix_size, pen ,brush);
    }

    float y = start.y + grad;

    int prev_x = start.x, prev_y = start.y;

    static int steps_Wu;
    steps_Wu = 0;

    QColor color_1(color);
    color_i.toRgb();
    color_i.setAlpha(intensity * 255);
    QColor color_2(color);
    color_i.toRgb();
    color_i.setAlpha(intensity * 255);
    for (int x = start.x + 1; x < end.x; x++)
    {
        if (abs(x - prev_x) == 1 && abs((int)y - prev_y) == 1)
            steps_Wu++;

        prev_x = x;
        prev_y = (int)y;

        if (!swap_f)
        {
            color_1.setAlpha((1 - (y - (float)trunc(y))) * 255);
            color_2.setAlpha((y - (float)trunc(y)) * 255);
            pen.setColor(color_1);
            brush.setColor(color_1);
            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * y + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
            pen.setColor(color_2);
            brush.setColor(color_2);
            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y + 1) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
        else
        {
            color_1.setAlpha((1 - (y - (float)trunc(y))) * 255);
            color_2.setAlpha((y - (float)trunc(y)) * 255);
            pen.setColor(color_1);
            brush.setColor(color_1);
            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * y + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(y_m, x_m, pix_size, pix_size, pen ,brush);
            pen.setColor(color_2);
            brush.setColor(color_2);
            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y + 1) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(y_m, x_m, pix_size, pix_size, pen ,brush);
        }

        y += grad;
    }
    return OK;
}
















