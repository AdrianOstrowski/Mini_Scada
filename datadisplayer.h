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

class DataDisplayer : public QDialog
{
    Q_OBJECT

public:
    explicit DataDisplayer(QWidget *parent = nullptr);
    ~DataDisplayer();
    bool display_data(DataBuffer&);
    void set_parameters(QString, QString, QString, bool);

private:
    ///
    /// \brief ui
    ///Ui class
    Ui::DataDisplayer *ui;
    ///
    /// \brief chartView
    ///Part of chart to display
    QtCharts::QChartView *chartView;
    ///
    /// \brief series
    ///Data series to display
    QtCharts::QLineSeries *series;
    ///
    /// \brief chart
    ///Chart cass object
    QtCharts::QChart *chart;
    ///
    /// \brief axisX
    ///X axi object
    QtCharts::QValueAxis *axisX;
    ///
    /// \brief axisY
    ///Y axi object
    QtCharts::QValueAxis *axisY;
    ///
    /// \brief menuBar
    ///Menubar of display window
    QMenuBar *menuBar;
    ///
    /// \brief mainLayout
    ///Layout object
    QVBoxLayout *mainLayout;
    ///
    /// \brief graphicsView
    ///Graph viev object
    QGraphicsView *graphicsView;
    ///
    /// \brief scene
    ///Graph scene object
    QGraphicsScene *scene;
    ///
    /// \brief fileMenu
    ///Element of menubar
    QMenu *fileMenu;
    ///
    /// \brief saveAction
    ///Element of menubar
    QAction *saveAction;

public slots:
    void save_to_clipboard();
    void closed_window();

signals:
    void closed();
};

#endif // DATADISPLAYER_H
