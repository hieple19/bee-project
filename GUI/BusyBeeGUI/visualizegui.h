#ifndef VISUALIZEGUI_H
#define VISUALIZEGUI_H

#include <QWidget>
#include "../../Engine/BusyBeeEngine/busybeeengine.h"
#include "../../Engine/BusyBeeEngine/runhistory.h"
#include "../../Engine/BusyBeeEngine/hive.h"
#include "../../Engine/Configuration/configuration.h"
#include <QDateTime>

namespace Ui {
class VisualizeGUI;
}

class VisualizeGUI : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizeGUI(QWidget *parent = nullptr);
    VisualizeGUI(BusyBeeEngine* engine , int run_index, QWidget *parent = nullptr);
    ~VisualizeGUI();

    void plot(int hive_index);
    std::vector<int>* get_alerts(){return hive_alert_index; }
private slots:
    void on_back_button_clicked();
    void PlotRangeChanged();

    void on_hive_list_currentRowChanged(int currentRow);

    void on_About_button_clicked();

private:
    Ui::VisualizeGUI *ui;

    BusyBeeEngine* engine;
    int nb_hives;
    Run* run;


    //data containers
    std::vector<Hive*>* hives;
    std::vector<QVector<double>*>* xContainers;
    std::vector<QVector<double>*>* yContainers;
    void load_data();

    //alerts
    std::vector<int>* hive_alert_index;

    //axis range
    double minX;
    double maxX;
    double minY;
    double maxY;

};

#endif // VISUALIZEGUI_H
