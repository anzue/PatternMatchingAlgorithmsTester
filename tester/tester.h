#ifndef TESTER_H
#define TESTER_H

#include "algorithms/consts.h"
#include "algorithms/executablealgo.h"
#include <QList>
#include <QString>

class Tester {
  private:
    QList<QString> testInfo;

  public:
    vector<vector<float>> test(vector<Algo*> algorithms);
    QList<QString> getTestInfo() { return testInfo; }
};

#endif // TESTER_H
