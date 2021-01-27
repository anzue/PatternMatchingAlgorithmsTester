#include "progressbar.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <main/mainchart.h>

ProgressBar::ProgressBar(MainChart* parent) : QWidget(parent) {
    sigmaProgress = new QProgressBar;
    sigmaProgress->setVisible(false);

    mProgress = new QProgressBar;

    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(sigmaProgress);
    layout->addWidget(mProgress);

    this->setLayout(layout);
}
