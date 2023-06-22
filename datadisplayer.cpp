#include "datadisplayer.h"
#include "ui_datadisplayer.h"

DataDisplayer::DataDisplayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataDisplayer)
{
    ui->setupUi(this);
    series = new QtCharts::QLineSeries();
    chart = new QtCharts::QChart();
    chartView = new QtCharts::QChartView(chart, this);

    // Ustawienia wykresu
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->legend()->hide();

    // Ustawienia widoku wykresu
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
    show();
}

DataDisplayer::~DataDisplayer()
{
    delete ui;
    delete series;
    delete chart;
    delete chartView;
    delete layout;
    qDebug() << "Displayer has been deleted";
}

bool DataDisplayer::display_data(DataBuffer &buffer)
{
    if(buffer.read_data().size() != 0)
    {
        QList<QByteArray> data = buffer.read_data();
        QList<QByteArray> textData;
        for(int i = 0; i < data.size(); i++)
        {
            textData.append(QByteArray::fromHex(data[i]));
            qDebug() << "textData = " << textData;
            if(buffer.get_type() == "Random")
            {
                series->clear();
                QDataStream stream(textData[i]);
                stream.setByteOrder(QDataStream::BigEndian); // Jeśli dane są w formacie Big Endian
                int value = 0;
                int j = 0;
                while (!stream.atEnd())
                {
                    stream >> value;
                    series->append(j, value);
                    qDebug() << "Value: " << value << "at: " << j;
                    j++;
                }
                chart->removeSeries(series);
                series->setName(buffer.get_name());
                chart->addSeries(series);
            }
            else if(buffer.get_type() == "Message")
            {
//                series->clear();
//                QString stringData = QString::fromUtf8(textData[i]);
//                QMessageBox::information(this, "Message", stringData);

            }
            //kolejne konwersje typów danych
        }
     } else qDebug() << "Data can't be displayed.";
        return 0;
    qDebug() << "No data to display";
    buffer.clear();
    return 0;
}
