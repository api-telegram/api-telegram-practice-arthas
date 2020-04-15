#include "dostaff.h"

DoStaff::DoStaff(QObject * parent):QObject(parent)
{

}

void DoStaff::run()
{
    printf("works");
    emit(finished());
}
