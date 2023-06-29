#include "datadisplayer.h"
#include "ui_datadisplayer.h"

///
/// \brief DataDisplayer::DataDisplayer
/// \param parent QWidget type window
///Constructor of data display creating simple elements of graph
DataDisplayer::DataDisplayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataDisplayer)
{
    ui->setupUi(this);
    menuBar = new QMenuBar(this);

    // Tworzenie MenuBox
    mainLayout = new QVBoxLayout(this);

    // Tworzenie osi X i Y
    axisX = new QtCharts::QValueAxis();
    axisY = new QtCharts::QValueAxis();

    // Tworzenie serii i wykresu
    series = new QtCharts::QLineSeries();
    chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // Tworzenie widoku wykresu
    chartView = new QtCharts::QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Ustawianie szerokości MenuBar
    int menuBarWidth = 35; // Ustaw preferowaną szerokość MenuBar
    menuBar->setFixedWidth(menuBarWidth); // Można również użyć setMinimumWidth()

    // Dodawanie widgetów do układu
    mainLayout->addWidget(menuBar);
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);

    // Dodawanie akcji do menu
    fileMenu = menuBar->addMenu("File");
    saveAction = fileMenu->addAction("Save to clipboard");
    connect(saveAction, &QAction::triggered, this, &DataDisplayer::save_to_clipboard);

    // Przypisywanie osi serii
    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

///
/// \brief DataDisplayer::~DataDisplayer
///Destructor of data display window
DataDisplayer::~DataDisplayer()
{
    delete ui;
    delete series;
    delete chart;
    delete chartView;
    delete layout;
    delete axisX;
    delete axisY;
    delete menuBar;
    delete mainLayout;
    delete graphicsView;
    delete scene;
    delete fileMenu;
    delete saveAction;
    qDebug() << "Displayer has been deleted";
}

///
/// \brief DataDisplayer::display_data
/// \param buffer Buffer with data to display
/// \return Status of display function problem with working
///
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
                int value;
                int j = 0;
                stream >> value;
                int max = value;
                int min = value;
                series->append(j, value);
                qDebug() << "Value: " << value << "at: " << j;
                while (!stream.atEnd())
                {
                    j++;
                    stream >> value;
                    if(value >= max)
                    {
                        max = value;
                    }
                    if(min >= value)
                    {
                        min = value;
                    }
                    series->append(j, value);
                    qDebug() << "Value: " << value << "at: " << j;
                }
                // Ustawianie wartości granicznych na osiach
                axisX->setRange(0, j);  // Zakres osi X
                axisY->setRange(min, max);   // Zakres osi Y
                chart->removeSeries(series);
                series->setName(buffer.get_name());
                chart->addSeries(series);
                show();
            }
            else if(buffer.get_type() == "Message")
            {
                series->clear();
                QString stringData = QString::fromUtf8(textData[i]);
                QMessageBox::information(this, "Message", stringData);
            }
            //more data types
        }
     } else qDebug() << "Data can't be displayed.";
        return 0;
    qDebug() << "No data to display";
    buffer.clear();
    return 0;
}

///
/// \brief DataDisplayer::set_parameters
/// \param line_type Line type
/// \param color Line color
/// \param line_size Line size
/// \param legend Status of legend required
/// Stes distplay parameters
///
void DataDisplayer::set_parameters(QString line_type, QString color, QString line_size, bool legend)
{
    QPen pen;
    pen.setWidth(line_size.toInt());
    // Ustawianie rodzaju linii
    if(line_type == "solid")
    {
        pen.setStyle(Qt::SolidLine);
    }
    else if(line_type == "dash")
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(line_type == "dot")
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(line_type == "dash-dot")
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(line_type == "dash-dot-dot")
    {
        pen.setStyle(Qt::DashDotDotLine);
    }

    // Ustawianie koloru linii
    if(color == "red")
    {
        pen.setColor(Qt::red);
    }
    else if(color == "blue")
    {
        pen.setColor(Qt::blue);
    }
    else if(color == "yellow")
    {
        pen.setColor(Qt::yellow);
    }
    else if(color == "green")
    {
        pen.setColor(Qt::green);
    }
    else if(color == "black")
    {
        pen.setColor(Qt::black);
    }
    else if(color == "cyan")
    {
        pen.setColor(Qt::cyan);
    }
    else if(color == "magenta")
    {
        pen.setColor(Qt::magenta);
    }

    // Ustawianie pióra dla serii
    series->setPen(pen);

    // Ustawianie widoczności legendy
    chart->legend()->setVisible(legend);
}

///
/// \brief DataDisplayer::save_to_clipboard
///Saves data to system clipboard
void DataDisplayer::save_to_clipboard()
{
    QPixmap pixmap = this->grab();
    if (!pixmap.isNull())
    {
        QApplication::clipboard()->setPixmap(pixmap); // Zapisz pixmap do schowka

        qDebug() << "Widget has been saved to clipboard";
    }
    else
    {
        qDebug() << "Failed to grab the widget";
    }
}
