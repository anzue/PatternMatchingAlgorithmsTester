#include <QCategoryAxis>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QtCharts>

#include <iomanip>

#include "algorithms/consts.h"
#include "mainchart.h"
#include "ui_mainchart.h"

const int TOTAL = 500000;
unsigned char T[TOTAL], T1[TOTAL], P[MAX_PAT_LEN];

unsigned int i, ii;
unsigned int m = 200, glob = 0;

unsigned int SIGMA = 256, MINM = 2, MAXM = 200, N = TOTAL - MAX_PAT_LEN, ITER = 20;

LARGE_INTEGER start, finish, freq;

QStringList patternLengths;
QStringList sigmaValues;

using namespace QtCharts;

MainChart::MainChart(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainChart) {
    tabs = new QTabWidget;

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

    QPushButton* refreshAll = new QPushButton("Rerun tests");

    QLineEdit* saveFileName = new QLineEdit;
    saveFileName->setText("savenamePattern");
    saveFileName->setMaximumWidth(200);

    QPushButton* saveToFile = new QPushButton("Save to file");
    saveFileName->setMaximumWidth(200);
    connect(saveToFile, &QPushButton::released, [=]() {
        save(saveFileName->text());
        saveGraph(saveFileName->text());
    });

    QCheckBox* autosave = new QCheckBox;
    autosave->setChecked(true);
    autosave->setText("Autosave");

    connect(refreshAll, &QPushButton::released, [=]() {
        runTests();
        if (autosave->isChecked())
            save("auto_" + QString::number(SIGMA));
    });

    QPushButton* generateReportButton = new QPushButton;
    generateReportButton->setText("Generate report");
    connect(generateReportButton, &QPushButton::released, [=]() { generateReport("readme"); });

    algoritms = {
        // new ExecutableAlgo("Horspool", search_h, false),
        new KExecutableAlgo("RZ{}_byte", search_RZk_byte, 13, true),
        new KExecutableAlgo("RZ{}_byte", search_RZk_byte, 14, true),
        new KExecutableAlgo("RZ{}_byte", search_RZk_byte, 15, false),
        new KExecutableAlgo("RZ{}_byte", search_RZk_byte, 16, false),

        new ExecutableAlgo("FSBNDM_W1", search_fsbndm_w1, false),
        new ExecutableAlgo("FSBNDM_W2", search_fsbndm_w2, false),
        new ExecutableAlgo("FSBNDM_W4", search_fsbndm_w4, false),
        new ExecutableAlgo("FSBNDM_W6", search_fsbndm_w6, false),
        new ExecutableAlgo("FSBNDM_W8", search_fsbndm_w8, true),
        new ExecutableAlgo("FSBNDM_31", search_fsbndmq31, false),

        new ExecutableAlgo("FS", search_fs, false),
        new ExecutableAlgo("FSw4", search_fs_w4, false),
        new ExecutableAlgo("FSw6", search_fs_w6, false),
        new ExecutableAlgo("FSw8", search_fs_w8, true),
        new ExecutableAlgo("FJS", search_fjs, false),

        new KExecutableAlgo("RZ{}_w2_byte", search_RZk_w2_byte, 13, true),
        new KExecutableAlgo("RZ{}_w2_byte", search_RZk_w2_byte, 14, true),
        new KExecutableAlgo("RZ{}_w2_byte", search_RZk_w2_byte, 15, false),
        new KExecutableAlgo("RZ{}_w2_byte", search_RZk_w2_byte, 16, false),

        new KExecutableAlgo("RZ{}_w2_pointer", search_RZk_w2_pointer, 13, true),
        new KExecutableAlgo("RZ{}_w2_pointer", search_RZk_w2_pointer, 14, true),
        new KExecutableAlgo("RZ{}_w2_pointer", search_RZk_w2_pointer, 15, false),
        new KExecutableAlgo("RZ{}_w2_pointer", search_RZk_w2_pointer, 16, false),

        new KExecutableAlgo("RZ{}_w3_byte", search_RZk_w3_byte, 13, true),
        new KExecutableAlgo("RZ{}_w3_byte", search_RZk_w3_byte, 14, true),
        new KExecutableAlgo("RZ{}_w3_byte", search_RZk_w3_byte, 15, false),
        new KExecutableAlgo("RZ{}_w3_byte", search_RZk_w3_byte, 16, false),

        new KExecutableAlgo("RZ{}_w3_pointer", search_RZk_w3_pointer, 13, true),
        new KExecutableAlgo("RZ{}_w3_pointer", search_RZk_w3_pointer, 14, true),
        new KExecutableAlgo("RZ{}_w3_pointer", search_RZk_w3_pointer, 15, false),
        new KExecutableAlgo("RZ{}_w3_pointer", search_RZk_w3_pointer, 16, false),

        new KExecutableAlgo("test_algo_{}", search_test_algo, 13, true),
        new KExecutableAlgo("test_algo_{}", search_test_algo, 14, true),
        new KExecutableAlgo("test_algo_{}", search_test_algo, 15, false),
        new KExecutableAlgo("test_algo_{}", search_test_algo, 16, false),
    };

    QVBoxLayout* algorithmSelectionLayout = new QVBoxLayout;

    for (int i = 0; i < (int)algoritms.size(); ++i) {
        QCheckBox* algoCheckbox = new QCheckBox;
        algoCheckbox->setChecked(algoritms[i]->isSelected);
        algoCheckbox->setText(QString::fromStdString(algoritms[i]->name));
        algorithmSelectionLayout->addWidget(algoCheckbox);

        connect(algoCheckbox, QOverload<int>::of(&QCheckBox::stateChanged), [=](int state) {
            assert(state != Qt::PartiallyChecked);
            if (state == Qt::Unchecked) {
                algoritms[i]->isSelected = false;
            } else if (state == Qt::Checked) {
                algoritms[i]->isSelected = true;
            }
        });
    }
    QWidget* algorithmSelectionWidget = new QWidget;
    algorithmSelectionWidget->setLayout(algorithmSelectionLayout);
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidget(algorithmSelectionWidget);

    QVBoxLayout* controlLayout = new QVBoxLayout;

    controlLayout->addWidget(scrollArea);

    QComboBox* sigmaComboBox = new QComboBox;

    if (sigmaValues.isEmpty()) {
        for (int i = 2; i <= 256; i += (i < 4) ? 2 : (i < 16) ? 4
                                                 : (i < 64)   ? 8
                                                              : 16)
            sigmaValues.append(QString::number(i));
    }
    sigmaComboBox->addItems(sigmaValues);
    sigmaComboBox->setCurrentText("256");
    sigmaComboBox->setFixedWidth(50);
    connect(sigmaComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) { SIGMA = sigmaValues.at(index).toInt(); });

    if (patternLengths.isEmpty()) {
        for (int i = 2; i <= MAX_PAT_LEN; i += (i < 16 ? 2 : i < 64 ? 4
                                                         : i < 128  ? 8
                                                                    : 16))
            patternLengths.append(QString::number(i));
    }

    QComboBox* minmComboBox = new QComboBox;
    minmComboBox->addItems(patternLengths);
    connect(minmComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) { MINM = patternLengths.at(index).toInt(); });
    minmComboBox->setCurrentText("40");
    minmComboBox->setFixedWidth(50);

    QComboBox* maxmComboBox = new QComboBox;
    maxmComboBox->addItems(patternLengths);
    connect(maxmComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) { MAXM = patternLengths.at(index).toInt(); });
    maxmComboBox->setCurrentText("400");
    maxmComboBox->setFixedWidth(50);

    controlLayout->addWidget(new QLabel("Alphabet Size"));
    controlLayout->addWidget(sigmaComboBox);

    controlLayout->addWidget(new QLabel("Min Pattern length"));
    controlLayout->addWidget(minmComboBox);

    controlLayout->addWidget(new QLabel("Max pattern length"));
    controlLayout->addWidget(maxmComboBox);

    controlLayout->addWidget(refreshAll);

    controlLayout->addWidget(saveFileName);
    controlLayout->addWidget(saveToFile);
    controlLayout->addWidget(autosave);
    controlLayout->addWidget(generateReportButton);

    controlLayout->setAlignment(Qt::AlignTop);

    QWidget* fakeControlWidget = new QWidget;
    fakeControlWidget->setLayout(controlLayout);
    fakeControlWidget->setMaximumHeight(900);
    fakeControlWidget->setMaximumWidth(200);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(tabs);
    mainLayout->addWidget(fakeControlWidget);

    QWidget* central = new QWidget();
    central->setLayout(mainLayout);
    central->setMinimumHeight(900);
    central->setMinimumWidth(900);

    setCentralWidget(central);
}

