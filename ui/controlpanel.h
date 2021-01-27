#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "algorithms/executablealgo.h"
#include <QMainWindow>
#include <QWidget>

class MainChart;

class ControlPanel : public QWidget {
    Q_OBJECT

  private:
    vector<Algo*> algorithms;

  public:
    explicit ControlPanel(MainChart* parent = nullptr);

    ControlPanel(vector<Algo*> algorithms);

    vector<Algo*> getActiveAlgorithms();

  signals:
};

#endif // CONTROLPANEL_H
