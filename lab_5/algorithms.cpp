#include "algorithms.h"
#include <math.h>
#include <iostream>

int flag = 0;

int RoundToInt(double d)
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

line_t convert_line(line_t line, canvas_t &canvas)
{
    line.start = get_point(line.start, canvas);
    line.end = get_point(line.end, canvas);
    return line;
}

void draw_line(line_t line, canvas_t canvas ,QString &color)
{
    QPen pen(color);
    pen.setWidth(2);
    line_t tmp;
    tmp = convert_line(line, canvas);
    canvas.scene->addLine(tmp.start.x, tmp.start.y, tmp.end.x, tmp.end.y,pen);
}

void DDA_algorithm(canvas_t canvas ,QString &color, point_t &start, point_t &end)
{
    start = get_point(start, canvas);
    end = get_point(end, canvas);

    float x = start.x, y = start.y;

    QImage image = QImage(WINDOW_WIDTH, WINDOW_HEIGHT, QImage::Format_RGB32);
    QPainter p (&canvas.im);
    QPen pen(color);
    pen.setWidth(0);
    QBrush brush(color, Qt::SolidPattern);
    p.setBrush(brush);
    p.setPen(pen);

    if (start.x == end.x && start.y == end.y && start.x >= 0 && start.x <= canvas.width
            && start.y >= 0 && start.y <= canvas.height)
    {
        QPoint buf(x, y);
        p.drawPoint(buf);
        return;
    }

    int l = abs(end.x - start.x) >= abs(end.y - start.y) ? abs(end.x - start.x): abs(end.y - start.y);

    float dx = (float)(end.x - start.x) / l;
    float dy = (float)(end.y - start.y) / l;

    int x_prev = RoundToInt(x);
    int y_prev = RoundToInt(y);

    for(int i = 0; i <= l; i++)
    {
        int x_r = RoundToInt(x), y_r = RoundToInt(y);

        x_prev = x_r;
        y_prev = y_r;

        if (x_r >= 0 && x_r <= canvas.width && y_r >= 0 && y_r <= canvas.height)
        {
            QPoint buf(x_r, y_r);
            p.drawPoint(buf);
        }

        x += dx;
        y += dy;
    }
}

void draw_lines(line_list_t lines, canvas_t canvas ,QString &color)
{
    if (lines.lines.size() != 0)
    {
        for(auto line: lines.lines)
        {
            draw_line(line, canvas, color);
        }
    }
}

error_code_t add_point_alg(point_t &new_point, line_list_t &lines, point_t &last, canvas_t canvas ,QString &color)
{
    if (last.x == new_point.x && last.y == new_point.y)
        return SAME_POINT;
    for(auto item: lines.lines)
    {
        if ((item.start.x == new_point.x && item.start.y == new_point.y) || (item.end.x == new_point.x && item.end.y == new_point.y))
            return SAME_POINT;
    }
    if (flag)
    {
        line_t line;
        line.start = last;
        line.end = new_point;
        last = new_point;
        lines.lines.push_back(line);
        DDA_algorithm(canvas,color, line.start, line.end);
    }
    else
    {
        flag = 1;
        last = new_point;
    }
    return OK;
}

error_code_t filling(line_list_t lines, canvas_t canvas ,QString &color_line, QString &color_fill)
{
    error_code_t er;
    if (lines.lines.size() == 0)
    {
        er = NO_LINES;
        return er;
    }

    int x_min = lines.lines[0].start.x;
    int x_max = lines.lines[0].start.x;
    int y_min = lines.lines[0].start.y;
    int y_max = lines.lines[0].start.y;

    for(auto line: lines.lines)
    {
        if (line.start.x < x_min)
            x_min = line.start.x;
        if (line.end.x < x_min)
            x_min = line.end.x;

        if (line.start.x > x_max)
            x_max = line.start.x;
        if(line.end.x > x_max)
            x_max = line.end.x;

        if (line.start.y < x_min)
            y_min = line.start.y;
        if (line.end.y < y_min)
            y_min = line.end.y;

        if (line.start.y > y_max)
            y_max = line.start.y;
        if(line.end.y > y_max)
            y_max = line.end.y;
    }

    bool flag;
    QTransform t;
    QGraphicsItem *item;
    for(int y = y_max; y >= y_min; y--)
    {
        flag = false;

        for(int x = x_min; x <= x_max; x++)
        {
            item = canvas.scene->itemAt(x, y, t);
        }
    }
}

