//
// Created by bmaco on 03.04.2024.
//

#ifndef LAB6_7_UI_H
#define LAB6_7_UI_H

#include "../business/service.h"

class Ui {
private:
    Service &serv;
public:
    Ui(Service &service) : serv(service) {};

    void run();

    void uiAddActivity();

    void uiDeleteActivity();

    void uiPrintAllActivities();

    void uiModifyActivity();

    void uiSearchActivity();

    void uiFilterByActivityType();

    void uiSortActivities();

    void uiGenerateCurrentActivities();

    void uiActivitiesTypeReport();

    void uiExportCurrentActivities();

    void uiUndoActions();
};


#endif //LAB6_7_UI_H
