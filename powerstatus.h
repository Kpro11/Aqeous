#ifndef POWERSTATUS_H
#define POWERSTATUS_H

#include <QDialog>
#include "stdlib.h"
using namespace std;

namespace Ui {
class PowerStatus;
}

class PowerStatus : public QDialog
{
    Q_OBJECT

public:
    explicit PowerStatus(QWidget *parent = nullptr);
    ~PowerStatus();

private:
    Ui::PowerStatus *ui;
};

#endif // POWERSTATUS_H
