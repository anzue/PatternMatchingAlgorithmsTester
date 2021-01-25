#ifndef MAINCHART_H
#define MAINCHART_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableView>
#include <QTableWidget>
#include <QtCharts>

#include "algorithms/executablealgo.h"
#include "tester/tester.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainChart;
}
QT_END_NAMESPACE

class MainChart : public QMainWindow {
    Q_OBJECT
  public:
    MainChart(QWidget* parent = nullptr);
    ~MainChart();

    void initChart();

  private:
    Ui::MainChart* ui;

    QTableWidget* runtimeTableResults;
    QTabWidget* tabs;
    QtCharts::QChartView* chartView;
    QtCharts::QChart* chart;

    Tester tester;

    vector<Algo*> algoritms;

  private slots:
    void runTests();
    void save(QString name);
    void saveGraph(QString name);
    void generateReport(QString name = "report");
};
#endif // MAINCHART_H
