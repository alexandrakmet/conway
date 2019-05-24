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

private:
    Ui::Patterns *ui;
};

#endif // PATTERNS_H
