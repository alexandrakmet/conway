#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QString>
#include <QPainter>
#include <QDebug>
#include <qmath.h>
#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    generations(-1),
    universeSize(50),
    PatternSelected(false)
{
    setMouseTracking(true);
    timer->setInterval(300);
    m_masterColor = "#005500";
    universe = new bool[(universeSize + 2) * (universeSize + 2)];
    next = new bool[(universeSize + 2) * (universeSize + 2)];
    generation = new int[(universeSize + 2) * (universeSize + 2)];
    rule.survive = new bool[9]; rule.born = new bool[9];

    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));

    memset(universe, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
    memset(next, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
    memset(rule.survive, false, sizeof(bool)*9);
    memset(rule.born, false, sizeof(bool)*9);
    rule.born[3] = true; rule.survive[2] = true; rule.survive[3] = true;
    memset(generation, 0, sizeof(int)*(universeSize + 2) * (universeSize + 2));
}

GameWidget::~GameWidget()
{
    delete [] universe;
    delete [] next;
}

void GameWidget::startGame(const int &number)
{
    generations = number;

    timer->start();
}

void GameWidget::stopGame()
{
    timer->stop();
}

void GameWidget::clear()
{
    memset(universe, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
    memset(next, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
    memset(generation, 0, sizeof(int)*(universeSize + 2) * (universeSize + 2));
    gameEnds(true);
    update();
}

void GameWidget::random(){
    clear();
    emit environmentChanged(true);
    for(int k = 1; k <= universeSize*universeSize/2; k++) {
         int x = g.bounded(universeSize);
         int y = g.bounded(universeSize);
         universe[y*universeSize+x]=true;
         generation[y*universeSize+x]=g.bounded(9);
        }
    update();
}


int GameWidget::cellNumber()
{
    return universeSize;
}

void GameWidget::setCellNumber(const int &s)
{
    universeSize = s;
    resetUniverse();
    update();
}

void GameWidget::resetUniverse()
{
    delete [] universe;
    delete [] next;
    universe = new bool[(universeSize + 2) * (universeSize + 2)];
    next = new bool[(universeSize + 2) * (universeSize + 2)];
    generation = new int[(universeSize + 2) * (universeSize + 2)];
    memset(universe, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
    memset(next, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
    memset(generation, 0, sizeof(int)*(universeSize + 2) * (universeSize + 2));

}

QString GameWidget::dump()
{
    char temp;
    QString master = "";
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            if(universe[k*universeSize + j] == true) {
                temp = '*';
            } else {
                temp = 'o';
            }
            master.append(temp);
            (generation[k*universeSize + j] != -1 && generation[k*universeSize + j]<10)? master.append(QString::number(generation[k*universeSize + j])):master.append(QString::number(9));
        }
        master.append("\n");
    }
    return master;
}

void GameWidget::setDump(const QString &data)
{
    int current = 0;
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            universe[k*universeSize + j] = data[current] == '*';
            current++;
            QString g = data[current];
            generation[k*universeSize + j]=g.toInt();
            current++;
        }
        current++;
    }

    update();
}

void GameWidget::setRule(bool *s, bool *b)
{
    clear();
    rule.survive=s;
    rule.born=b;

}

int GameWidget::interval()
{
    return timer->interval();
}

void GameWidget::setInterval(int msec)
{
    timer->setInterval(msec);
}

bool GameWidget::isAlive(int k, int j)
{
    int power = 0;
    power += universe[(k+1)*universeSize +  j];
    power += universe[(k-1)*universeSize + j];
    power += universe[k*universeSize + (j+1)];
    power += universe[k*universeSize + (j-1)];
    power += universe[(k+1)*universeSize + ( j-1)];
    power += universe[(k-1)*universeSize + (j+1)];
    power += universe[(k-1)*universeSize + (j-1)];
    power += universe[(k+1)*universeSize +  (j+1)];
    if ((universe[k*universeSize + j] == true) && rule.survive[power]){
        generation[k*universeSize + j]++;
        return true;
    }
    if(universe[k*universeSize + j] == false && rule.born[power]) return true;
    generation[k*universeSize + j]=0;
    return false;
}

void GameWidget::newGeneration()
{
    if(generations < 0)
        generations++;
    int notChanged=0;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            next[k*universeSize + j] = isAlive(k, j);
            if(next[k*universeSize + j] == universe[k*universeSize + j])
                notChanged++;
        }
    }
    if(notChanged == universeSize*universeSize) {
        QMessageBox::information(this,
                                 tr("Game lost sense"),
                                 tr("The End. Now game finished because all the next generations will be the same."),
                                 QMessageBox::Ok);
        stopGame();
        gameEnds(true);
        return;
    }
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            universe[k*universeSize + j] = next[k*universeSize + j];
        }
    }
    update();
    generations--;
    if(generations == 0) {
        stopGame();
        gameEnds(true);
        QMessageBox::information(this,
                                 tr("Game finished."),
                                 tr("Iterations finished."),
                                 QMessageBox::Ok,
                                 QMessageBox::Cancel);
    }
}


