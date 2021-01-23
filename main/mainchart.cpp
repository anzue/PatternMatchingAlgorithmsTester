#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtCharts>

#include "algorithms/consts.h"
#include "mainchart.h"
#include "ui_mainchart.h"

using namespace QtCharts;

QStringList patternLengths;
QStringList sigmaValues;

MainChart::MainChart(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainChart) {
    tester = Tester();
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
    connect(saveToFile, &QPushButton::released, [=]() { save(saveFileName->text()); });

    QCheckBox* autosave = new QCheckBox;
    autosave->setChecked(true);
    autosave->setText("Autosave");

    connect(refreshAll, &QPushButton::released, [=]() {
        refreshAllAction();
        if (autosave->isChecked())
            save("auto_" + QString::number(SIGMA));
    });

    QVBoxLayout* algorithmSelectionLayout = new QVBoxLayout;

    algoritms = {
        new ExecutableAlgo("Horspool", search_h, false),
        new RZk_byte_v1<13>(),
        new RZk_byte_v1<14>(),
        (new RZk_byte_v1<15>())->withSelection(false),
        (new RZk_byte_v1<16>())->withSelection(false),
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

    };

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
    QVBoxLayout* controlLayout = new QVBoxLayout;

    controlLayout->addLayout(algorithmSelectionLayout);

    QComboBox* sigmaComboBox = new QComboBox;

    if (sigmaValues.isEmpty()) {
        for (int i = 2; i <= 256; i += (i < 4) ? 2 : (i < 16) ? 4 : (i < 64) ? 8 : 16)
            sigmaValues.append(QString::number(i));
    }
    sigmaComboBox->addItems(sigmaValues);
    sigmaComboBox->setCurrentText("256");
    sigmaComboBox->setFixedWidth(50);
    connect(sigmaComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) { SIGMA = sigmaValues.at(index).toInt(); });

    if (patternLengths.isEmpty()) {
        for (int i = 2; i <= MAX_PAT_LEN; i += (i < 16 ? 2 : i < 64 ? 4 : i < 128 ? 8 : 16))
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
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList row;
        QString separator;

        data << "Sigma" << SIGMA << "\n";
        row << "PatLength";
        for (int c = 0; c < runtimeTableResults->columnCount(); ++c) {
            row << runtimeTableResults->horizontalHeaderItem(c)->data(Qt::DisplayRole).toString();
            separator = separator + " --- " + ((c < runtimeTableResults->columnCount() - 1) ? "|" : "");
        }
        data << row.join(" | ") << "\n";
        data << separator << "\n";

        for (int r = 0; r < runtimeTableResults->rowCount(); ++r) {
            row.clear();
            row << runtimeTableResults->verticalHeaderItem(r)->data(Qt::DisplayRole).toString();
            for (int c = 0; c < runtimeTableResults->columnCount(); ++c) {
                if (runtimeTableResults->item(r, c)->font().weight() == QFont::Bold)
                    row << " **" + runtimeTableResults->item(r, c)->text() + "** ";
                else
                    row << runtimeTableResults->item(r, c)->text();
            }
            data << row.join(" | ") << "\n";
        }
        statusBar()->showMessage(tr("File saved successfully."), 3000);
        file.close();
    }

    //    QPixmap pixmap(chartView->size());
    //    chartView->render(&pixmap);
    //    pixmap.save(name + ".jpg");

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

void MainChart::refreshAllAction() {
    vector<ExecutableAlgo*> algosTmp;
    QList<QString> ver_labels;

    unsigned int i, j, maxIdx;

    for (i = 0; i < algoritms.size(); ++i) {
        if (algoritms[i]->isSelected) {
            algosTmp.push_back(algoritms[i]);
            ver_labels.push_back(QString::fromStdString(algoritms[i]->name));
        }
    }

    auto res = tester.test(algosTmp);
    auto hor_labels = tester.getTestInfo();

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
            // runtimeTableResults->item(j, i)->setFont(simpleFont);
            if (res[j][i] < res[maxIdx][i])
                maxIdx = j;
        }
        runtimeTableResults->item(maxIdx, i)->setFont(boldFont);
    }

    runtimeTableResults->setVerticalHeaderLabels(ver_labels);
    runtimeTableResults->setHorizontalHeaderLabels(hor_labels);
    runtimeTableResults->update();

    chart->removeAllSeries();

    float miny = 1e9;
    float maxy = -1e9;

    for (i = 0; i < algorithmsCount; ++i) {
        QLineSeries* series = new QLineSeries(chart);

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
