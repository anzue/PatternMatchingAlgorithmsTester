#include "mainchart.h"
#include "algorithms/consts.h"
#include "ui/progressbar.h"
#include "ui_mainchart.h"
#include <QCategoryAxis>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QtCharts>
#include <iomanip>
#include <ui/controlpanel.h>

using namespace QtCharts;

MainChart::MainChart(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainChart) {
    tabs = new QTabWidget;

    for (int i = 2; i <= 256; i += (i < 4) ? 2 : (i < 16) ? 4
                                             : (i < 64)   ? 8
                                                          : 16)
        sigmaValues.append(QString::number(i));

    QWidget* tableTab = new QWidget;

    runtimeTableResults = new QTableWidget;
    runtimeTableResults->setRowCount(1);
    runtimeTableResults->setColumnCount(1);

    runtimeTableResults->setItem(0, 0, new QTableWidgetItem("Result will be here"));

    QHBoxLayout* tableLayout = new QHBoxLayout;
    tableLayout->addWidget(runtimeTableResults);
    tableTab->setLayout(tableLayout);

    chart = new QChart();
    chartView = new QChartView(chart);

    tabs->addTab(tableTab, "Table representation");
    tabs->addTab(chartView, "Graph represenation");

    if (patternLengths.isEmpty()) {
        for (int i = 2; i <= MAX_PAT_LEN; i += (i < 16 ? 2 : i < 64 ? 4
                                                         : i < 128  ? 8
                                                                    : 16))
            patternLengths.append(QString::number(i));
    }

    controlPanel = new ControlPanel(this);
    QHBoxLayout* mainHLayout = new QHBoxLayout;
    mainHLayout->addWidget(tabs);
    mainHLayout->addWidget(controlPanel);

    progressBar = new ProgressBar(this);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(mainHLayout);
    mainLayout->addWidget(progressBar);

    QWidget* central = new QWidget();
    central->setLayout(mainLayout);
    central->setMinimumHeight(900);
    central->setMinimumWidth(900);

    setCentralWidget(central);
}

MainChart::~MainChart() { delete ui; }

vector<vector<float>> toRelativeResults(vector<vector<float>> defaultResult) {
    vector<vector<float>> res(defaultResult.size(), vector<float>());

    for (int patIndx = 0; patIndx < defaultResult[0].size(); ++patIndx) {
        int minIndx = 0;
        for (int algo_id = 0; algo_id < defaultResult.size(); ++algo_id) {
            if (defaultResult[algo_id][patIndx] < defaultResult[minIndx][patIndx])
                minIndx = algo_id;
        }
        for (int algo_id = 0; algo_id < defaultResult.size(); ++algo_id) {
            res[algo_id].push_back(defaultResult[minIndx][patIndx] / defaultResult[algo_id][patIndx]);
        }
    }
    return res;
}

void MainChart::runTests() {

    unsigned int i, j, maxIdx;

    vector<Algo*> algorithms = controlPanel->getActiveAlgorithms();
    vector<vector<float>> res = test(algorithms);

    QStringList horLabels = getTestPatternLengths();
    QStringList verLabels = QStringList();
    for (auto& algo : algorithms)
        verLabels.append(QString::fromStdString(algo->name));

    unsigned int algorithmsCount = res.size();
    unsigned int patternsCount = res[0].size();

    QAbstractItemModel* const model = runtimeTableResults->model();
    model->removeRows(0, model->rowCount());
    model->removeColumns(0, model->columnCount());

    runtimeTableResults->setColumnCount(res[0].size());
    runtimeTableResults->setRowCount(res.size());

    for (i = 0; i < algorithmsCount; ++i) {
        for (j = 0; j < patternsCount; ++j) {
            QTableWidgetItem* item = runtimeTableResults->item(i, j);
            if (!item) {
                item = new QTableWidgetItem();
                runtimeTableResults->setItem(i, j, item);
            }
            item->setText(QString::number(res[i][j]));
        }
    }

    QFont boldFont;
    boldFont.setBold(true);

    QFont simpleFont;
    simpleFont.setBold(false);

    for (i = 0; i < patternsCount; ++i) {
        maxIdx = 0;
        for (j = 0; j < algorithmsCount; ++j) {
            if (res[j][i] < res[maxIdx][i])
                maxIdx = j;
        }
        runtimeTableResults->item(maxIdx, i)->setFont(boldFont);
    }

    runtimeTableResults->setVerticalHeaderLabels(verLabels);
    runtimeTableResults->setHorizontalHeaderLabels(horLabels);
    runtimeTableResults->update();

    chart->removeAllSeries();

    float miny = 1e9;
    float maxy = -1e9;

    auto relativeResult = toRelativeResults(res);

    for (i = 0; i < algorithmsCount; ++i) {
        QLineSeries* series = new QLineSeries(chart);

        series->setName(verLabels[i]);
        for (int j = 0; j < res[i].size(); ++j) {
            series->append(horLabels[j].toInt(), relativeResult[i][j]);
            miny = min(miny, res[i][j]);
            maxy = max(maxy, res[i][j]);
        }
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    QCategoryAxis* axisX = new QCategoryAxis;
    axisX->setRange(horLabels.begin()->toInt(), horLabels.rbegin()->toInt());
    axisX->setTickCount(horLabels.size());
    for (auto xlabel : horLabels)
        axisX->append(xlabel, xlabel.toInt());

    axisX->setLabelFormat("%.0f");
    chart->setAxisX(axisX);
}

void MainChart::generateReport(QString name) {
    QFile file(name + ".md");
    file.remove();
    file.close();
    vector<int> sigmaDisplayValues = {4, 8, 16, 32, 64, 96, 128, 192, 256};
    int oldSigma = SIGMA;

    progressBar->sigmaProgress->setValue(0);
    progressBar->sigmaProgress->setVisible(true);
    progressBar->sigmaProgress->setMaximum(sigmaDisplayValues.size());
    for (int& sigma : sigmaDisplayValues) {
        progressBar->sigmaProgress->setFormat("Sigma progress " + QString::number(sigma));
        progressBar->sigmaProgress->setValue(progressBar->sigmaProgress->value() + 1);

        SIGMA = sigma;
        runTests();
        save(name);
    }
    progressBar->sigmaProgress->setVisible(false);
    SIGMA = oldSigma;
}
