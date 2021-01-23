#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtCharts>

#include "Algorithms/consts.h"
#include "mainchart.h"
#include "ui_mainchart.h"

using namespace QtCharts;

MainChart::MainChart(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainChart)
{
    tester = Tester();
    tabs = new QTabWidget;

    QWidget* tableTab = new QWidget;

    runtimeTableResults = new QTableWidget;
    runtimeTableResults->setRowCount(1);
    runtimeTableResults->setColumnCount(1);

    runtimeTableResults->setItem(0, 0, new QTableWidgetItem("Hello"));

    QHBoxLayout* tableLayout = new QHBoxLayout;
    tableLayout->addWidget(runtimeTableResults);
    tableTab->setLayout(tableLayout);

    chart = new QChart();
    QChartView* chartView = new QChartView(chart);

    tabs->addTab(tableTab, "Table representation");
    tabs->addTab(chartView, "Graph represenation");

    QPushButton* refreshAll = new QPushButton("Rerun tests");
    connect(refreshAll, SIGNAL(released()), this, SLOT(refreshAllAction()));

    QVBoxLayout* algorithmSelectionLayout = new QVBoxLayout;

    algoritms = {
        new ExecutableAlgo("Horspool", search_h, false),
        new RZk_byte_v1<13>(),
        (new RZk_byte_v1<14>())->withSelection(false),
        (new RZk_byte_v1<15>())->withSelection(false),
        (new RZk_byte_v1<16>())->withSelection(false),
        new ExecutableAlgo("FSBNDM_W1", search_fsbndm_w1, false),
        new ExecutableAlgo("FSBNDM_W2", search_fsbndm_w2, false),
        new ExecutableAlgo("FSBNDM_W4", search_fsbndm_w4, false),
        new ExecutableAlgo("FSBNDM_W6", search_fsbndm_w6, false),
        new ExecutableAlgo("FSBNDM_W8", search_fsbndm_w8, true),
        new ExecutableAlgo("FSBNDM_31", search_fsbndmq31, false),
        new ExecutableAlgo("FSw4", search_fs_w4, false),
        new ExecutableAlgo("FSw6", search_fs_w6, false),
        new ExecutableAlgo("FSw8", search_fs_w8, false)

    };

    for (int i = 0; i < (int)algoritms.size(); ++i) {
        QCheckBox* algoCheckbox = new QCheckBox;
        algoCheckbox->setChecked(algoritms[i]->isSelected);
        algoCheckbox->setText(QString::fromStdString(algoritms[i]->name));
        algorithmSelectionLayout->addWidget(algoCheckbox);

        connect(algoCheckbox, QOverload<int>::of(&QCheckBox::stateChanged),
            [=](int state) {
                assert(state != Qt::PartiallyChecked);
                if (state == Qt::Unchecked) {
                    algoritms[i]->isSelected = false;
                } else if (state == Qt::Checked) {
                    algoritms[i]->isSelected = true;
                }
            });
    }
    QVBoxLayout* controlLayout = new QVBoxLayout;

    controlLayout->addLayout(algorithmSelectionLayout);

    QComboBox* sigmaComboBox = new QComboBox;

    QStringList sigmaItems = QStringList();

    for (int i = 2; i <= 256; i += (i < 4)
             ? 2
             : (i < 16) ? 4
             : (i < 64) ? 8
                        : 16)

        sigmaItems.append(QString::number(i));

    sigmaComboBox->addItems(sigmaItems);
    sigmaComboBox->setCurrentText("256");
    sigmaComboBox->setFixedWidth(50);
    connect(sigmaComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) {
            SIGMA = sigmaItems.at(index).toInt();
        });

    QStringList mItems = QStringList();
    //   for(int i=2; i <= MAX_PAT_LEN; i+= (i< 4)?2: (i < 16)?4 : (i < 64)? 4 : 8)
    for (int i = 4; i <= MAX_PAT_LEN; i += 4)
        mItems.append(QString::number(i));

    QComboBox* minmComboBox = new QComboBox;
    minmComboBox->addItems(mItems);
    connect(minmComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) {
            MINM = mItems.at(index).toInt();
        });
    minmComboBox->setCurrentText("80");
    minmComboBox->setFixedWidth(50);

    QComboBox* maxmComboBox = new QComboBox;
    maxmComboBox->addItems(mItems);
    connect(maxmComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) {
            MAXM = mItems.at(index).toInt();
        });
    maxmComboBox->setCurrentText("160");
    maxmComboBox->setFixedWidth(50);

    QLabel* sigmaName = new QLabel("SIGMA");
    QLabel* minmName = new QLabel("MINM");
    QLabel* maxmName = new QLabel("MAXM");

    controlLayout->addWidget(sigmaName);
    controlLayout->addWidget(sigmaComboBox);

    controlLayout->addWidget(minmName);
    controlLayout->addWidget(minmComboBox);

    controlLayout->addWidget(maxmName);
    controlLayout->addWidget(maxmComboBox);

    controlLayout->addWidget(refreshAll);
    controlLayout->setAlignment(Qt::AlignTop);
    QWidget* fakeControlWidget = new QWidget;
    fakeControlWidget->setLayout(controlLayout);
    fakeControlWidget->setMaximumHeight(900);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(tabs);
    mainLayout->addWidget(fakeControlWidget);

    QWidget* central = new QWidget();
    central->setLayout(mainLayout);
    central->setMinimumHeight(900);
    central->setMinimumWidth(900);

    setCentralWidget(central);
}

MainChart::~MainChart()
{
    delete ui;
}

void MainChart::refreshAllAction()
{
    vector<ExecutableAlgo*> algosTmp;
    QList<QString> ver_labels;

    for (int i = 0; i < algoritms.size(); ++i) {
        if (algoritms[i]->isSelected) {
            algosTmp.push_back(algoritms[i]);
            ver_labels.push_back(QString::fromStdString(algoritms[i]->name));
        }
    }

    auto res = tester.test(algosTmp);

    auto hor_labels = tester.getTestInfo();

    runtimeTableResults->setColumnCount(res[0].size());
    runtimeTableResults->setRowCount(res.size());

    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            QTableWidgetItem* item = runtimeTableResults->item(i, j);
            if (!item) {
                item = new QTableWidgetItem();
                runtimeTableResults->setItem(i, j, item);
            }
            item->setText(QString::number(res[i][j]));
        }
    }
    runtimeTableResults->setVerticalHeaderLabels(ver_labels);
    runtimeTableResults->setHorizontalHeaderLabels(hor_labels);
    runtimeTableResults->update();

    chart->removeAllSeries();

    float miny = 1e9;
    float maxy = -1e9;

    for (int i = 0; i < res.size(); ++i) {
        QLineSeries* series = new QLineSeries(chart);
        //        series->setPointLabelsVisible(true);
        //        series->setPointLabelsColor(Qt::black);
        //        series->setPointLabelsFormat("@yPoint");

        series->setName(ver_labels[i]);
        for (int j = 0; j < res[i].size(); ++j) {
            series->append(hor_labels[j].toInt(), res[i][j]);
            miny = min(miny, res[i][j]);
            maxy = max(maxy, res[i][j]);
        }
        chart->addSeries(series);
    }
    chart->createDefaultAxes();
    QValueAxis* axisX = new QValueAxis;
    axisX->setRange(hor_labels.begin()->toInt(), hor_labels.rbegin()->toInt());
    axisX->setTickCount(MIN(15, (hor_labels.rbegin()->toInt() - hor_labels.begin()->toInt()) / 4));
    axisX->setLabelFormat("%.0f");
    chart->setAxisX(axisX);
}
