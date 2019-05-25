#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include "gamewidget.h"
#include "patterns.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void selected(bool*,int);

public slots:
    void selectPattern();
    void selectMasterColor();
    void onComboboxChanged();
    void saveGame();
    void loadGame();


private:
    Ui::MainWindow *ui;
    QColor currentColor;
    GameWidget* game;
    Patterns pattern;
    QString* ruleSetName;
    QString* ruleSetSur;
    QString* ruleSetBor;

};

#endif // MAINWINDOW_H
