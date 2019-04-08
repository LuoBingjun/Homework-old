#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")；

#include <QMainWindow>
#include <QLabel>
#include <vector>

class pt;
class pt_pair;

namespace Ui {
class MainWindow;
}

class graphicsLabel : public QLabel
{
    Q_OBJECT
public:
    explicit graphicsLabel(QWidget *parent = nullptr);
    std::vector<pt> pts;
    pt_pair* closest = nullptr;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    graphicsLabel* gLabel = nullptr;
};

#endif // MAINWINDOW_H
