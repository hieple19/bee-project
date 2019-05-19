#include "busybeegui.h"
#include "ui_busybeegui.h"
#include <QComboBox>

/** @brief constructor for main menu GUI. it initilizes the window and variables*/
BusyBeeGUI::BusyBeeGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BusyBeeGUI)
{
    ui->setupUi(this);

    //limit window management
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setFixedSize(this->size());


    //initialize buttons visibility
    ui->GenerateButton->setVisible(true);
    ui->AnalyzeButton->setVisible(false);
    ui->default_button->setVisible(true);
    ui->random_button->setVisible(true);

    //initialize frames visibility
    ui->External_conditions_frame->setVisible(true);
    ui->hive_information_frame->setVisible(true);
    ui->models_list->setVisible(false);

    //initilize label visibility
    ui->hive_information_label->setVisible(true);

    //init default values temperature
    ui->temperature_label->setText("60° Fahrenheit");
    ui->temperature_slider->setRange(-20,120);
    ui->temperature_slider->setValue(60);

    //init default values hive size
    ui->colony_size_spinbox->setRange(10000,70000);
    ui->colony_size_label->setText("Bees");
    ui->colony_size_slider->setRange(10000,70000);
    location= "";

    //init config buttons
    set_default_config();

    //randomizer
    srand (time(nullptr));

    //load info from db
    config = new Configuration();
    external_cond = new ExternalConditions();
    engine = new BusyBeeEngine(config);
    engine->load_run_history();
    //load nb of runs to gui
    ui->models_count->setText(QString::number(engine->get_history()->get_nb_runs()));

    //set list style
    ui->models_list->setStyleSheet("font: 16pt Serif");
    swarm=0;
    const_pop=0;
}


BusyBeeGUI::~BusyBeeGUI()
{
    delete ui;
    delete engine;
}

/** @brief Updates UI style when Visualize Model Button is clicked */
void BusyBeeGUI::on_VisualizeModel_clicked()
{
    ui->GenerateModel->setStyleSheet("position: absolute;\nleft: 0%;\nright: 0%;\ntop: 0%;\nbottom: 0%;\n\nbackground: #3E5265;\n\n/* Generate Model */\n\nposition: absolute;\nwidth: 509px;\nheight: 76px;\nleft: 138px;\ntop: 24px;\nfont: 400 20pt \"Bitstream Vera Sans Serif\";\n\ncolor: #FFFFFF;");
    ui->VisualizeModel->setStyleSheet("background: #1ABC9C;\n\n/* Visualize */\n\nposition: absolute;\nwidth: 509px;\nheight: 76px;\nleft: 138px;\ntop: 24px;\n\nfont: 400 20pt \"Bitstream Vera Sans Serif\";\n\ncolor: #FFFFFF;");
    ui->selected->move(600,340);
    ui->GenerateButton->setVisible(false);
    ui->AnalyzeButton->setVisible(true);
    ui->External_conditions_frame->setVisible(false);
    ui->external_conditions_label->setVisible(false);
    ui->hive_information_frame->setVisible(false);
    ui->hive_information_label->setVisible(false);
    ui->default_button->setVisible(false);
    ui->random_button->setVisible(false);
    ui->models_list->setVisible(true);
    ui->swarm_check_box->setVisible(false);
    ui->swarm_label->setVisible(false);
    ui->const_pop_check_box->setVisible(false);
    ui->const_pop_label->setVisible(false);

    //populate the list
    //std::cout << "nb of runs "<< engine->get_history()->get_nb_runs()<< std::endl;
    //std::cout << "nb rows "<< engine->get_history()->get_nb_runs()<< std::endl;
    if(ui->models_list->count()<engine->get_history()->get_nb_runs()){
        ui->models_list->clear();
        for (int i =1; i<=engine->get_history()->get_nb_runs();i++) {
            ui->models_list->addItem("Run " + QString::number(i));

        }
    }


}

