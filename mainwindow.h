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
    Patterns pattern;

    QColor getCurrentColor() const;

    GameWidget *getGame() const;

    Ui::MainWindow *getUi() const;

    void saveFile(QString filename);



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
    QString* ruleSetName;
    QString* ruleSetSur;
    QString* ruleSetBor;

};

#endif // MAINWINDOW_H
