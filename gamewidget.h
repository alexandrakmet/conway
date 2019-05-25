#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QWidget>
#include <QRandomGenerator>
#include <QMouseEvent>


class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

    int getUniverseSize() const;

    int getGenerations() const;

    QColor getMasterColor() const;

    bool *getSurvive() const;
    bool *getBorn() const;

    bool *getUniverse() const;

    int *getGeneration() const;

    bool getPatternSelected() const;

    bool timerState();

protected:

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    //when one of the cell has been changed,emit this signal to lock the universeSize
    void environmentChanged(bool ok);
    //when game is over or clear is called,emit it to unlock the universeSize
    void gameEnds(bool ok);

public slots:
    void startGame(const int &number = -1); // start
    void stopGame(); // finish
    void clear(); // clear
    void random();
    void patternSelected(bool*,int);


    int cellNumber(); // number of the cells in one row
    void setCellNumber(const int &s); // set number of the cells in one row

    int interval(); // interval between generations
    void setInterval(int msec); // set interval between generations

    QColor masterColor(); // color of the cells
    void setMasterColor(const QColor &color); // set color of the cells

    QString dump(); // dump of current universe
    void setDump(const QString &data); // set current universe from it's dump
    void setRule(bool*, bool*);

private slots:
    void paintGrid(QPainter &p);
    void paintUniverse(QPainter &p);
    void newGeneration();

private:
    bool PatternSelected;
    bool* pattern;
    int patternSize;
    QRandomGenerator g;
    QColor m_masterColor;
    QTimer* timer;
    int generations;
    bool* universe; // map
    bool* next; // map
    int* generation;
    int universeSize;
    struct Rule {
        bool* survive;
        bool* born;
    } rule;

    bool isAlive(int k, int j); // return true if universe[k][j] accept rules
    void resetUniverse();// reset the size of universe
};

#endif // GAMEWIDGET_H
