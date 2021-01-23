#ifndef TESTER_H
#define TESTER_H

#include <QList>
#include <QString>
#include "algorithms/consts.h"
#include "Algorithms/executablealgo.h"

class Tester
{
private:

    QList<QString> testInfo;
public:
    vector<vector< float > > test(vector<ExecutableAlgo*> algorithms);
    QList<QString> getTestInfo() {return testInfo;}
};

#endif // TESTER_H
