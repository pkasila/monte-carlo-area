#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setValidator(new QIntValidator(0, 10000000, this));

    QLineSeries* series1 = new QLineSeries();
    series1->setName("y1");
    QLineSeries* series2 = new QLineSeries();
    series2->setName("y2");

    double x = -3.0;
    while(x < 0.5) {
        series1->append(x, 5.0*sin(0.7*x+2.0));
        series2->append(x, (9.0*(x+2.0)*(x+2.0)-7.0)/10.0);
        x += 0.01;
    }

    ui->graphicsView->chart()->addSeries(series1);
    ui->graphicsView->chart()->addSeries(series2);
    ui->graphicsView->chart()->createDefaultAxes();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(calc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calc() {
    int n = ui->lineEdit->text().toInt();

    if (y1 != nullptr) {
        ui->graphicsView->chart()->removeSeries(y1);
    }
    if (y2 != nullptr) {
        ui->graphicsView->chart()->removeSeries(y2);
    }

    y1 = new QScatterSeries();
    y1->setName("Непопавшие точки");
    y1->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    y1->setMarkerSize(5);
    y1->setBorderColor(QColorConstants::Yellow);

    y2 = new QScatterSeries();
    y2->setName("Попавшие точки");
    y2->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    y2->setMarkerSize(5);
    y2->setBorderColor(QColorConstants::Blue);

    int inside = 0;

    for (int i = 0; i < n; i++) {
        double x = -3.0 + ((double)rand() / RAND_MAX) * (0.5 - -3.0);
        double y = -1.0 + ((double)rand() / RAND_MAX) * (5.0 - -1.0);

        double xy1 = 5.0*sin(0.7*x+2.0);
        double xy2 = (9.0*(x+2.0)*(x+2.0)-7.0)/10.0;

        bool underY1 = y <= xy1;
        bool aboveY2 = y >= xy2;

        bool ins = underY1 && aboveY2;

        if (ins) {
            y2->append(x, y);
            inside++;
        } else {
            y1->append(x, y);
        }
    }

    double footprint = 6.0 * 3.5 * (double(inside) / double(n));

    ui->label_5->setText(QString::number(footprint));

    ui->graphicsView->chart()->addSeries(y1);
    ui->graphicsView->chart()->addSeries(y2);
    ui->graphicsView->chart()->createDefaultAxes();
}
