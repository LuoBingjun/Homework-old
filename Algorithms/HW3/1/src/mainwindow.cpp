#include <QTime>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gLabel = new graphicsLabel(ui->tab);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QTime time;
    int n = ui->spinBox->value();
    std::vector<pt>&& pts = produce_pts(n);
    time.start();
    QSort(pts, 1, n, cmp_xy);
    auto&& d = divide_and_conquer(pts, 1, n);
    int time_Diff = time.elapsed();
    QMessageBox::information(nullptr, "运行成功", "共随机生成" + QString::number(n) + "个点\n其中最近点对为(" + QString::number(d.a.x) + ", " +  QString::number(d.a.y) + ")和(" + QString::number(d.b.x) + ", " +  QString::number(d.b.y) + ")\n最近距离为" + QString::number(d.dis) +"\n运行时间为" + QString::number(time_Diff) + "ms", QMessageBox::Yes, QMessageBox::Yes);
}

graphicsLabel::graphicsLabel(QWidget *parent):QLabel(parent)
{
    setGeometry(0,40,1280,720);
    setStyleSheet("border:2px solid black;");
    pts.push_back(pt());
}

void graphicsLabel::mousePressEvent(QMouseEvent *event)
{
    pt p(event->x(),event->y());
    qDebug() << p.x << "," << p.y;
    pts.push_back(p);
    update();
}

void graphicsLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(QBrush(Qt::black), 2, Qt::SolidLine));
    for(auto& i : pts)
    {
        painter.drawPoint(i.x, i.y);
    }

    if(closest)
    {
        painter.setPen(QPen(QBrush(Qt::red), 4, Qt::SolidLine));
        painter.drawPoint(closest->a.x, closest->a.y);
        painter.drawPoint(closest->b.x, closest->b.y);
        painter.setPen(QPen(QBrush(Qt::red), 2, Qt::SolidLine));
        painter.drawLine(closest->a.x, closest->a.y, closest->b.x, closest->b.y);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QTime time;
    int n = gLabel->pts.size() - 1;
    time.start();
    QSort(gLabel->pts, 1, n, cmp_xy);
    auto&& d = divide_and_conquer(gLabel->pts, 1, n);
    int time_Diff = time.elapsed();

    if(gLabel->closest)
        delete gLabel->closest;
    gLabel->closest = new pt_pair(d);

    update();
    QMessageBox::information(nullptr, "运行成功", "共添加" + QString::number(n) + "个点\n其中最近点对为(" + QString::number(d.a.x) + ", " +  QString::number(d.a.y) + ")和(" + QString::number(d.b.x) + ", " +  QString::number(d.b.y) + ")\n最近距离为" + QString::number(d.dis) +"\n运行时间为" + QString::number(time_Diff) + "ms", QMessageBox::Yes, QMessageBox::Yes);
}

void MainWindow::on_pushButton_3_clicked()
{
    gLabel->pts.clear();
    gLabel->pts.push_back(pt());
    if(gLabel->closest)
    {
        delete gLabel->closest;
        gLabel->closest = nullptr;
    }
    update();
}
