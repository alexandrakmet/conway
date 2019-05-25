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

void Patterns::setCurrentPattern(QString s)
{
    switch (s.toInt()) {
    case 0: current = new bool[225]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0,
                                    0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0,
                                    0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0,
                                    0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0,
                                    0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0,
                                    0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0,
                                    0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
        size=15;
        break;

    case 1: current = new bool[36]{0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 1, 0, 0,
                                    0, 1, 0, 0, 1, 0,
                                    0, 0, 1, 0, 1, 0,
                                    0, 0, 0, 1, 0, 0,
                                    0, 0, 0, 0, 0, 0 };
            size=6;
        break;

    case 2:  current = new bool[81]{0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 1, 1, 0, 1, 1, 0, 0,
                0, 0, 1, 1, 0, 1, 1, 0, 0,
                0, 0, 0, 1, 0, 1, 0, 0, 0,
                0, 1, 0, 1, 0, 1, 0, 1, 0,
                0, 1, 0, 1, 0, 1, 0, 1, 0,
                0, 1, 1, 0, 0, 0, 1, 1, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
        size=9;
        break;
    case 3: current = new bool[36]{0, 0, 0, 0, 0, 0,
                0, 0, 0, 1, 0, 0,
                0, 0, 0, 0, 1, 0,
                0, 0, 1, 1, 1, 0,
                0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0 };
       size=6;
       break;

    case 4:current = new bool[49]{0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 1, 1, 0,
                0, 0, 0, 0, 0, 1, 0,
                0, 0, 0, 0, 1, 0, 0,
                0, 1, 0, 1, 0, 0, 0,
                0, 1, 1, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0
    };
       size=7;
       break;

    case 5:current = new bool[36]{  0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 1, 0, 0,
                                    0, 1, 0, 0, 1, 0,
                                    0, 0, 1, 1, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0 };
        size=6;
        break;

    case 6:current = new bool[36]{  0, 0, 0, 0, 0, 0,
                                    0, 1, 1, 0, 0, 0,
                                    0, 1, 0, 0, 0, 0,
                                    0, 0, 0, 0, 1, 0,
                                    0, 0, 0, 1, 1, 0,
                                    0, 0, 0, 0, 0, 0 };
        size=6;
        break;

    case 7:current = new bool[196]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
        size=14;
        break;

    case 8:current = new bool[169]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0,
                0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
                0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0,
                0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0,
                0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0,
                0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
                0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
        size=13;
        break;

    case 9:current = new bool[36]{  0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 1, 0, 0,
                                    0, 0, 1, 0, 1, 0,
                                    0, 0, 0, 1, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0 };
        size=6;
        break;

    case 10:current = new bool[81]{0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 1, 1, 1, 1, 1, 1, 0, 0,
                0, 1, 0, 0, 0, 0, 0, 1, 0,
                0, 1, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 1, 0, 0, 0, 0, 1, 0,
                0, 0, 0, 0, 1, 1, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
};
        size = 9;
        break;

    case 11:current = new bool[49]{0, 0, 0, 0, 0, 0, 0,
                0, 1, 0, 0, 1, 0, 0,
                0, 0, 0, 0, 0, 1, 0,
                0, 1, 0, 0, 0, 1, 0,
                0, 0, 1, 1, 1, 1, 0,
                0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0
    };
        size=7;
        break;

    default: current=nullptr; size=0;
    }
    return;
}



void Patterns::choice()
{
     QToolButton* buttonSender = qobject_cast<QToolButton*>(sender());
     QString k = buttonSender->text();
     setCurrentPattern(k);
     close();

}

