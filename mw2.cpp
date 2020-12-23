#include "mw2.h"
#include "ui_mw2.h"

mw2::mw2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mw2)
{
    ui->setupUi(this);
}

mw2::~mw2()
{
    delete ui;
}
