#include "setting.h"
#include "ui_form.h"

SettingPane::SettingPane(QWidget *parent) :
    parent(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

SettingPane::~SettingPane()
{
    delete ui;
}


