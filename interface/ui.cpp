//
// Created by bmaco on 03.04.2024.
//

#include "ui.h"
#include <iostream>

using namespace std;

void Ui::run() {
    int running = 1;
    while (running) {
        cout << "1 Add\n"
                "2 Delete\n"
                "3 Modify\n"
                "4 Print all\n"
                "5 Search\n"
                "6 Filter by type\n"
                "7 Sort by attribute\n"
                "8 Generate current activities\n"
                "9 Print type raport current activities\n"
                "10 Export current activities\n"
                "11 Undo\n"
                "0 Exit\n"
                "Command:";
        int cmd = 0;
        cin >> cmd;
        switch (cmd) {
            case 1:
                uiAddActivity();
                break;
            case 2:
                uiDeleteActivity();
                break;
            case 3:
                uiModifyActivity();
                break;
            case 4:
                uiPrintAllActivities();
                break;
            case 5:
                uiSearchActivity();
                break;
            case 6:
                uiFilterByActivityType();
                break;
            case 7:
                uiSortActivities();
                break;
            case 8:
                uiGenerateCurrentActivities();
                break;
            case 9:
                uiActivitiesTypeReport();
                break;
            case 10:
                uiExportCurrentActivities();
                break;
            case 11:
                uiUndoActions();
                break;
            case 0:
                running = 0;
                break;
        }

    }
}

void Ui::uiAddActivity() {
    int command = 0;
    cout << "1 Add to list of activities\n2 Add to current list of activities\n";
    cout <<"Command:";
    cin >> command;
    if(command == 1){
        string title, description, type;
        int duration = 0;
        cout << "Title: ";
        cin >> title;
        cout << "Description: ";
        cin >> description;
        cout << "Type: ";
        cin >> type;
        cout << "Duration: ";
        cin >> duration;

        try {
            serv.serviceAdd(title, description, type, duration);
            cout << "Activity added\n";
        } catch (Exception &exception) {
            cout << exception.getMessage();
        }
    }else if(command == 2){
        string title;
        cout << "Title: ";
        cin >> title;
        try {
            auto size = serv.serviceAddCurrentActivity(title);
            cout << "Current activity added\n";
            cout << "Current activities' list size: "<< size <<'\n';
        } catch (Exception &exception) {
            cout << exception.getMessage();
        }
    }else throw "invalid command\n";


}

void Ui::uiPrintAllActivities() {
    try{
        const auto &activities = serv.serviceGetAll();
        cout << "Number of activities: " << activities.size() << '\n';
        for (auto &activity: activities) {
            cout << activity.getTitle() << " " << activity.getDescription() << " " << activity.getType() << " "
                 << activity.getDuration() << '\n';
        }
    }catch(Exception exception){
        cout<<exception.getMessage();
    }


}

void Ui::uiDeleteActivity() {
    int command = 0;
    cout << "1 Delete an activity from list of activities\n2 Delete all current activities\n";
    cout <<"Command:";
    cin >> command;
    if(command == 1){
        string title, description, type;
        int duration = 0;
        cout << "Title: ";
        cin >> title;
        cout << "Description: ";
        cin >> description;
        cout << "Type: ";
        cin >> type;
        cout << "Duration: ";
        cin >> duration;

        try {
            serv.serviceDelete(title, description, type, duration);
            cout << "Activity deleted\n";
        } catch (Exception &exception) {
            cout << exception.getMessage();
        }
    }else if(command == 2){
        try {
            auto size = serv.serviceDeleteCurrentActivities();
            cout << "Current activities deleted\n";
            cout << "Current activities' list size: "<< size <<'\n';
        } catch (Exception &exception) {
            cout << exception.getMessage();
        }
    }else throw "invalid command\n";

}

void Ui::uiModifyActivity() {
    string title, description, type;
    int duration = 0;
    cout << "Title: ";
    cin >> title;
    cout << "New description: ";
    cin >> description;
    cout << "New type: ";
    cin >> type;
    cout << "New duration: ";
    cin >> duration;

    try {
        serv.serviceModify(title, description, type, duration);
        cout << "Activity modified\n";
    } catch (Exception &exception) {
        cout << exception.getMessage();
    }
}

void Ui::uiSearchActivity() {
    string title;
    cout << "Title: ";
    cin >> title;

    try {
        Activity activity = serv.serviceSearch(title);
        cout << "Activity found:\n";
        cout << activity.getTitle() << " " << activity.getDescription() << " " << activity.getType() << " "
             << activity.getDuration() << '\n';
    } catch (Exception &exception) {
        cout << exception.getMessage();
    }
}

void Ui::uiFilterByActivityType(){
    string type;
    cout << "Type: ";
    cin >> type;

    try {
        const auto &activities = serv.serviceGetFilteredByType(type);
        for (auto &activity: activities) {
            cout << activity.getTitle() << " " << activity.getDescription() << " " << activity.getType() << " "
                 << activity.getDuration() << '\n';
        }

    } catch (Exception &exception) {
        cout << exception.getMessage();
    }
}

void Ui::uiSortActivities(){
    int command = 0;
    cout << "Sort by: \n1 Title\n2 Description\n3 Type and duration\n";
    cout <<"Command:";
    cin >> command;
    if(command == 1){
        const auto &activities = serv.serviceSortedByTitle();
        for (auto &activity: activities) {
            cout << activity.getTitle() << " " << activity.getDescription() << " " << activity.getType() << " "
                 << activity.getDuration() << '\n';
        }
    }else if(command == 2){
        const auto &activities = serv.serviceSortedByDescription();
        for (auto &activity: activities) {
            cout << activity.getTitle() << " " << activity.getDescription() << " " << activity.getType() << " "
                 << activity.getDuration() << '\n';
        }
    }else if(command == 3){
        const auto &activities = serv.serviceSortedByTypeAndDuration();
        for (auto &activity: activities) {
            cout << activity.getTitle() << " " << activity.getDescription() << " " << activity.getType() << " "
                 << activity.getDuration() << '\n';
        }
    }else throw "invalid command\n";


}

void Ui::uiGenerateCurrentActivities(){
    int nrGenerated = 0;
    cout << "Number of activities you want to generate: ";
    cin >> nrGenerated;

    try {
        auto size = serv.serviceGenerateCurrentActivities(nrGenerated);
        cout << "Current activities generated\n";
        cout << "Current activities' list size: "<< size <<'\n';
    } catch (Exception &exception) {
        cout << exception.getMessage();
    }
}

void Ui::uiActivitiesTypeReport(){
    const auto &typeReport = serv.serviceTypeReport();
    for (auto &type: typeReport) {
        cout << type.first << " " << type.second << " " << '\n';
    }

}


void Ui::uiExportCurrentActivities() {
    int fileType = 0;
    cout << "File type: \n1. HTML\n2. CVS\n";
    cin >> fileType;

    if(fileType == 1){
        string filename;
        cout << "File name: ";
        cin >> filename;
        try{
            serv.serviceExportCurrentActivitiesToHTML(filename);
        }catch (Exception exception){
            cout << exception.getMessage();
        }
    }else{
        string filename;
        cout << "File name: ";
        cin >> filename;
        try{
            serv.serviceExportCurrentActivitiesToCVS(filename);
        }catch (Exception exception){
            cout << exception.getMessage();
        }
    }
}

void Ui::uiUndoActions() {
    try{
        serv.serviceUndo();
    }catch (Exception exception){
        cout << exception.getMessage();
    }
}
