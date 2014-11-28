#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mycanvas.h"
#include <QMainWindow>
#include <QRadioButton>
#include <QFrame>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_radioButton_released();

    void on_radioButton_2_released();

    void on_radioButton_3_released();

    void on_radioButton_4_released();

private:
    Ui::MainWindow *ui;

    QRadioButton* mThirdTile;
    QRadioButton* mFourthTile;

    QFrame* mSFMLFrame;
    MyCanvas* mSFMLView;
};

#endif // MAINWINDOW_H