MainChart::~MainChart() { delete ui; }

void MainChart::save(QString name) {
    QFile file(name + ".md");
    if (file.open(QFile::WriteOnly | QFile::Append)) {
        QTextStream data(&file);
        QStringList row;
        QString separator = "| --- ";

        data << "  \nSigma" << SIGMA << "  \n";
        row << "PatLength";
        for (int c = 0; c < runtimeTableResults->columnCount(); ++c) {
            row << runtimeTableResults->horizontalHeaderItem(c)->data(Qt::DisplayRole).toString();
            separator = separator + " |  --- ";
        }
        data << "|  " << row.join("  |  ") << "  |\n";
        data << separator << " |\n";

        for (int r = 0; r < runtimeTableResults->rowCount(); ++r) {
            row.clear();
            row << runtimeTableResults->verticalHeaderItem(r)->data(Qt::DisplayRole).toString();
            for (int c = 0; c < runtimeTableResults->columnCount(); ++c) {
                if (runtimeTableResults->item(r, c)->font().weight() == QFont::Bold)
                    row << " **" + runtimeTableResults->item(r, c)->text() + "** ";
                else
                    row << runtimeTableResults->item(r, c)->text();
            }
            data << "|  " << row.join("  |  ") << "  |\n";
        }
        statusBar()->showMessage(tr("File saved successfully."), 3000);
        file.close();
    }
}

