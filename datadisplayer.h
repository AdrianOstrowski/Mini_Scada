#ifndef DATADISPLAYER_H
#define DATADISPLAYER_H

#include <QWidget>
#include "databuffer.h"
#include <qdatastream.h>
#include <QLabel>
#include <QVBoxLayout>
#include <QChart>
#include <QLineSeries>
#include <QtCharts/QChartView>
#include <QMessageBox>

namespace Ui {
class DataDisplayer;
}

class DataDisplayer : public QWidget
{
    Q_OBJECT

public:
    explicit DataDisplayer(QWidget *parent = nullptr);
    ~DataDisplayer();
    bool display_data(DataBuffer&);
private:
    Ui::DataDisplayer *ui;
    QtCharts::QChartView *chartView;
    QtCharts::QLineSeries *series;
    QtCharts::QChart *chart;
    QVBoxLayout *layout;
};

#endif // DATADISPLAYER_H
