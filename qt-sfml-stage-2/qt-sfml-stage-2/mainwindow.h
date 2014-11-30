#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mycanvas.h"
#include "jradiobutton.h"

#include <QMainWindow>
#include <QRadioButton>
#include <QFrame>
#include <QSignalMapper>

#include <vector>

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

private:
    Ui::MainWindow *ui;

    QSignalMapper* mSignalMapper;

    QFrame* mSFMLFrame;
    MyCanvas* mSFMLView;
    std::vector<JRadioButton*> mRadioButtons;
};

#endif // MAINWINDOW_H
