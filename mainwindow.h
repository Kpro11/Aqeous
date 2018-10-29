#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtAV>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double valueI;

private slots:
    void on_depth_slider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QtAV::VideoOutput *m_vo;
    QtAV::AVPlayer *m_player;

};



#endif // MAINWINDOW_H
