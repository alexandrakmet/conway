#include "patterns.h"
#include "ui_patterns.h"
#include <vector>
#include <QDebug>

Patterns::Patterns(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Patterns)
{
    ui->setupUi(this);
    std::vector<QToolButton*> toolButtons={ui->toolButton, ui->toolButton_2, ui->toolButton_3, ui->toolButton_4, ui->toolButton_5, ui->toolButton_6, ui->toolButton_7,
                                 ui->toolButton_8, ui->toolButton_9, ui->toolButton_10, ui->toolButton_11, ui->toolButton_12};

    QPixmap p;

    for (int i=0;i<toolButtons.size();i++) {
        QString s = QString::fromUtf8( "C:\\Users\\Alexandra\\Documents\\QT\\GOL\\image\\");
        s.append(QString::number(i+1));
        p.load(s);
        p.scaled(115,115, Qt::AspectRatioMode(), Qt::TransformationMode());
        toolButtons[i]->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButtons[i]->setIcon(QIcon(p));
        toolButtons[i]->setIconSize(QSize(115, 115));
        connect(toolButtons[i], SIGNAL(clicked()),this, SLOT(choice()));
    }
}


Patterns::~Patterns()
{
    delete ui;
}

void Patterns::mousePressEvent(QMouseEvent *e)
{

}

void Patterns::choice()
{
     QToolButton* buttonSender = qobject_cast<QToolButton*>(sender());
     QString k = buttonSender->text();
     qDebug()<<k;
    close();
}

