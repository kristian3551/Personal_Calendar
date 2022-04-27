#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../Calendar/Calendar.h"

class Controller {
    Calendar calendar;
    void addEvent();
    void removeEvent();
    void showDayEvents();
    void changeEvent();
    void searchByString();
    void getStatsForEmployment();
    void findFreeTimeForEvent();
public:
    void run();
};

#endif