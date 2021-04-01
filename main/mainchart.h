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

class ControlPanel;
class ProgressBar;

class MainChart : public QMainWindow {
    Q_OBJECT
  public:
    MainChart(QWidget* parent = nullptr);
    ~MainChart();

    vector<vector<float>> test(vector<Algo*> algorithms);

    void initChart();

  private:
    unsigned int MINM = 2, MAXM = 200, N = TOTAL - 2 * MAX_PAT_LEN, OUTER_ITER = 5, INNER_ITER = 3;

    QStringList patternLengths;
    QStringList sigmaValues;

    QStringList getTestPatternLengths();

    Ui::MainChart* ui;

    ControlPanel* controlPanel;
    ProgressBar* progressBar;

    QTableWidget* runtimeTableResults;
    QTabWidget* tabs;
    QtCharts::QChartView* chartView;
    QtCharts::QChart* chart;

  private slots:
    void runTests();
    void save(QString name);
    void saveGraph(QString name);
    void generateReport(QString name = "report");

    friend class ControlPanel;
    friend class ProgressBar;
};
#endif // MAINCHART_H
