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

ControlPanel::ControlPanel(MainChart* parent) : QWidget(parent) {

    algorithms = {
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

    QPushButton* rerunTests = new QPushButton("Rerun tests");

    connect(rerunTests, &QPushButton::released, [=]() {
        parent->runTests();
    });

    QLineEdit* saveFileName = new QLineEdit;
    saveFileName->setText("savenamePattern");
    saveFileName->setMaximumWidth(200);

    QPushButton* saveToFile = new QPushButton("Save to file");
    saveFileName->setMaximumWidth(200);
    connect(saveToFile, &QPushButton::released, [=]() {
        parent->save(saveFileName->text());
        parent->saveGraph(saveFileName->text());
    });

    QPushButton* generateReportButton = new QPushButton;
    generateReportButton->setText("Generate report");
    connect(generateReportButton, &QPushButton::released, [=]() { parent->generateReport("readme"); });

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
    minmComboBox->setCurrentText("40");
    minmComboBox->setFixedWidth(50);

    QComboBox* maxmComboBox = new QComboBox;
    maxmComboBox->addItems(parent->patternLengths);
    connect(maxmComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) { parent->MAXM = parent->patternLengths.at(index).toInt(); });
    maxmComboBox->setCurrentText("400");
    maxmComboBox->setFixedWidth(50);

    controlLayout->addWidget(new QLabel("Alphabet Size"));
    controlLayout->addWidget(sigmaComboBox);

    controlLayout->addWidget(new QLabel("Min Pattern length"));
    controlLayout->addWidget(minmComboBox);

    controlLayout->addWidget(new QLabel("Max pattern length"));
    controlLayout->addWidget(maxmComboBox);

    controlLayout->addWidget(rerunTests);

    controlLayout->addWidget(saveFileName);
    controlLayout->addWidget(saveToFile);
    controlLayout->addWidget(generateReportButton);

    controlLayout->setAlignment(Qt::AlignTop);

    this->setLayout(controlLayout);
    this->setMaximumWidth(400);
}

vector<Algo*> ControlPanel::getActiveAlgorithms() {
    vector<Algo*> tmp;
    for (auto& algo : algorithms)
        if (algo->isSelected)
            tmp.push_back(algo);
    return tmp;
}