void GameWidget::patternSelected(bool *p, int s)
{
    PatternSelected = (p != nullptr && s <= universeSize);
   if(PatternSelected){
       pattern = p;
       patternSize = s;
   }
}

bool GameWidget::getPatternSelected() const
{
    return PatternSelected;
}

bool GameWidget::timerState()
{
    return timer->isActive();
}

int *GameWidget::getGeneration() const
{
    return generation;
}

bool *GameWidget::getUniverse() const
{
    return universe;
}



QColor GameWidget::getMasterColor() const
{
    return m_masterColor;
}

int GameWidget::getGenerations() const
{
    return generations;
}

int GameWidget::getUniverseSize() const
{
    return universeSize;
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintUniverse(p);
    paintGrid(p);

}

bool mousePressed=false;
bool wasMoved = false;
void GameWidget::mousePressEvent(QMouseEvent *e)
{
    emit environmentChanged(true);
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    int k = floor(e->y()/cellHeight) + 1;
    int j = floor(e->x()/cellWidth) + 1;
    if(PatternSelected){
        for(int x = 0; x < patternSize; x++){
            for(int y = 0; y < patternSize; y++){
                if((k + y) < universeSize+2) {
                    PatternSelected = false;
                    universe[(k + y)*universeSize + j + x] = pattern[y*patternSize + x];
                    generation[(k + y)*universeSize + j + x] = 0;
                    wasMoved = false;
                }
            }
        }
    } else {
        universe[k*universeSize + j] = !universe[k*universeSize + j];
        mousePressed = true;
    }
    update();
}

int prevK, prevJ; int* prevGener; bool* prevUniv;
void GameWidget::mouseMoveEvent(QMouseEvent *e)
{

    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    int k = floor(e->y()/cellHeight) + 1;
    int j = floor(e->x()/cellWidth) + 1;
    int currentLocation = k*universeSize + j;
    if(mousePressed){
        if(!universe[currentLocation]){                //if current cell is empty,fill in it
            universe [currentLocation]= !universe[currentLocation];
            update();
        }
    }
    else if(PatternSelected) {
        if(wasMoved){
            for(int x = 0; x < patternSize; x++){
                for(int y = 0; y < patternSize; y++){
                    if((prevK + y) < universeSize+2) {
                        universe[(prevK + y)*universeSize + prevJ + x] = prevUniv[y*patternSize + x];
                        generation[(prevK + y)*universeSize + prevJ + x] = prevGener[y*patternSize + x];
                }
            }
        }
        }
        wasMoved = true;
        prevGener = new int[patternSize*patternSize];
        prevUniv = new bool[patternSize*patternSize];
        prevK = k; prevJ = j;
        for(int x = 0; x < patternSize; x++){
            for(int y = 0; y < patternSize; y++){
                if((k + y) < universeSize+2) {
                    prevUniv[y*patternSize + x] = universe[(k + y)*universeSize + j + x];
                    prevGener[y*patternSize + x] = generation[(k + y)*universeSize + j + x];
                    universe[(k + y)*universeSize + j + x] = pattern[y*patternSize + x];
                    generation[(k + y)*universeSize + j + x] = -1;
                }
            }
         }
        update();

    }
}


void GameWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mousePressed=false;
}

void GameWidget::paintGrid(QPainter &p)
{
    QRect borders(0, 0, width()-1, height()-1); // borders of the universe
    QColor gridColor = "black"; // color of the grid
    gridColor.setAlpha(10); // must be lighter than main color
    p.setPen(gridColor);
    double cellWidth = (double)width()/universeSize; // width of the widget / number of cells at one row
    for(double k = cellWidth; k <= width(); k += cellWidth)
        p.drawLine(k, 0, k, height());
    double cellHeight = (double)height()/universeSize; // height of the widget / number of cells at one row
    for(double k = cellHeight; k <= height(); k += cellHeight)
        p.drawLine(0, k, width(), k);
    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter &p)
{
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            qreal left = (qreal)(cellWidth*j-cellWidth);
            qreal top  = (qreal)(cellHeight*k-cellHeight);
            QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
            if(universe[k*universeSize + j] == true) {
                if(generation[k*universeSize + j] == -1) p.fillRect(r, QBrush("#5fd361"));
                else if(generation[k*universeSize + j] < 2)
                p.fillRect(r, QBrush(m_masterColor));
                else
                p.fillRect(r, QBrush(m_masterColor.lighter(110*(generation[k*universeSize + j])/2)));
            }  else p.fillRect(r, QBrush("#e3e3e3"));
        }
    }
}

QColor GameWidget::masterColor()
{
    return m_masterColor;
}

void GameWidget::setMasterColor(const QColor &color)
{
    m_masterColor = color;
    update();
}

bool* GameWidget::getSurvive() const
{
    return rule.survive;
}

bool *GameWidget::getBorn() const
{
    return rule.born;
}
