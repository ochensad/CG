#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_Button_DDA_clicked();

    void on_go_back_Button_clicked();

    void on_addlineButton_clicked();

    void on_comboBox_activated(int index);

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
