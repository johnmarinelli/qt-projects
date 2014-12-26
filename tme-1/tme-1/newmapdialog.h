#ifndef NEWMAPDIALOG_H
#define NEWMAPDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

class NewMapDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit* mWidthInput;
    QLineEdit* mHeightInput;

    int mWidth, mHeight;

    QPushButton* mConfirm;

    QVBoxLayout* mLayout;

public:
    explicit NewMapDialog(QWidget *parent = 0);

signals:
    void makeNew(std::tuple<int, int> package);

public slots:

private slots:
    void sendNewMapInfo();

};

#endif // NEWMAPDIALOG_H