/** @brief Updates UI style when Generate Model Button is clicked */
void BusyBeeGUI::on_GenerateModel_clicked()
{
    ui->GenerateModel->setStyleSheet("background: #1ABC9C;\n\n/* Visualize */\n\nposition: absolute;\nwidth: 509px;\nheight: 76px;\nleft: 138px;\ntop: 24px;\n\nfont: 400 20pt \"Bitstream Vera Sans Serif\";\n\ncolor: #FFFFFF;");
    ui->VisualizeModel->setStyleSheet("position: absolute;\nleft: 0%;\nright: 0%;\ntop: 0%;\nbottom: 0%;\n\nbackground: #3E5265;\n\n/* Visualize Model */\n\nposition: absolute;\nwidth: 509px;\nheight: 76px;\nleft: 138px;\ntop: 24px;\nfont: 400 20pt \"Bitstream Vera Sans Serif\";\n\ncolor: #FFFFFF;");
    ui->selected->move(0,340);
    ui->GenerateButton->setVisible(true);
    ui->AnalyzeButton->setVisible(false);
    ui->External_conditions_frame->setVisible(true);
    ui->external_conditions_label->setVisible(true);
    ui->hive_information_frame->setVisible(true);
    ui->hive_information_label->setVisible(true);
    ui->default_button->setVisible(true);
    ui->random_button->setVisible(true);
    ui->swarm_check_box->setVisible(true);
    ui->swarm_label->setVisible(true);
    ui->const_pop_check_box->setVisible(true);
    ui->const_pop_label->setVisible(true);

    ui->models_list->setVisible(false);
    ui->models_list->clear();
}

/** @brief  calls the back end engine to create simulations and add it to the database*/
void BusyBeeGUI::on_GenerateButton_clicked()
{
    try {

        if(location == ""){
            throw 1;
        }else {
            //            if(config!= nullptr) delete config;
            //            if(external_cond!= nullptr)  delete external_cond;
            external_cond = new ExternalConditions(temperature,ExternalConditions::Season(ui->season_combo->currentIndex()), ExternalConditions::Weather(ui->weather_combo->currentIndex()));
            config = new Configuration(nb_hives, colony_size, location);
            config->set_swarm_mode(swarm);
            config->set_constant_pop(const_pop);

            //create model
            engine->set_config(config);
            engine->set_conditions(external_cond);
            engine->make_new_run();
            engine->simulate();
            engine->save_run();

            //update model count
            ui->models_count->setText(QString::number(engine->get_history()->get_nb_runs()));
            //success
            QMessageBox::information(this,tr("Model Generation Complete"),tr("Model Successfully Generated."));
        }

    } catch ( int x ) {
        //
        if(x==1){
            QMessageBox::critical(this,tr("Error"),tr("Type a Location"));
        }else{
            QMessageBox::critical(this,tr("Error"),tr("Error Creating The Model."));
        }
    }
}


/** @brief creates and about the software message */
void BusyBeeGUI::on_About_button_clicked()
{
    QMessageBox::information(this,tr("About BusyBee"),tr("BusyBee is a software created by BeeRex for the Software Engineering class in Lafayette College.\n Authors: Slim Ghodhbane, Ian Bowe, Lucy Shin, and Hiep Le."));
}

/** @brief updates temperature when temperature slider value is changes
 *  @param value - new value */
void BusyBeeGUI::on_temperature_slider_valueChanged(int value)
{
    QString v =QString::number(value) + "° Fahrenheit";
    ui->temperature_label->setText(v);
    temperature = value;
}

/** @brief updates season when season combo box value is changes
 *  @param index - index of new season */
void BusyBeeGUI::on_season_combo_currentIndexChanged(int index)
{
    ui->season_combo->clearFocus();
    external_cond->setSeason(index);
}

/** @brief restore parameters to default*/
void BusyBeeGUI::on_default_button_clicked()
{
    set_default_config();
}

