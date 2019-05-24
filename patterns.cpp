#include "patterns.h"
#include "ui_patterns.h"
#include <QPainter>

Patterns::Patterns(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Patterns)
{
    ui->setupUi(this);
    QPainter p(this);
    paintUniverse(p);
}

Patterns::~Patterns()
{
    delete ui;
}

void Patterns::paintUniverse( QPainter &p)
{

    double cellWidth = (double)ui->frame->width()/10;
    double cellHeight = (double)ui->frame->height()/10;
    // if there is any sense to paint it
                qreal left = (qreal)(cellWidth); // margin from left
                qreal top  = (qreal)(cellHeight); // margin from top
                QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
                p.fillRect(r, QBrush("red")); // fill cell with brush of main color

            }