void MainChart::saveGraph(QString name) {
    QPixmap p = chartView->grab();
    QOpenGLWidget* glWidget = chartView->findChild<QOpenGLWidget*>();
    if (glWidget) {
        QPainter painter(&p);
        QPoint d = glWidget->mapToGlobal(QPoint()) - chartView->mapToGlobal(QPoint());
        painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
        painter.drawImage(d, glWidget->grabFramebuffer());
        painter.end();
    }
    p.save(name + ".jpg", "jpg");
}

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
    vector<Algo*> algosTmp;
    QList<QString> ver_labels;

    unsigned int i, j, maxIdx;

    for (i = 0; i < algoritms.size(); ++i) {
        if (algoritms[i]->isSelected) {
            algosTmp.push_back(algoritms[i]);
            ver_labels.push_back(QString::fromStdString(algoritms[i]->name));
        }
    }

    auto res = test(algosTmp);

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

    runtimeTableResults->setVerticalHeaderLabels(ver_labels);
    runtimeTableResults->setHorizontalHeaderLabels(horLabels);
    runtimeTableResults->update();

    chart->removeAllSeries();

    float miny = 1e9;
    float maxy = -1e9;

    auto relativeResult = toRelativeResults(res);

    for (i = 0; i < algorithmsCount; ++i) {
        QLineSeries* series = new QLineSeries(chart);

        series->setName(ver_labels[i]);
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
    for (int& sigma : sigmaDisplayValues) {
        statusBar()->showMessage("Generating report for Sigma = " + sigma, 3000);
        SIGMA = sigma;
        runTests();
        save(name);
    }
    SIGMA = oldSigma;
}

vector<vector<float>> MainChart::test(vector<Algo*> algorithms) {
    QueryPerformanceFrequency(&freq);
    cout << "Running test : \n"
         << "SIGMA = " << SIGMA << "\n"
         << "MINM = " << MINM << "\n"
         << "MAXM = " << MAXM << "\n"
         << std::endl;

    vector<vector<float>> res(algorithms.size(), vector<float>(0));
    horLabels.clear();
    for (int i = 0; i < N; i++) {
        T[i] = (rand() + glob % 320) % SIGMA;
        glob = (glob * 11 + 30157) % 499;
    }
    for (int i = 0; i < m; i++) {
        P[i] = (rand() + glob) % SIGMA;
        glob = (glob * 123 + 3157) % 893;
    }

    int max_ig = 5;

    //    std::setprecision(2);
    //    std::cout << "Algo\t";
    //    for (i = 0; i < algorithms.size(); ++i)
    //        std::cout << std::setw(16) << algorithms[i]->name << " ";
    //    std::cout << "\n";

    for (QString& mstr : patternLengths) {
        m = mstr.toInt();

        if (m < MINM || m > MAXM)
            continue;

        vector<int> matches(algorithms.size(), 0);
        vector<float> execTime(algorithms.size(), 0);

        horLabels.push_back(mstr);

        for (int ig = 0; ig < max_ig; ig++) {
            memcpy(T1, T, N);

            for (int i = 0; i < m; i++) {
                P[i] = (rand() + glob) % SIGMA;
                glob = (glob * 123 + 3157) % 893;
            }

            ITER = 20;
            for (ii = 0; ii < ITER; ii++) {
                int patpos = (rand()) % (N - m - 2);
                memcpy(T1 + patpos, P, m);
                memcpy(T1, P, m);

                for (i = 0; i < algorithms.size(); ++i) {
                    matches[i] += algorithms[i]->search(P, (int)m, T1, (int)N, &execTime[i]);

                    if (matches[i] != matches[0]) {
                        cout << "Result for algo " << algorithms[i]->name << " is " << matches[i]
                             << " while for algo " + algorithms[0]->name + " is " + to_string(matches[0])
                             << "\nM = " << m << ", SIGMA = " << SIGMA << std::endl;
                    }
                    // assert(matches[i] == matches[0]);
                }
            }
        }
        //  cout << "M = " << m << "\t";
        for (i = 0; i < algorithms.size(); ++i) {
            res[i].push_back(execTime[i] / ITER / max_ig);
            //    cout << std::setw(16) << execTime[i] / ITER / max_ig << " "; //<< "\t" << matches[i] << "\t";
        }
        //  cout << "\n";
    }
    //  cout << std::endl;

    return res;
}
