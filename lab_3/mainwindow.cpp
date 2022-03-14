#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "request.h"
#include "error_code.h"
#include <vector>
#include <QIcon>
#include <stdio.h>
#include <cmath>
#include <QMessageBox>

static canvas_t canvas;
vector<request_t> actions_arr;
point_t Ox;
enum action act = NO_ALG;
static float k = 1.0;
static int pix = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QListWidgetItem *item_blue = new QListWidgetItem(QIcon(":/new/prefix1/img/blue.png"), "blue");
    QListWidgetItem *item_blue_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/blue.png"), "blue");
    ui->listWidget->addItem(item_blue);
    ui->listWidget_2->addItem(item_blue_1);
    QListWidgetItem *item_red = new QListWidgetItem(QIcon(":/new/prefix1/img/red.png"), "red");
    QListWidgetItem *item_red_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/red.png"), "red");
    ui->listWidget->addItem(item_red);
    ui->listWidget_2->addItem(item_red_1);
    QListWidgetItem *item_pink = new QListWidgetItem(QIcon(":/new/prefix1/img/pink.png"), "pink");
    QListWidgetItem *item_pink_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/pink.png"), "pink");
    ui->listWidget->addItem(item_pink);
    ui->listWidget_2->addItem(item_pink_1);
    QListWidgetItem *item_yellow = new QListWidgetItem(QIcon(":/new/prefix1/img/yellow.png"), "yellow");
    QListWidgetItem *item_yellow_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/yellow.png"), "yellow");
    ui->listWidget->addItem(item_yellow);
    ui->listWidget_2->addItem(item_yellow_1);
    QListWidgetItem *item_green = new QListWidgetItem(QIcon(":/new/prefix1/img/green.png"), "green");
    QListWidgetItem *item_green_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/green.png"), "green");
    ui->listWidget->addItem(item_green);
    ui->listWidget_2->addItem(item_green_1);
    QListWidgetItem *item_black = new QListWidgetItem(QIcon(":/new/prefix1/img/black.png"), "black");
    QListWidgetItem *item_black_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/black.png"), "black");
    ui->listWidget->addItem(item_black);
    ui->listWidget_2->addItem(item_black_1);
    QListWidgetItem *item_purple = new QListWidgetItem(QIcon(":/new/prefix1/img/purple.png"), "purple");
    QListWidgetItem *item_purple_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/purple.png"), "purple");
    ui->listWidget->addItem(item_purple);
    ui->listWidget_2->addItem(item_purple_1);
    QListWidgetItem *item_orange = new QListWidgetItem(QIcon(":/new/prefix1/img/orange.png"), "orange");
    QListWidgetItem *item_orange_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/orange.png"), "orange");
    ui->listWidget->addItem(item_orange);
    ui->listWidget_2->addItem(item_orange_1);

    QListWidgetItem *item_white = new QListWidgetItem(QIcon(":/new/prefix1/img/white.png"), "white");
    ui->listWidget_2->addItem(item_white);
    QListWidgetItem *item_magenta_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/magenta.png"), "magenta");
    ui->listWidget_2->addItem(item_magenta_1);
    QListWidgetItem *item_cyan_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/cyan.png"), "cyan");
    ui->listWidget_2->addItem(item_cyan_1);
    QListWidgetItem *item_gray_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/gray.png"), "gray");
    ui->listWidget_2->addItem(item_gray_1);
    QListWidgetItem *item_light_green_1 = new QListWidgetItem(QIcon(":/new/prefix1/img/light_green.png"), "light green");
    ui->listWidget_2->addItem(item_light_green_1);

    QListWidgetItem *item_magenta = new QListWidgetItem(QIcon(":/new/prefix1/img/magenta.png"), "magenta");
    ui->listWidget->addItem(item_magenta);
    QListWidgetItem *item_cyan = new QListWidgetItem(QIcon(":/new/prefix1/img/cyan.png"), "cyan");
    ui->listWidget->addItem(item_cyan);
    QListWidgetItem *item_gray = new QListWidgetItem(QIcon(":/new/prefix1/img/gray.png"), "gray");
    ui->listWidget->addItem(item_gray);
    QListWidgetItem *item_light_green = new QListWidgetItem(QIcon(":/new/prefix1/img/light_green.png"), "light green");
    ui->listWidget->addItem(item_light_green);

    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    canvas.scene = ui->graphicsView->scene();
    canvas.width = canvas.scene->width();
    canvas.height = canvas.scene->height();

    Ox.x = 0;
    Ox.y = 0;

    Ox = get_point(Ox, canvas);

    canvas.scene->addLine(Ox.x, Ox.y, Ox.x, 0, QPen(Qt::black, 1));
    canvas.scene->addLine(Ox.x, Ox.y, Ox.x, 800, QPen(Qt::black, 1));
    canvas.scene->addLine(Ox.x, Ox.y, 0, Ox.y, QPen(Qt::black, 1));
    canvas.scene->addLine(Ox.x, Ox.y, 970, Ox.y, QPen(Qt::black, 1));

    ui->comboBox->addItem("Qtline");
    ui->comboBox->addItem("DDA");
    ui->comboBox->addItem("BresenhamReal");
    ui->comboBox->addItem("BresenhamInt");
    ui->comboBox->addItem("Wu");
    ui->comboBox->addItem("BresenhamWS");

    ui->Button_compare->setStyleSheet("QPushButton {"
                                  "display: inline-block;"
                                  "font-size: 12px;"
                                  "cursor: pointer;"
                                  "text-align: center;"
                                  "text-decoration: none;"
                                  "outline: none;"
                                  "color: #fff;"
                                  "background-color: #4CAF50;"
                                  "border: none;"
                                  "border-radius: 10px;"
                                  "box-shadow: 0 9px #999;"
                                "}"
                                "QPushButton:hover {background-color: #3e8e41}"
                                "QPushButton:pressed {"
                                  "background-color: #3e8e41;"
                                  "box-shadow: 0 5px #666;"
                                  "transform: translateY(4px);"
                                "}");
    ui->addlineButton->setStyleSheet("QPushButton {"
                                  "display: inline-block;"
                                  "font-size: 12px;"
                                  "cursor: pointer;"
                                  "text-align: center;"
                                  "text-decoration: none;"
                                  "outline: none;"
                                  "color: #fff;"
                                  "background-color: #4CAF50;"
                                  "border: none;"
                                  "border-radius: 10px;"
                                  "box-shadow: 0 9px #999;"
                                "}"
                                "QPushButton:hover {background-color: #3e8e41}"
                                "QPushButton:pressed {"
                                  "background-color: #3e8e41;"
                                  "box-shadow: 0 5px #666;"
                                  "transform: translateY(4px);"
                                "}");
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
    ui->listWidget_2->setStyleSheet("QListWidget {"
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
    ui->comboBox->setStyleSheet("QComboBox {"
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
                            "QComboBox:hover {background-color: #fff}"
                            "QComboBox:pressed {"
                              "selection-background-color: #C0C0C0;"
                              "box-shadow: 0 5px #666;"
                              "transform: translateY(4px);"
                            "}");
    ui->spinBox_x_end->setStyleSheet("QSpinBox {"
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
    ui->spinBox_y_end->setStyleSheet("QSpinBox {"
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
    ui->spinBox_x_start->setStyleSheet("QSpinBox {"
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
    ui->spinBox_y_start->setStyleSheet("QSpinBox {"
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
    request_t request;
    request.action = QUIT;
    delete ui;
}


void MainWindow::on_go_back_Button_clicked()
{
    error_code_t er = OK;
    if (actions_arr.size() == 0)
    {
        er = ERROR_SCENE;
        error_message(er);
        return;
    }
    actions_arr.pop_back();
    er = clear_canvas(canvas);
    if(er)
        error_message(er);

    Ox.x = 0;
    Ox.y = 0;

    Ox = get_point(Ox, canvas);

    canvas.scene->addLine(Ox.x, Ox.y, Ox.x, 0, QPen(Qt::black, 1));
    canvas.scene->addLine(Ox.x, Ox.y, Ox.x, 800, QPen(Qt::black, 1));
    canvas.scene->addLine(Ox.x, Ox.y, 0, Ox.y, QPen(Qt::black, 1));
    canvas.scene->addLine(Ox.x, Ox.y, 970, Ox.y, QPen(Qt::black, 1));

    for(auto item: actions_arr)
    {
        item.k = k;
        item.pix_size = pix;
        switch_action(item);
    }
}


void MainWindow::on_addlineButton_clicked()
{
    request_t request;
    request.action = act;
    error_code_t er = OK;
    ret_data_t r;

    if (act == NO_ALG)
    {
        er = ERROR_NO_ALG;
        error_message(er);
        return;
    }

    if (ui->listWidget->selectedItems().size() == 0)
    {
        er = ERROR_NO_COLOR;
        error_message(er);
        return;
    }

    request.color = ui->listWidget->currentItem()->text();
    request.start.x = ui->spinBox_x_start->value();
    request.start.y = ui->spinBox_y_start->value();
    request.end.x = ui->spinBox_x_end->value();
    request.end.y = ui->spinBox_y_end->value();

    request.canvas = canvas;
    request.k = k;
    request.pix_size = pix;

    actions_arr.push_back(request);
    r = switch_action(request);
}


void MainWindow::on_comboBox_activated(int index)
{
    QString alg = ui->comboBox->currentText();
    printf("%d", index);

    if (alg == "DDA")
        act = DDA;
    else if (alg == "Qtline")
        act = ORDINARYLINE;
    else if (alg == "BresenhamReal")
        act = B_REAL;
    else if (alg == "BresenhamInt")
        act = B_INT;
    else if (alg == "Wu")
        act = WU;
    else if (alg == "BresenhamWS")
        act = B_WS;
    else
        act = NO_ALG;
}



void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    printf("%d\n", position);
    pix = (int) 1 + position / 10;
    k = 1.0 + position/ 10;
    printf("%d %lf\n", position, k);

    ret_data_t r;
    error_code_t er = OK;

    er = clear_canvas(canvas);
    if(er)
        error_message(er);

    Ox.x = 0;
    Ox.y = 0;

    Ox = get_point(Ox, canvas);

    canvas.scene->addLine(Ox.x, Ox.y, Ox.x, 0, QPen(Qt::black, 1));
    canvas.scene->addLine(Ox.x, Ox.y, Ox.x, 800, QPen(Qt::black, 1));
    canvas.scene->addLine(Ox.x, Ox.y, 0, Ox.y, QPen(Qt::black, 1));
    canvas.scene->addLine(Ox.x, Ox.y, 970, Ox.y, QPen(Qt::black, 1));

    for(auto item: actions_arr)
    {
        item.k = k;
        item.pix_size = pix;
        r = switch_action(item);
    }
}

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    QString color = item->text();
    QBrush brush(color, Qt::SolidPattern);
    canvas.scene->setBackgroundBrush(brush);
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


void MainWindow::on_Button_compare_clicked()
{
    int step = ui->spinBox->value();

    for(int i = 0; i < 6; i++)
    {
        if (i == 0)
            act = DDA;
        else if (i == 1)
            act = B_REAL;
        else if (i == 2)
            act = B_INT;
        else if (i == 3)
            act = B_WS;
        else if (i == 4)
            act = WU;
        else if (i == 5)
            act = ORDINARYLINE;
        request_t request;
        request.action = act;
        ret_data_t er;

        request.color = ui->listWidget->item(i)->text();
        request.start.x = ui->spinBox_x_start->value() + i * step;
        request.start.y = ui->spinBox_y_start->value();
        request.end.x = ui->spinBox_x_end->value() + i * step;
        request.end.y = ui->spinBox_y_end->value();

        request.canvas = canvas;
        request.k = k;
        request.pix_size = pix;

        actions_arr.push_back(request);
        er = switch_action(request);

    }
}


void MainWindow::on_actionDDA_triggered()
{
    FILE *f = fopen("output.txt", "w");

    int len = 150;
    point_t center;
    center.x = 0;
    center.y = 0;

    for(int i = 0; i <= 360; i++)
    {
        point_t end;
        end.x = RoundToInt(center.x + len * cos(i * PI / 180.0));
        end.y = RoundToInt(center.y + len * sin(i * PI / 180.0));
        request_t request;
        request.action = DDA;
        ret_data_t er;

        request.color = ui->listWidget->item(0)->text();
        request.start.x = center.x;
        request.start.y = center.y;
        request.end.x = end.x;
        request.end.y = end.y;

        request.canvas = canvas;
        request.k = k;
        request.pix_size = pix;

        er = switch_action(request);
        er.a = i;
        fprintf(f, "%d %d\n", (int)er.a, er.steps);
    }
    fclose(f);
    request_t request;
    request.action = NO_ALG;
    actions_arr.push_back(request);
    system("python graph.py");
}


void MainWindow::on_actionBresenhamReal_triggered()
{
    FILE *f = fopen("output.txt", "w");

    int len = 150;
    point_t center;
    center.x = 0;
    center.y = 0;

    for(int i = 0; i <= 360; i++)
    {
        point_t end;
        end.x = RoundToInt(center.x + len * cos(i * PI / 180.0));
        end.y = RoundToInt(center.y + len * sin(i * PI / 180.0));
        request_t request;
        request.action = B_REAL;
        ret_data_t er;

        request.color = ui->listWidget->item(0)->text();
        request.start.x = center.x;
        request.start.y = center.y;
        request.end.x = end.x;
        request.end.y = end.y;

        request.canvas = canvas;
        request.k = k;
        request.pix_size = pix;

        er = switch_action(request);
        er.a = i;
        fprintf(f, "%d %d\n", (int)er.a, er.steps);
    }
    fclose(f);
    request_t request;
    request.action = NO_ALG;
    actions_arr.push_back(request);
    system("python graph.py");
}


void MainWindow::on_actionBresenhamInt_triggered()
{
    FILE *f = fopen("output.txt", "w");

    int len = 150;
    point_t center;
    center.x = 0;
    center.y = 0;

    for(int i = 0; i <= 360; i++)
    {
        point_t end;
        end.x = RoundToInt(center.x + len * cos(i * PI / 180.0));
        end.y = RoundToInt(center.y + len * sin(i * PI / 180.0));
        request_t request;
        request.action = B_INT;
        ret_data_t er;

        request.color = ui->listWidget->item(0)->text();
        request.start.x = center.x;
        request.start.y = center.y;
        request.end.x = end.x;
        request.end.y = end.y;

        request.canvas = canvas;
        request.k = k;
        request.pix_size = pix;

        er = switch_action(request);
        er.a = i;
        fprintf(f, "%d %d\n", (int)er.a, er.steps);
    }
    fclose(f);
    request_t request;
    request.action = NO_ALG;
    actions_arr.push_back(request);
    system("python graph.py");
}


void MainWindow::on_actionBresenhamWS_triggered()
{
    FILE *f = fopen("output.txt", "w");

    int len = 150;
    point_t center;
    center.x = 0;
    center.y = 0;

    for(int i = 0; i <= 360; i++)
    {
        point_t end;
        end.x = RoundToInt(center.x + len * cos(i * PI / 180.0));
        end.y = RoundToInt(center.y + len * sin(i * PI / 180.0));
        request_t request;
        request.action = B_WS;
        ret_data_t er;

        request.color = ui->listWidget->item(0)->text();
        request.start.x = center.x;
        request.start.y = center.y;
        request.end.x = end.x;
        request.end.y = end.y;

        request.canvas = canvas;
        request.k = k;
        request.pix_size = pix;

        er = switch_action(request);
        er.a = i;
        fprintf(f, "%d %d\n", (int)er.a, er.steps);
    }
    fclose(f);
    request_t request;
    request.action = NO_ALG;
    actions_arr.push_back(request);
    system("python graph.py");
}


void MainWindow::on_actionWu_triggered()
{
    FILE *f = fopen("output.txt", "w");

    int len = 150;
    point_t center;
    center.x = 0;
    center.y = 0;

    for(int i = 0; i <= 360; i++)
    {
        point_t end;
        end.x = RoundToInt(center.x + len * cos(i * PI / 180.0));
        end.y = RoundToInt(center.y + len * sin(i * PI / 180.0));
        request_t request;
        request.action = WU;
        ret_data_t er;

        request.color = ui->listWidget->item(0)->text();
        request.start.x = center.x;
        request.start.y = center.y;
        request.end.x = end.x;
        request.end.y = end.y;

        request.canvas = canvas;
        request.k = k;
        request.pix_size = pix;

        er = switch_action(request);
        er.a = i;
        fprintf(f, "%d %d\n", (int)er.a, er.steps);
    }
    fclose(f);
    request_t request;
    request.action = NO_ALG;
    actions_arr.push_back(request);
    system("python graph.py");
}

