#include "circle_alg.h"
#include <stdio.h>

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



ret_data_t Circle_Canon(canvas_t canvas ,QString &color, point_t &center, int radius, float k, int pix_size, int flag)
{
    int64_t start = 0, end = 0;
    start += tick();
    int x_m;
    int y_m;
    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    ret_data_t er;
    er.radius = radius;
    center = get_point(center, canvas);
    for(int x = center.x; x <= center.x + RoundToInt(radius / sqrt(2)); x++)
    {
        int y = center.y + RoundToInt(sqrt(radius * radius - (x - center.x) * (x - center.x)));

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

            x_m = (int) (k * (y + center.x - center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (x + center.y - center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (- y + center.x + center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (x + center.y - center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (y + center.x - center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (- x + center.y + center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (- y + center.x + center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (-x + center.y + center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
    }
    end += tick();
    er.time = (double)(end - start) / SEC;
    return er;
}

ret_data_t Circle_Param(canvas_t canvas ,QString &color, point_t &center, int radius, float k, int pix_size, int flag)
{
    int64_t start = 0, end = 0;
    start += tick();
    int x_m;
    int y_m;
    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    ret_data_t er;
    er.radius = radius;
    center = get_point(center, canvas);

    double step = 1.0 / radius;
    for(double t = 0.0; t <= PI / 4; t += step)
    {
        int y = center.y + RoundToInt(radius * cos(t));
        int x = center.x + RoundToInt(radius * sin(t));

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

            x_m = (int) (k * (y + center.x - center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (x + center.y - center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (- y + center.x + center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (x + center.y - center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (y + center.x - center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (- x + center.y + center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (- y + center.x + center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (-x + center.y + center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
    }
    end += tick();
    er.time = (double)(end - start) / SEC;
    return er;
}

ret_data_t Circle_Bresenham(canvas_t canvas ,QString &color, point_t &center, int radius, float k, int pix_size, int flag)
{
    int64_t start = 0, end = 0;
    start += tick();
    int x_m;
    int y_m;
    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    ret_data_t er;
    er.radius = radius;
    center = get_point(center, canvas);

    int x = 0;
    int y = radius;
    int D = 2 * (1 - radius);

    int x_k;
    int y_k;

    while (x <= y)
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

            x_m = (int) (k * (y_k + center.x - center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (x_k + center.y - center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (- y_k + center.x + center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (x_k + center.y - center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (y_k + center.x - center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (- x_k + center.y + center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (- y_k + center.x + center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (-x_k + center.y + center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
        if (D < 0)
        {
            int D1 = 2 * D + 2 * y - 1;
            if (D1 <= 0)
            {
                x += 1;
                D += 2 * x + 1;
            }
            else
            {
                x += 1;
                y -= 1;
                D += 2 * (x - y + 1);
            }
        }
        else
        {
            x += 1;
            y -= 1;
            D += 2 * (x - y + 1);
        }
    }
    end += tick();
    er.time = (double)(end - start) / SEC;
    return er;
}

ret_data_t Circle_MidPoint(canvas_t canvas ,QString &color, point_t &center, int radius, float k, int pix_size, int flag)
{
    int64_t start = 0, end = 0;
    start += tick();
    int x_m;
    int y_m;
    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    ret_data_t er;
    er.radius = radius;
    center = get_point(center, canvas);

    int x = 0;
    int y = radius;
    int D = RoundToInt(1.25 - radius);

    int x_k;
    int y_k;

    while (x <= y)
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

            x_m = (int) (k * (y_k + center.x - center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (x_k + center.y - center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (- y_k + center.x + center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (x_k + center.y - center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (y_k + center.x - center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (- x_k + center.y + center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);

            x_m = (int) (k * (- y_k + center.x + center.y) + (1 - k) * (canvas.width / 2));
            y_m = (int) (k * (-x_k + center.y + center.x) + (1 - k) * (canvas.height / 2));
            canvas.scene->addRect(x_m, y_m, pix_size, pix_size, pen ,brush);
        }
        if (D > 0)
        {
            x += 1;
            y -= 1;
            D += 2 * (x - y);
        }
        else
        {
            x += 1;
            D += 2 * x + 1;
        }
    }
    end += tick();
    er.time = (double)(end - start) / SEC;
    return er;
}

ret_data_t Circle_Ordinary(canvas_t canvas ,QString &color, point_t &center, int radius, float k, int pix_size, int flag)
{
    int64_t start = 0, end = 0;
    start += tick();
    int x_m;
    int y_m;
    QPen pen(color);
    pen.setWidth(pix_size);
    QBrush brush(color, Qt::NoBrush);
    ret_data_t er;
    er.radius = radius;
    center = get_point(center, canvas);
    if (flag)
    {
        x_m = (int) (k * (center.x) + (1 - k) * (canvas.width / 2));
        y_m = (int) (k * (center.y) + (1 - k) * (canvas.height / 2));
        radius = radius * k;
        canvas.scene->addEllipse(x_m - radius, y_m - radius, radius * 2, radius * 2, pen, brush);
    }
    end += tick();
    er.time = (double)(end - start) / SEC;
    return er;
}

