#ifndef CONTROLTESTER_H
#define CONTROLTESTER_H

#include <QDialog>


namespace Ui {
class controltester;
}

class controltester : public QDialog
{
    Q_OBJECT

public:
    explicit controltester(QWidget *parent = nullptr);
    ~controltester();


private:
    Ui::controltester *ui;
};

#endif // CONTROLTESTER_H
