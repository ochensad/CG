#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

#define WINDOW_WIDTH 970
#define WINDOW_HEIGHT 630

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_go_back_Button_clicked();

    void on_addlineButton_clicked();

    void on_comboBox_activated(int index);

    void on_horizontalSlider_sliderMoved(int position);

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_Button_compare_clicked();

    void on_actionDDA_triggered();

    void on_actionBresenhamReal_triggered();

    void on_actionBresenhamInt_triggered();

    void on_actionBresenhamWS_triggered();

    void on_actionWu_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
