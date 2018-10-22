#ifndef SECONDARYWINDOW_H
#define SECONDARYWINDOW_H

#include <QMainWindow>

namespace Ui {
class SecondaryWindow;
}

class SecondaryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondaryWindow(QWidget *parent = nullptr);
    ~SecondaryWindow();

private slots:
    void on_openSim_clicked();

private:
    Ui::SecondaryWindow *ui;
};

#endif // SECONDARYWINDOW_H
