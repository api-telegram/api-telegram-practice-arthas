#ifndef DOSTAFF_H
#define DOSTAFF_H

#include <QObject>
#include <iostream>


class DoStaff: public QObject
{
    Q_OBJECT
public:
    DoStaff(QObject *parent = 0);

public slots:
    void run();

 signals:
    void finished();
};

#endif // DOSTAFF_H
