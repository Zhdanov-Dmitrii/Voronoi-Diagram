#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::Point MainWindow::randSite(int w, int h)
{
    return MainWindow::Point(qrand()%w, qrand()%h, qRgb(qrand()%255, qrand()%255, qrand()%255) );
}

int MainWindow::createDiagram(int w, int h, int n)
{
    n = sites.size() < n ? sites.size() : n;

    QImage img(w,h, QImage::Format_RGB32);
    int time = clock();
    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            QRgb color = sites[0].color;
            int minDist = (x-sites[0].x)*(x-sites[0].x)+(y-sites[0].y)*(y-sites[0].y);
            for(int i = 1; i < n; i++)
            {
                int dist = (x-sites[i].x)*(x-sites[i].x)+(y-sites[i].y)*(y-sites[i].y);
                if(minDist > dist)
                {
                    minDist = dist;
                    color = sites[i].color;
                }

                img.setPixel(x,y, color);
            }
        }
    }
    time = clock() - time;

    img.save(QString::number(n) + ".png");
    return time;
}

void MainWindow::on_startTest_PB_clicked()
{
    int start = ui->start_SP->value();
    int end = ui->end_SP->value();
    int step = ui->step_SP->value();
    int repeat = ui->repeat_SP->value();


    ui->result->setRowCount((end-start)/step+1);
    for(int n = start,i = 0; n <= end;n+=step, i++)
    {
        double tn = 0;
        double t2n = 0;

        for(int j = 0; j < repeat; j++)
        {
            sites.clear();
            //Генерация случайных сайтов
            for(int i = 0; i < 2*n; i++)
                sites.append(randSite(2024,2024));

            tn += createDiagram(2048, 2048, n);
            t2n += createDiagram(2048,2048, 2*n);
        }

        tn = tn/(1000*repeat);
        t2n = t2n/(1000*repeat);

        ui->result->setItem(i,0, new QTableWidgetItem(QString::number(n)));
        ui->result->setItem(i,1, new QTableWidgetItem(QString::number(tn)));
        ui->result->setItem(i,2, new QTableWidgetItem(QString::number(t2n)));
        ui->result->setItem(i,3, new QTableWidgetItem(QString::number(t2n/tn)));

    }
}

