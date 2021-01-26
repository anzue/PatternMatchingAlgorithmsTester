#ifndef MAINCHART_H
#define MAINCHART_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableView>
#include <QTableWidget>
#include <QtCharts>

#include "algorithms/executablealgo.h"

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

    vector<vector<float>> test(vector<Algo*> algorithms);
    QList<QString> gethorLabels() { return horLabels; }

    void initChart();

  private:
    Ui::MainChart* ui;

    QTableWidget* runtimeTableResults;
    QTabWidget* tabs;
    QtCharts::QChartView* chartView;
    QtCharts::QChart* chart;

    vector<Algo*> algoritms;
    QList<QString> horLabels;

  private slots:
    void runTests();
    void save(QString name);
    void saveGraph(QString name);
    void generateReport(QString name = "report");
};
#endif // MAINCHART_H
