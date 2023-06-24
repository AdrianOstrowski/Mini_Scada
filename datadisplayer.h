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
#include <QValueAxis>
#include <qbrush.h>
#include <QMenuBar>
#include <QClipboard>
#include <QPixmap>

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
    void set_parameters(QString, QString, QString, bool);

private:
    Ui::DataDisplayer *ui;
    QtCharts::QChartView *chartView;
    QtCharts::QLineSeries *series;
    QtCharts::QChart *chart;
    QVBoxLayout *layout;
    QtCharts::QValueAxis *axisX;
    QtCharts::QValueAxis *axisY;
    QMenuBar *menuBar;
    QVBoxLayout *mainLayout;
    QHBoxLayout *rightLayout;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QMenu *fileMenu;
    QAction *saveAction;

public slots:
    void save_to_clipboard();
};

#endif // DATADISPLAYER_H
