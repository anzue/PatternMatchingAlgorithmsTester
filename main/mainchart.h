#ifndef MAINCHART_H
#define MAINCHART_H

#include <QMainWindow>
#include <QTableView>
#include <QTabWidget>
#include <QTableWidget>
#include <QtCharts>

#include "Tester/tester.h"
#include "Algorithms/executablealgo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainChart; }
QT_END_NAMESPACE

class MainChart : public QMainWindow
{
    Q_OBJECT
public:
    MainChart(QWidget *parent = nullptr);
    ~MainChart();

    void initChart();

private:
    Ui::MainChart *ui;

    QTableWidget *runtimeTableResults;
    QTabWidget *tabs;
    QtCharts::QChart *chart;

    Tester tester;

    vector<ExecutableAlgo*> algoritms;

private slots:
    void refreshAllAction();
};
#endif // MAINCHART_H
