#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QProgressBar>
#include <QWidget>

class MainChart;

class ProgressBar : public QWidget {
    Q_OBJECT

  public:
    explicit ProgressBar(MainChart* parent = nullptr);

    QProgressBar* sigmaProgress;
    QProgressBar* mProgress;

  signals:
};

#endif // PROGRESSBAR_H
