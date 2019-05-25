#ifndef PATTERNS_H
#define PATTERNS_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class Patterns;
}

class Patterns : public QDialog
{
    Q_OBJECT

public:
    explicit Patterns(QWidget *parent = nullptr);
    ~Patterns();
    void mousePressEvent(QMouseEvent *e);

public slots:
    void choice();

private:
    Ui::Patterns *ui;
};

#endif // PATTERNS_H
