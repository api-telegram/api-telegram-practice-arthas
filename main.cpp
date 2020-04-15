#include <QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <QTimer>
#include <QDebug>

#include "botthread.h"

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    BotThread thread;
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, &thread, &QThread::quit);
    QObject::connect(&thread, &QThread::finished, &thread, &QThread::deleteLater);
    thread.start();

    return a.exec();
}
