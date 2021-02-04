#include "mainchart.h"

#include <QApplication>

#ifdef MATCH_DEBUGGING
std::map<string, vector<int>> matches_pos;
#endif

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainChart w;
    w.show();
    return a.exec();
}
