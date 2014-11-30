#ifndef JRADIOBUTTON_H
#define JRADIOBUTTON_H

#include <QRadioButton>

class JRadioButton : public QRadioButton
{
    Q_OBJECT
public:
    explicit JRadioButton(const QString& text, QWidget *parent = 0);

    void setIconPath(const QString path);

signals:

public slots:

private:
    QString mIconPath;

};

#endif // JRADIOBUTTON_H
