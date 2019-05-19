#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    ui->ok_button->setStyleSheet("border-image:url(:/images/images/check.png);");
}

About::~About()
{
    delete ui;
}