void BusyBeeGUI::set_default_config(){
    ui->season_combo->setCurrentIndex(0);

    ui->weather_combo->blockSignals(true);
    ui->weather_combo->setCurrentIndex(1);
    ui->weather_combo->blockSignals(false);

    ui->temperature_slider->setValue(60);
    ui->nb_hives_spinbox->setValue(1);
    ui->colony_size_slider->setValue(20000);

    //external_cond->setSeason(0);
    //external_cond->setWeather(1);
    temperature = 60;
    nb_hives = 1;
    colony_size = 20000;
    location = "";
}

/** @brief load random parameters to the variables*/
void BusyBeeGUI::on_random_button_clicked()
{
    set_random_config();
}

void BusyBeeGUI::set_random_config(){
    int season =rand()%4;
    int weather =rand()%4;
    int temp = (rand()%141) - 20;
    int nb_h = rand() % 10 +1;
    int col_s = (rand()%60001) +10000;
    ui->season_combo->blockSignals(true);
    ui->season_combo->setCurrentIndex(season);
    ui->season_combo->blockSignals(false);

    ui->weather_combo->blockSignals(true);
    ui->weather_combo->setCurrentIndex(weather);
    ui->weather_combo->blockSignals(false);

    ui->temperature_slider->setValue(temp);
    ui->nb_hives_spinbox->setValue(nb_h);
    ui->colony_size_slider->setValue(col_s);

    external_cond->setSeason(season);
    external_cond->setWeather(weather);
    temperature = temp;
    nb_hives = nb_h;
    colony_size = col_s;

}

/** @brief updates weather when weather box value is changed
 *  @param index - index of new weather */
void BusyBeeGUI::on_weather_combo_currentIndexChanged(int index)
{
    external_cond->setWeather(index);
}

/** @brief updates colony size when colony size slider value is changed
 *  @param value - new colony size value */
void BusyBeeGUI::on_colony_size_slider_valueChanged(int value)
{
    ui->colony_size_spinbox->setValue(value);
    colony_size = value;
}

/** @brief updates colony size when spin box value is changed
 *  @param value - new colony size value */
void BusyBeeGUI::on_colony_size_spinbox_valueChanged(int arg1)
{
    ui->colony_size_slider->setValue(arg1);
    colony_size = arg1;
}

void BusyBeeGUI::on_AnalyzeButton_clicked()
{
    //Qt::WindowFlags flags = windowFlags();
    //setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    if( ui->models_list->currentRow() <0){
        QMessageBox::critical(this,tr("Error"),tr("Please Select a Run"));
    }else{
        visualize_gui = new VisualizeGUI(engine,ui->models_list->currentRow(), nullptr);
        visualize_gui->setWindowModality(Qt::ApplicationModal);
        visualize_gui->show();
        if(visualize_gui->get_alerts()->size()>0){
            for (int i = 1; i<=visualize_gui->get_alerts()->size();i++) {
                char alert[100];
                strcpy(alert,"Potential Swarm Detected in Hive ");
                strcat(alert, std::to_string(i).c_str());
                QMessageBox::critical(this,tr("Error"),tr(alert));
            }
        }
    }

}

void BusyBeeGUI::on_location_label_textEdited(const QString &arg1)
{
    location = arg1.toStdString();
}

void BusyBeeGUI::on_nb_hives_spinbox_valueChanged(int arg1)
{
    nb_hives = arg1;
}

void BusyBeeGUI::on_swarm_check_box_stateChanged(int arg1)
{
    if(arg1==0){
        swarm=0;
    }else{
        swarm = 1;
    }
}

void BusyBeeGUI::on_const_pop_check_box_stateChanged(int arg1)
{
    if(arg1==0){
        const_pop=0;
        std::cout << "CFalse" << std::endl;
    }else{
        const_pop = 1;
        std::cout << "CTrue" << std::endl;

    }
}
