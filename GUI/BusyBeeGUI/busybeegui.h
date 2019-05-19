#ifndef BUSYBEEGUI_H
#define BUSYBEEGUI_H

#include <QMainWindow>
#include<QIcon>
#include <QMessageBox>
#include <QPushButton>
#include <exception>
#include <iostream>
#include <QListWidget>

#include <random>
#include "../../Engine/ExternalConditions/ExternalConditions.h"


#include "visualizegui.h"


namespace Ui {
class BusyBeeGUI;
}

class BusyBeeGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit BusyBeeGUI(QWidget *parent = nullptr);
    ~BusyBeeGUI();



private slots:
    void on_VisualizeModel_clicked();

    void on_GenerateModel_clicked();

    void on_GenerateButton_clicked();

    void on_About_button_clicked();

    void on_temperature_slider_valueChanged(int value);


    void on_season_combo_currentIndexChanged(int index);

    void on_weather_combo_currentIndexChanged(int index);

    void on_colony_size_slider_valueChanged(int value);

    void on_default_button_clicked();

    void on_random_button_clicked();

    void on_colony_size_spinbox_valueChanged(int arg1);

    void on_AnalyzeButton_clicked();

    void on_location_label_textEdited(const QString &arg1);

    void on_nb_hives_spinbox_valueChanged(int arg1);

    void on_swarm_check_box_stateChanged(int arg1);

    void on_const_pop_check_box_stateChanged(int arg1);

private:
    Ui::BusyBeeGUI *ui;


    ExternalConditions* external_cond;
    int temperature;
    int nb_hives;
    int colony_size;
    std::string location;
    bool swarm;
    bool const_pop;

    VisualizeGUI* visualize_gui;

    //load visualing list variables
    //load database
    Configuration* config;
    BusyBeeEngine* engine;


    void set_default_config();
    void set_random_config();

};

#endif // BUSYBEEGUI_H
