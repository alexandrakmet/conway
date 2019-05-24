#ifndef PATTERNS_H
#define PATTERNS_H

#include <QDialog>

namespace Ui {
class Patterns;
}

class Patterns : public QDialog
{
    Q_OBJECT

public:
    explicit Patterns(QWidget *parent = nullptr);
    ~Patterns();
Ui::Patterns *ui;
private:
    void paintUniverse(QPainter &p);

};

#endif // PATTERNS_H
