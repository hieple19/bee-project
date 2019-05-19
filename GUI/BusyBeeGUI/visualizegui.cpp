#include "visualizegui.h"
#include "ui_visualizegui.h"


VisualizeGUI::VisualizeGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualizeGUI)
{
    ui->setupUi(this);

    //set title
    QWidget::setWindowTitle("Model Visualizer");
    //limit window management
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setFixedSize(this->size());

    plot(0);

}

VisualizeGUI::VisualizeGUI(BusyBeeEngine* engine, int row_index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualizeGUI)
{
    ui->setupUi(this);

    //set title
    QWidget::setWindowTitle("Model Visualizer");
    //limit window management
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setFixedSize(this->size());

    //inti data
    //engine->load_run_history();

    run = engine->get_history()->get_run(row_index);
    hives = run->get_hives_list();
    nb_hives = run->get_num_hives();

    //data containers
    xContainers = new std::vector<QVector<double>*>();
    yContainers = new std::vector<QVector<double>*>();

    //initial alert detector
    hive_alert_index = new std::vector<int>();
    //load all the data
    load_data();



    //update hive list
    ui->hive_list->setStyleSheet("font: 16pt Serif");
    for (int i = 1;i<=nb_hives;i++) {
        ui->hive_list->addItem("Hive "+ QString::number(i));
    }


    //draw first hive
    ui->hive_list->setCurrentRow(0);
    //plot first hive
    plot(0);

}
VisualizeGUI::~VisualizeGUI()
{
    delete ui;
    delete xContainers;
    delete yContainers;

    SIGNAL(close());
}

void VisualizeGUI::on_back_button_clicked()
{

    this->close();


    delete this;

}

void VisualizeGUI::plot(int hive_index){
    // set some pens, brushes and backgrounds:
    ui->graph->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->graph->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->graph->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->graph->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->graph->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->graph->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->graph->xAxis->setTickLabelColor(Qt::white);
    ui->graph->yAxis->setTickLabelColor(Qt::white);
    ui->graph->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->graph->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->graph->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->graph->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->graph->xAxis->grid()->setSubGridVisible(true);
    ui->graph->yAxis->grid()->setSubGridVisible(true);
    ui->graph->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->graph->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->graph->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->graph->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->graph->setBackground(plotGradient);

    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 500);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->graph->axisRect()->setBackground(axisRectGradient);

    //set ranges;
    minX = 0;
    maxX =  60000;

    //set ranges;
    minY = 0;
    maxY = 60000;

    //set default scale
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:

    ui->graph->xAxis->setRange(minX,maxX);

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    ui->graph->xAxis->setTicker(dateTimeTicker);
    dateTimeTicker->setDateTimeFormat("hh:mm:ss \n ddd MMMM d");

    ui->graph->xAxis->setLabel("Time");
    ui->graph->xAxis->setLabelFont(QFont("Sans Serif",12, 10,true));
    ui->graph->xAxis->setLabelColor(QColor(255,255,255,255));
    ui->graph->yAxis->setRange(minY,maxY);
    ui->graph->yAxis->setLabel("Bee Count");
    ui->graph->yAxis->setLabelFont(QFont("Sans Serif",12, 10,true));
    ui->graph->yAxis->setLabelColor(QColor(255,255,255,255));


    //add graph
    ui->graph->clearGraphs();
    ui->graph->clearItems();
    ui->graph->clearPlottables();
    ui->graph->addGraph();
    ui->graph->graph(0)->setData(*xContainers->at(hive_index),*(yContainers->at(hive_index)));
    ui->graph->graph(0)->setPen(QPen(Qt::green)); // line color blue for first graph
    QPen pen = ui->graph->graph(0)->pen();
    pen.setWidth(10);
    ui->graph->graph(0)->setPen(ui->graph->graph(0)->pen());
    ui->graph->graph(0)->setBrush(QBrush(QColor(0, 255, 0, 20)));
    ui->graph->graph(0)->rescaleAxes();

    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );
    //connect(ui->graph, SIGNAL(beforeReplot()),this,SLOT(PlotRangeChanged()));

    ui->graph->replot();
    ui->graph->repaint();

}

void VisualizeGUI::load_data(){
    //create data;
    for(int i=0;i<nb_hives;i++){

       std::vector<PopulationHistory*>* pop_hist=  hives->at(i)->get_pop_history();
       //std::cout <<pop_hist->size()<<std::endl;
       QVector<double>* x= new QVector<double>();
       QVector<double>* y= new QVector<double>();
       //QVector<double> x(pop_hist->size()), y(pop_hist->size());

       //int offset = pop_hist->at(0)->time->getT();
       //std::cout<<offset<<std::endl;
       //std::cout<<hives->at(i)->getPop()<<std::endl;
       for (int j=0; j<pop_hist->size(); ++j)
       {
        //add time
        // x->push_back((pop_hist->at(j)->time->getT() - offset)/1000); // t in s
        //x->push_back(pop_hist->at(j)->time->getT());

         //create current date and set corresponding time
         QDateTime dt = QDateTime::currentDateTime();
         QTime time(pop_hist->at(j)->time->getTmp()->tm_hour,pop_hist->at(j)->time->getTmp()->tm_min,pop_hist->at(j)->time->getTmp()->tm_sec,pop_hist->at(j)->time->getMS());
         dt.setTime(time);
         //QDate d(pop_hist->at(j)->time->getTmp()->tm_year,pop_hist->at(j)->time->getTmp()->tm_mon, pop_hist->at(j)->time->getTmp()->tm_mday );
         //dt.setDate(d);

         //add time to x axis
         x->push_back(dt.toTime_t());


         //check for alerts
         if(pop_hist->at(j)->population < (hives->at(i)->get_original_pop()/2)){
             hive_alert_index->push_back(i);
             break;
         }

         y->push_back(pop_hist->at(j)->population);

       }

       xContainers->push_back(x);
       yContainers->push_back(y);
    }

}


void VisualizeGUI::PlotRangeChanged()
{
    if (ui->graph->xAxis->range().lower <= 0)
    {
          if (ui->graph->xAxis->range().upper <= maxX)
            ui->graph->xAxis->setRangeUpper(maxX);
      ui->graph->xAxis->setRangeLower(0);
    } else if (ui->graph->xAxis->range().upper <= maxX)
    {
      ui->graph->xAxis->setRangeUpper(maxX);
    }

    if (ui->graph->yAxis->range().lower <= 0)
    {

      ui->graph->yAxis->setRangeLower(0);
    }
}

void VisualizeGUI::on_hive_list_currentRowChanged(int currentRow)
{
    plot(currentRow);
}

void VisualizeGUI::on_About_button_clicked()
{
    QMessageBox::information(this,tr("About BusyBee"),tr("BusyBee is a software created by BeeRex for the Software Engineering class in Lafayette College.\n Authors: Slim Ghodhbane, Ian Bowe, Lucy Shin, and Hiep Le."));

}
