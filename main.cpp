#include "domain/activity.h"
#include "repos/repository.h"
#include "interface/ui.h"
#include "interface/activityGUI.h"
#include <QtWidgets/QApplication>


void testAll() {
    testCreateActivity();
    testLoadWrite();
    testAdd();
    testDel();
    testModify();
    testSearch();
    testServiceAdd();
    testServiceDelete();
    testServiceModify();
    testServiceSearch();
    testServiceFilter();
    testServiceAddCurrent();
    testServiceDeleteCurrent();
    testServiceGenerateCurrent();
    testSort();
    testServiceReport();
    testServiceExport();
    testServiceUndo();

}

int main(int arg, char *argv[]) {
    //testAll();
    //Repository repository;
    //ProbRepository probRepository(0.1);
    FileRepository frepository("activities");
    Service service(frepository);

    Ui ui(service);
    //ui.run();

    QApplication application(arg, argv);
    ActivityGUI gui(service);
    gui.show();


    return application.exec();
}
