#include "patterns.h"
#include "ui_patterns.h"

Patterns::Patterns(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Patterns)
{
    ui->setupUi(this);
}

Patterns::~Patterns()
{
    delete ui;
}
