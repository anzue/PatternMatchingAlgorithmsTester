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

using namespace QtCharts;

void MainChart::save(QString name) {
    QFile file(name);
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
    p.save(name, "jpg");
}
