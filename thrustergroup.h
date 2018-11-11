#ifndef THRUSTERGROUP_H
#define THRUSTERGROUP_H

#include <QDialog>
#include "stdlib.h"
using namespace std;

namespace Ui {
class ThrusterGroup;
}

class ThrusterGroup : public QDialog
{
    Q_OBJECT

public:
    explicit ThrusterGroup(QWidget *parent = nullptr);
    ~ThrusterGroup();





private slots:



private:
    Ui::ThrusterGroup *ui;
};

#endif // THRUSTERGROUP_H
