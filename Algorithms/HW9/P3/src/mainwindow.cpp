#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <string>
#include <fstream>
#include <QFileDialog>
#include <QTime>

inline int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

std::vector<int> Brute_Force_matcher(const std::string& T, const std::string& P)
{
    std::vector<int> res;
    int n = T.length();
    int m = P.length();
    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        for (; j < m; j++)
            if (T[i + j] != P[j])
                break;
        if (j == m)
            res.push_back(i);
    }
    return res;
}

int* compute_prefix_function(const std::string& P)
{
    int m = P.length();
    int *pi = new int[m];
    pi[0] = -1;
    int k = -1;
    for (int q = 1; q < m; q++)
    {
        while (k >= 0 && P[k + 1] != P[q])
            k = pi[k];
        if (P[k + 1] == P[q])
            k++;
        pi[q] = k;
    }
    return pi;
}

std::vector<int> KMP_matcher(const std::string& T, const std::string& P)
{
    std::vector<int> res;
    int n = T.length();
    int m = P.length();
    int* pi = compute_prefix_function(P);
    int q = -1;
    for (int i = 0; i < n; i++)
    {
        while (q >= 0 && P[q + 1] != T[i])
            q = pi[q];
        if (P[q + 1] == T[i])
            q++;
        if (q == m - 1)
        {
            res.push_back(i - q);
            q = pi[q];
        }
    }
    delete[] pi;
    return res;
}

int* compute_bmBc(const std::string& P)
{
    int *bmBc = new int[128];
    int m = P.length();
    for (int a = 0; a < 128; a++)
        bmBc[a] = m;
    for (int i = 1; i <= m - 1; i++)
        bmBc[P[i - 1]] = m - i;
    return bmBc;
}

int* compute_Osuff(const std::string& P)
{
    int m = P.length();
    int* Osuff = new int[m];
    for (int i = 0; i < m; i++)
    {
        int k = 0;
        while (i - k >= 0 && P[i - k] == P[m - 1 - k])
            k++;
        Osuff[i] = k;
    }
    return Osuff;
}

int* compute_bmGs(const std::string& P)
{
    int m = P.length();
    int* Osuff = compute_Osuff(P);
    int* bmGs = new int[m];
    for (int i = 1; i <= m; i++)
        bmGs[i-1] = m;
    int j = 1;
    for (int i = m - 1; i >= 1; i--)
    {
        if(Osuff[i-1]==i)
            while (j <= m - i)
            {
                if (bmGs[j - 1] == m)
                    bmGs[j - 1] = m - i;
                j = j + 1;
            }
    }
    for (int i = 1; i <= m - 1; i++)
        bmGs[m - Osuff[i - 1] - 1] = m - i;
    return bmGs;
}

std::vector<int> BM_matcher(const std::string& T, const std::string& P)
{
    std::vector<int> res;
    int n = T.length();
    int m = P.length();
    int *bmBc = compute_bmBc(P);
    int *bmGs = compute_bmGs(P);
    int s = 0;
    while (s <= n - m)
    {
        int i = m;
        while (P[i - 1] == T[s + i - 1])
        {
            if (i == 1)
            {
                res.push_back(s);
                break;
            }
            else
                i = i - 1;
        }
        s = s + max(bmGs[i - 1], bmBc[T[s + i - 1]] - m + i);
    }
    delete[] bmBc;
    delete[] bmGs;
    return res;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::string fileName = QFileDialog::getOpenFileName(
                   this, tr("打开文件"),
                   "./", tr("文本文件 (*.txt);;所有文件 (*.*)")).toStdString();
    std::ifstream ifs(fileName);
    getline(ifs, P);
    getline(ifs, T);
    ui->lineEdit->setText(QString::fromStdString(P));
    ui->lineEdit_2->setText(QString::fromStdString(T));
    ui->label_3->setText("P的长度：" + QString::number(P.size()));
    ui->label_4->setText("T的长度：" + QString::number(T.size()));
}

void MainWindow::on_pushButton_2_clicked()
{
    int index = ui->comboBox->currentIndex();
    std::vector<int> res;
    QTime time;
    time.start(); //开始计时，以ms为单位
    switch(index)
    {
    case 0:
        res = Brute_Force_matcher(T, P);
        break;

    case 1:
        res = KMP_matcher(T, P);
        break;

    case 2:
        res = BM_matcher(T, P);
        break;
    }
    int time_Diff = time.elapsed(); //返回从上次start()或restart()开始以来的时间差，单位ms
    QString resText;
    resText += "运行时间：" + QString::number(time_Diff) + "ms\n";
    resText += "共匹配到" + QString::number(res.size()) + "个位置：" + '\n';
    for(auto i : res)
    {
        resText += QString::number(i) + ' ';
    }
    ui->textBrowser->setPlainText(resText);
}
