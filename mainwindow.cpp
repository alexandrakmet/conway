#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentColor(QColor("#000")),
    game(new GameWidget(this))
{
    ui->setupUi(this);

    QPixmap icon(16, 16);
    icon.fill(currentColor);
    ui->colorButton->setIcon( QIcon(icon) );

    const int RULE_SET_LENGTH = 12;
    ruleSetName = new QString[RULE_SET_LENGTH + 1]{"Life", "Replicator",
            "Seeds", "B25/S4", "Inkspot", "34Life",
            "Diamoeba", "2x2", "HighLife", "Day&Night",
            "Morley", "Anneal", "Custom"};
    ruleSetBor = new QString[RULE_SET_LENGTH]{"3", "1;3;5;7", "2", "2;5",
            "3", "3;4", "3;5;6;7;8", "3;6",
            "3;6", "3;6;7;8", "3;6;8", "4;6;7;8"};
    ruleSetSur = new QString[RULE_SET_LENGTH]{"2;3", "1;3;5;7", "", "4",
            "0;1;2;3;4;5;6;7;8", "3;4", "5;6;7;8", "1;2;5",
            "2;3", "3;4;6;7;8", "2;4;5", "3;5;6;7;8"};
    for (int i = 0; i < RULE_SET_LENGTH + 1; i++) {
        ui->comboRules->addItem(ruleSetName[i]);
    }

    connect(ui->startButton, SIGNAL(clicked()), game,SLOT(startGame()));
    connect(ui->stopButton, SIGNAL(clicked()), game,SLOT(stopGame()));
    connect(ui->clearButton, SIGNAL(clicked()), game,SLOT(clear()));
    connect(ui->randButton, SIGNAL(clicked()), game,SLOT(random()));
    connect(ui->iterInterval, SIGNAL(valueChanged(int)), game, SLOT(setInterval(int)));
    connect(ui->cellsControl, SIGNAL(valueChanged(int)), game, SLOT(setCellNumber(int)));
    connect(ui->stepButton,SIGNAL(clicked()), game,SLOT(newGeneration()));
    connect(game,SIGNAL(environmentChanged(bool)),ui->cellsControl,SLOT(setDisabled(bool)));
    connect(game,SIGNAL(gameEnds(bool)),ui->cellsControl,SLOT(setEnabled(bool)));
    connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(selectMasterColor()));

    connect(ui->comboRules, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboboxChanged()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadGame()));

    ui->mainLayout->setStretchFactor(ui->gameLayout, 8);
    ui->mainLayout->setStretchFactor(ui->setLayout, 2);
    ui->gameLayout->addWidget(game);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onComboboxChanged() {
    if (ui->comboRules->currentIndex() != ui->comboRules->count() - 1) {
        ui->labelSurv->setText(ruleSetSur[ui->comboRules->currentIndex()]);
        ui->labelBorn->setText(ruleSetBor[ui->comboRules->currentIndex()]);
    }
    bool* sur = new bool[9];
    bool* bor = new bool[9];
    for (int i = 0; i < 9; i ++) {
        sur[i] = bor[i] = false;
    }
    QStringList surList = ruleSetSur[ui->comboRules->currentIndex()].split(';');
    for (int i = 0; i < surList.size(); i++) {
        sur[surList.at(i).toInt()] = true;
    }
    QStringList borList = ruleSetBor[ui->comboRules->currentIndex()].split(';');
    qDebug()<<ruleSetBor[ui->comboRules->currentIndex()];
    for (int i = 0; i < borList.size(); i++) {
        bor[borList.at(i).toInt()] = true;
    }
    game->setRule(sur, bor);

}

void MainWindow::saveGame()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save current game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game *.life Files (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QString s = QString::number(game->cellNumber())+"\n";
    file.write(s.toUtf8());
    file.write(game->dump().toUtf8());
    QColor color = game->masterColor();
    QString buf = QString::number(color.red())+" "+
                  QString::number(color.green())+" "+
                  QString::number(color.blue())+"\n";
    file.write(buf.toUtf8());
    buf.clear();
    buf = QString::number(ui->iterInterval->value())+"\n";
    file.write(buf.toUtf8());
    file.close();
}

void MainWindow::loadGame()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open saved game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game Of Life File (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    int sv;
    in >> sv;
    ui->cellsControl->setValue(sv);

    game->setCellNumber(sv);
    QString dump="";
    for(int k=0; k != sv; k++) {
        QString t;
        in >> t;
        dump.append(t+"\n");
    }
    game->setDump(dump);

    int r,g,b; // RGB color
    in >> r >> g >> b;
    currentColor = QColor(r,g,b);
    game->setMasterColor(currentColor); // sets color of the dots
    QPixmap icon(16, 16); // icon on the button
    icon.fill(currentColor); // fill with new color
    ui->colorButton->setIcon( QIcon(icon) ); // set icon for button
    in >> r; // r will be interval number
    ui->iterInterval->setValue(r);
    game->setInterval(r);
}

void MainWindow::selectMasterColor()
{
    QColor color = QColorDialog::getColor(currentColor, this, tr("Select color of figures"));
    if(!color.isValid())
        return;
    currentColor = color;
    game->setMasterColor(color);
    QPixmap icon(16, 16);
    icon.fill(color);
    ui->colorButton->setIcon( QIcon(icon) );
}


