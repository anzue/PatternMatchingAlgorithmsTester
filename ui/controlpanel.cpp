#include "controlpanel.h"
#include "algorithms/consts.h"
#include "main/mainchart.h"
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

ControlPanel::ControlPanel(MainChart* parent)
    : QWidget(parent)
{

    algorithms = {

        // new KExecutableAlgo("RZ{}_w2_mmx", RZk_w2_mmx, 13, false),
        // new KExecutableAlgo("RZ{}_w2_mmx", RZk_w2_mmx, 14, false),

        new KExecutableAlgo("RZ{}_byte", RZk_byte, 13, true),
        new KExecutableAlgo("RZ{}_byte", RZk_byte, 14, false),

        new KExecutableAlgo("RZ{}_w2_byte", RZk_w2_byte, 13, true),
        new KExecutableAlgo("RZ{}_w2_byte", RZk_w2_byte, 14, false),

        new KExecutableAlgo("RZ{}_w2_pointer", RZk_w2_pointer, 13, true),
        new KExecutableAlgo("RZ{}_w2_pointer", RZk_w2_pointer, 14, false),

        new KExecutableAlgo("RZ{}_w2_simd3", RZk_w2_simd3, 13, true),

        new KExecutableAlgo("RZ{}_w3_byte", RZk_w3_byte, 13, true),
        new KExecutableAlgo("RZ{}_w3_byte", RZk_w3_byte, 14, false),

        new KExecutableAlgo("RZ{}_w3_pointer", RZk_w3_pointer, 13, true),
        new KExecutableAlgo("RZ{}_w3_pointer", RZk_w3_pointer, 14, false),

        new KExecutableAlgo("RZ{}_w3_simd1", RZk_w3_simd1, 13, true),
        new KExecutableAlgo("RZ{}_w3_simd1", RZk_w3_simd1, 14, false),

        new KExecutableAlgo("RZ{}_w3_simd2", RZk_w3_simd2, 13, true),
        new KExecutableAlgo("RZ{}_w3_simd2", RZk_w3_simd2, 14, false),

        new KExecutableAlgo("RZ{}_w3_simd3", RZk_w3_simd3, 13, true),

        new KExecutableAlgo("RZ{}_w3_simd2_range_cmp", RZk_w3_simd2_range_cmp, 13, true),

        new KExecutableAlgo("RZ{}_w3_simd3_range_cmp", RZk_w3_simd3_range_cmp, 13, true),

        new KExecutableAlgo("RZ{}_w4_simd2", RZk_w4_simd2, 13, true),

        new KExecutableAlgo("RZ{}_w4_simd3", RZk_w4_simd3, 13, true),
        new KExecutableAlgo("RZ{}_w4_simd3_pointer", RZk_w4_simd3_pointer, 13, false),

        new KExecutableAlgo("test_algo_{}", test_algo, 13, false),
        //  new KExecutableAlgo("test_algo_{}", test_algo, 14, false),

        //   new ExecutableAlgo("FSBNDM_W1", fsbndm_w1, false),
        //   new ExecutableAlgo("FSBNDM_W2", fsbndm_w2, false),
        new ExecutableAlgo("FSBNDM_W4", fsbndm_w4, false),
        new ExecutableAlgo("FSBNDM_W6", fsbndm_w6, false),
        new ExecutableAlgo("FSBNDM_W8", fsbndm_w8, false),
        new ExecutableAlgo("FSBNDM_31", fsbndmq31, false),

        new ExecutableAlgo("FS", fs, false),
        new ExecutableAlgo("FSw4", fs_w4, false),
        new ExecutableAlgo("FSw6", fs_w6, false),
        new ExecutableAlgo("FSw8", fs_w8, true),
        new ExecutableAlgo("FJS", fjs, true),

        new KExecutableAlgo("Z{}_byte", Zk_byte, 13, true),
        new KExecutableAlgo("Z{}_byte", Zk_byte, 14, false),

        new KExecutableAlgo("Z{}_w2_byte", Zk_w2_byte, 13, true),
        new KExecutableAlgo("Z{}_w2_byte", Zk_w2_byte, 14, false),

        new ExecutableAlgo("Z8", Z8_byte, false),

        //  new KExecutableAlgo("Z{}_shift2", Zk_shift2_byte, 13, true),

    };

    QPushButton* rerunTests = new QPushButton("Rerun tests");

    connect(rerunTests, &QPushButton::released, [=]() {
        parent->runTests();
    });

    QPushButton* saveTable = new QPushButton("Save table");
    connect(saveTable, &QPushButton::released, [=]() {
        QString name = QFileDialog::getSaveFileName(this, tr("Save table"), "../PatMatchAlgoTester/results", tr("MD reports (*.md)"));

        parent->save(name);
    });

    QPushButton* saveGraph = new QPushButton("Save graph");
    connect(saveGraph, &QPushButton::released, [=]() {
        QString name = QFileDialog::getSaveFileName(this, tr("Save graph"), "../PatMatchAlgoTester/results", tr("Images (*.jpg)"));
        parent->saveGraph(name);
    });

    QPushButton* generateReportButton = new QPushButton;
    generateReportButton->setText("Generate report");
    connect(generateReportButton, &QPushButton::released, [=]() {
        QString name = QFileDialog::getSaveFileName(this, tr("Save File"), "../PatMatchAlgoTester/results", tr("MD reports (*.md)"));
        parent->generateReport(name); });

    QComboBox* sigmaComboBox = new QComboBox;

    sigmaComboBox->addItems(parent->sigmaValues);
    sigmaComboBox->setCurrentText("256");
    sigmaComboBox->setFixedWidth(50);
    connect(sigmaComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) { SIGMA = parent->sigmaValues.at(index).toInt(); });

    QVBoxLayout* algorithmSelectionLayout = new QVBoxLayout;

    for (int i = 0; i < (int)algorithms.size(); ++i) {
        QCheckBox* algoCheckbox = new QCheckBox;
        algoCheckbox->setChecked(algorithms[i]->isSelected);
        algoCheckbox->setText(QString::fromStdString(algorithms[i]->name));
        algorithmSelectionLayout->addWidget(algoCheckbox);

        connect(algoCheckbox, QOverload<int>::of(&QCheckBox::stateChanged), [=](int state) {
            assert(state != Qt::PartiallyChecked);
            if (state == Qt::Unchecked) {
                algorithms[i]->isSelected = false;
            } else if (state == Qt::Checked) {
                algorithms[i]->isSelected = true;
            }
        });
    }

    QWidget* algorithmSelectionWidget = new QWidget;
    algorithmSelectionWidget->setLayout(algorithmSelectionLayout);
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidget(algorithmSelectionWidget);

    QVBoxLayout* controlLayout = new QVBoxLayout;

    controlLayout->addWidget(scrollArea);

    QComboBox* minmComboBox = new QComboBox;
    minmComboBox->addItems(parent->patternLengths);
    connect(minmComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) { parent->MINM = parent->patternLengths.at(index).toInt(); });
    minmComboBox->setCurrentText("48");
    minmComboBox->setFixedWidth(50);

    QComboBox* maxmComboBox = new QComboBox;
    maxmComboBox->addItems(parent->patternLengths);
    connect(maxmComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) { parent->MAXM = parent->patternLengths.at(index).toInt(); });
    maxmComboBox->setCurrentText("416");
    maxmComboBox->setFixedWidth(50);

    QSpinBox* outerItersComboBox = new QSpinBox;
    outerItersComboBox->setMinimum(5);
    outerItersComboBox->setMaximum(500);
    outerItersComboBox->setValue(5);
    connect(outerItersComboBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) { parent->OUTER_ITER = value; });

    QSpinBox* innerItersComboBox = new QSpinBox;
    innerItersComboBox->setMinimum(1);
    innerItersComboBox->setMaximum(1000);
    innerItersComboBox->setValue(10);
    connect(innerItersComboBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) { parent->INNER_ITER = value; });

    controlLayout->addWidget(new QLabel("Alphabet Size"));
    controlLayout->addWidget(sigmaComboBox);

    controlLayout->addWidget(new QLabel("Min Pattern length"));
    controlLayout->addWidget(minmComboBox);

    controlLayout->addWidget(new QLabel("Max pattern length"));
    controlLayout->addWidget(maxmComboBox);

    controlLayout->addWidget(new QLabel("Outer Iterations"));
    controlLayout->addWidget(outerItersComboBox);

    controlLayout->addWidget(new QLabel("Inner Iterations"));
    controlLayout->addWidget(innerItersComboBox);

    controlLayout->addWidget(rerunTests);

    controlLayout->addWidget(saveTable);
    controlLayout->addWidget(saveGraph);
    controlLayout->addWidget(generateReportButton);

    controlLayout->setAlignment(Qt::AlignTop);

    this->setLayout(controlLayout);
    this->setMaximumWidth(400);
}

vector<Algo*> ControlPanel::getActiveAlgorithms()
{
    vector<Algo*> tmp;
    for (auto& algo : algorithms)
        if (algo->isSelected)
            tmp.push_back(algo);
    return tmp;
}
