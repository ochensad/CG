#include "ellipse_alg.h"

static uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

ret_data_t Ellipse_Ordinary(canvas_t canvas ,QString &color, point_t &center, int a, int b, float k, int pix_size, int flag)
{
    int64_t start = 0, end = 0;
    start += tick();
    int x_m;
    int y_m;
    QPen pen(color);
    pen.setWidth(pix_size);
    QBrush brush(color, Qt::NoBrush);
    ret_data_t er;
    er.radius = a;
    center = get_point(center, canvas);
    if (flag)
    {
        x_m = (int) (k * (center.x) + (1 - k) * (canvas.width / 2));
        y_m = (int) (k * (center.y) + (1 - k) * (canvas.height / 2));
        a *= k;
        b *= k;
        canvas.scene->addEllipse(x_m - a, y_m - b, a * 2, b * 2, pen, brush);
    }
    end += tick();
    er.time = (double)(end - start) / SEC;
    return er;
}

ret_data_t Ellipse_Canon(canvas_t canvas ,QString &color, point_t &center, int a, int b, float k, int pix_size, int flag)
{
    int64_t start = 0, end = 0;
    start += tick();
    int x_m;
    int y_m;
    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    ret_data_t er;
    er.radius = a;
    center = get_point(center, canvas);

    int limit = center.x + RoundToInt(a / sqrt(1 + b*b / (a*a)));
    for(int x = center.x; x <= limit; x++)
    {
        int y = RoundToInt(sqrt(a * a - (x - center.x) * (x - center.x)) * b / a) + center.y;
        if (flag)
        {
            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
    }

    limit = center.y + RoundToInt(b / sqrt(1 + a*a / (b*b)));
    for(int y = center.y; y <= limit; y++)
    {
        int x = RoundToInt(sqrt(b * b - (y - center.y) * (y - center.y)) * a / b) + center.x;
        if (flag)
        {
            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
    }
    end += tick();
    er.time = (double)(end - start) / SEC;
    return er;
}

ret_data_t Ellipse_Param(canvas_t canvas ,QString &color, point_t &center, int a, int b, float k, int pix_size, int flag)
{
    int64_t start = 0, end = 0;
    start += tick();
    int x_m;
    int y_m;
    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    ret_data_t er;
    er.radius = a;
    center = get_point(center, canvas);

    double step;
    if (a <= b)
        step = 1.0 / b;
    else
        step = 1.0 / a;

    for(double t = 0.0; t <= PI/ 2; t += step)
    {
        int x = center.x + RoundToInt(a * cos(t));
        int y = center.y + RoundToInt(b * sin(t));

        if (flag)
        {
            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * x + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
    }
    end += tick();
    er.time = (double)(end - start) / SEC;
    return er;
}

ret_data_t Ellipse_Bresenham(canvas_t canvas ,QString &color, point_t &center, int a, int b, float k, int pix_size, int flag)
{
    int64_t start = 0, end = 0;
    start += tick();
    int x_m;
    int y_m;
    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    ret_data_t er;
    er.radius = a;
    center = get_point(center, canvas);

    int x = 0, y = b;
    int b2 = b * b, a2 = a * a;
    int D = RoundToInt(b2 - a2 * b + 0.25 * a2);

    int x_k, y_k;
    while (b2 * x < a2 * y)
    {
        x_k = x + center.x;
        y_k = y + center.y;
        if (flag)
        {
            x_m = (int) (k * x_k + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x_k) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * x_k + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x_k) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
        if (D >= 0)
        {
            y -= 1;
            D -= 4 * a2 * y;
        }

        D += 2 * b2 * (3 + 2 * x);
        x += 1;
    }

    D = RoundToInt(b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 0.5) * (y - 0.5) - a2 * b2);

    while (y + 1 > 0)
    {
        x_k = x + center.x;
        y_k = y + center.y;
        if (flag)
        {
            x_m = (int) (k * x_k + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x_k) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * x_k + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x_k) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
        if (D <= 0)
        {
            x += 1;
            D += 4 * b2 * x;
        }

        y -= 1;
        D += 2 * a2 * (3 - 2 * y);
    }
    end += tick();
    er.time = (double)(end - start) / SEC;
    return er;
}

ret_data_t Ellipse_MidPoint(canvas_t canvas ,QString &color, point_t &center, int a, int b, float k, int pix_size, int flag)
{
    int64_t start = 0, end = 0;
    start += tick();
    int x_m;
    int y_m;
    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    ret_data_t er;
    er.radius = a;
    center = get_point(center, canvas);

    int x = 0, y = b;
    int b2 = b * b, a2 = a * a;
    double D = b2 - a2 * b + 0.25 * a2;

    int x_k, y_k;
    while (b2 * x < a2 * y)
    {
        x_k = x + center.x;
        y_k = y + center.y;
        if (flag)
        {
            x_m = (int) (k * x_k + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x_k) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * x_k + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x_k) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
        if (D > 0)
        {
            x += 1;
            y -= 1;
            D += 2 * b2 * x - 2 * a2 * y;
        }
        else
        {
            x += 1;
            D += b2 * (2 * x + 1);
        }
    }

    D += 0.75 * (a2 + b2) - (a2 * y + b2 * x);

    while (y >= 0)
    {
        x_k = x + center.x;
        y_k = y + center.y;
        if (flag)
        {
            x_m = (int) (k * x_k + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x_k) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * x_k + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (2 * center.x - x_k) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (2 * center.y - y_k) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
        if (D > 0)
        {
            y -= 1;
            x += 1;
            D += a2 * (2 * y + 1) - 2 * b2 * x;
        }
        else
        {
            y -= 1;
            D += a2 * (2 * y + 1);
        }
    }
    end += tick();
    er.time = (double)(end - start) / SEC;
    return er;
}
