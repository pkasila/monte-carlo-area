#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineSeries>
#include <QScatterSeries>
#include <QIntValidator>
#include <QRandomGenerator>
#include <QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QScatterSeries* y1;
    QScatterSeries* y2;

public slots:
    void calc();
};
#endif // MAINWINDOW_H
