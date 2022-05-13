#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "request.h"
#include "error_code.h"
#include <vector>
#include <QIcon>
#include <iostream>
#include <cmath>
#include <QMessageBox>
#include <sstream>
using namespace std;

static canvas_t canvas;
vector<request_t> actions_arr;
line_list_t lines;
point_t last = {-1000,-1000};
enum action act = NO_ALG;
static float k = 1.0;
static int pix = 1;
QGraphicsScene *scene;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QListWidgetItem *item_blue = new QListWidgetItem(QIcon(":/new/prefix1/img/blue.png"), "blue");
    ui->listWidget->addItem(item_blue);
    QListWidgetItem *item_red = new QListWidgetItem(QIcon(":/new/prefix1/img/red.png"), "red");
    ui->listWidget->addItem(item_red);
    QListWidgetItem *item_pink = new QListWidgetItem(QIcon(":/new/prefix1/img/pink.png"), "pink");
    ui->listWidget->addItem(item_pink);
    QListWidgetItem *item_yellow = new QListWidgetItem(QIcon(":/new/prefix1/img/yellow.png"), "yellow");
    ui->listWidget->addItem(item_yellow);
    QListWidgetItem *item_green = new QListWidgetItem(QIcon(":/new/prefix1/img/green.png"), "green");
    ui->listWidget->addItem(item_green);
    QListWidgetItem *item_black = new QListWidgetItem(QIcon(":/new/prefix1/img/black.png"), "black");
    ui->listWidget->addItem(item_black);
    QListWidgetItem *item_purple = new QListWidgetItem(QIcon(":/new/prefix1/img/purple.png"), "purple");
    ui->listWidget->addItem(item_purple);
    QListWidgetItem *item_orange = new QListWidgetItem(QIcon(":/new/prefix1/img/orange.png"), "orange");
    ui->listWidget->addItem(item_orange);
    QListWidgetItem *item_magenta = new QListWidgetItem(QIcon(":/new/prefix1/img/magenta.png"), "magenta");
    ui->listWidget->addItem(item_magenta);
    QListWidgetItem *item_cyan = new QListWidgetItem(QIcon(":/new/prefix1/img/cyan.png"), "cyan");
    ui->listWidget->addItem(item_cyan);
    QListWidgetItem *item_gray = new QListWidgetItem(QIcon(":/new/prefix1/img/gray.png"), "gray");
    ui->listWidget->addItem(item_gray);
    QListWidgetItem *item_light_green = new QListWidgetItem(QIcon(":/new/prefix1/img/light_green.png"), "light green");
    ui->listWidget->addItem(item_light_green);

    scene = new QGraphicsScene(this);

    ui->go_back_Button->setStyleSheet("QPushButton {"
                              "display: inline-block;"
                              "font-size: 12px;"
                              "cursor: pointer;"
                              "text-align: center;"
                              "text-decoration: none;"
                              "outline: none;"
                              "color: #fff;"
                              "background-color: #DC143C;"
                              "border: none;"
                              "border-radius: 10px;"
                              "box-shadow: 0 9px #999;"
                            "}"
                            "QPushButton:hover {background-color: #B22222}"
                            "QPushButton:pressed {"
                              "background-color: #B22222;"
                              "box-shadow: 0 5px #666;"
                              "transform: translateY(4px);"
                            "}");
    ui->listWidget->setStyleSheet("QListWidget {"
                              "display: inline-block;"
                              "font-size: 12px;"
                              "cursor: pointer;"
                              "text-align: center;"
                              "text-decoration: none;"
                              "outline: none;"
                              "color: #696969;"
                              "background-color: #fff;"
                              "border: none;"
                              "border-radius: 10px;"
                              "box-shadow: 0 9px #999;"
                            "}"
                            "QListWidget:hover {background-color: #fff}"
                            "QListWidget:pressed {"
                              "selection-background-color: #C0C0C0;"
                              "box-shadow: 0 5px #666;"
                              "transform: translateY(4px);"
                            "}");

    ui->spinBox_x->setStyleSheet("QSpinBox {"
                              "display: inline-block;"
                              "font-size: 12px;"
                              "cursor: pointer;"
                              "text-align: center;"
                              "text-decoration: none;"
                              "outline: none;"
                              "color: #696969;"
                              "background-color: #DCDCDC;"
                              "border: none;"
                              "border-radius: 10px;"
                              "box-shadow: 0 9px #999;"
                            "}");
    ui->spinBox_y->setStyleSheet("QSpinBox {"
                              "display: inline-block;"
                              "font-size: 12px;"
                              "cursor: pointer;"
                              "text-align: center;"
                              "text-decoration: none;"
                              "outline: none;"
                              "color: #696969;"
                              "background-color: #DCDCDC;"
                              "border: none;"
                              "border-radius: 10px;"
                              "box-shadow: 0 9px #999;"
                            "}");
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_go_back_Button_clicked()
{
    error_code_t er = OK;
    if (lines.lines.size() == 0 && last.x == -1000 && last.y == -1000)
    {
        er = ERROR_SCENE;
        error_message(er);
        return;
    }
    er = clear_canvas(canvas);
    if(er)
        error_message(er);
    ui->listWidget_2->takeItem(lines.lines.size());
    if (lines.lines.size() != 0)
    {
        lines.lines.pop_back();
        QString s = ui->listWidget->currentItem()->text();
        draw_lines(lines, canvas, s);
    }
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    printf("%d\n", position);
    pix = (int) 1 + position / 10;
    k = 1.0 + position/ 10;
    printf("%d %lf\n", position, k);

    error_code_t er = OK;

    er = clear_canvas(canvas);
    if(er)
        error_message(er);
}

void MainWindow::on_action_5_triggered()
{
    QMessageBox::about (NULL, "Об авторе", "Ляпина Наталья \n ИУ7-42Б Вариант №14 \nМогу рассказать анекдот");
}


void MainWindow::on_action_6_triggered()
{
    QMessageBox::about (NULL, "О задаче", "Реализовать различные алгоритмы построения одиночных отрезков. "
                                          "Отрезок задается координатой начала, координатой конца и цветом.");
}


void MainWindow::on_action_7_triggered()
{
    if(QMessageBox:: question (NULL, "Выход", "Вы действительно хотите выйти?") == QMessageBox::Yes)
        QApplication::quit();
}



void MainWindow::on_pushButton_add_point_clicked()
{
    error_code_t er;
    if (ui->listWidget->selectedItems().size() == 0)
    {
        er = ERROR_NO_COLOR;
        error_message(er);
        return;
    }
    request_t req;
    req.action = ADD_POINT;
    req.new_point.x = ui->spinBox_x->value();
    req.new_point.y = ui->spinBox_y->value();

    req.lines = lines;
    req.last_point = last;
    req.color_line = ui->listWidget->currentItem()->text();
    req.canvas = canvas;

    canvas.scene = scene;
    canvas.width = WINDOW_WIDTH;
    canvas.height = WINDOW_HEIGHT;


    er = switch_action(req);
    if (er == OK)
    {
        lines = req.lines;
        last = req.last_point;
        stringstream ss;
        ss << req.new_point.x << ' ' << req.new_point.y;
        string s = ss.str();
        QListWidgetItem *new_item = new QListWidgetItem(QString::fromStdString(s));
    }
    else
        error_message(er);
}

