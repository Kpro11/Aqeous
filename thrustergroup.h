#ifndef THRUSTERGROUP_H
#define THRUSTERGROUP_H

#include <QDialog>

namespace Ui {
class ThrusterGroup;
}

class ThrusterGroup : public QDialog
{
    Q_OBJECT

public:
    explicit ThrusterGroup(QWidget *parent = nullptr);
    ~ThrusterGroup();

private:
    Ui::ThrusterGroup *ui;
};

#endif // THRUSTERGROUP_H
