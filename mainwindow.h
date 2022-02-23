#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct Point
    {
        int x, y;
        QRgb color;

        Point(int x, int y, QRgb color)
        {
            this->x = x;
            this->y = y;
            this->color = color;
        }
    };

private slots:
    void on_startTest_PB_clicked();

private:
    Ui::MainWindow *ui;
    QList<Point> sites;


    int createDiagram(int w, int h, int n);
    Point randSite(int w, int h);
};
#endif // MAINWINDOW_H
