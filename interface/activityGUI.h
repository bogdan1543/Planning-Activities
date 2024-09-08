#ifndef LAB6_7_ACTIVITYGUI_H
#define LAB6_7_ACTIVITYGUI_H

#include "../business/service.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QMessageBox>
#include <QTableWidget>
#include <QtWidgets>
#include "../utils/MyTableModel.h"


class ActivityGUI: public QWidget, public Observer{
public:
    explicit ActivityGUI(Service &service): serv(service){
        model = new MyTableModel(service.serviceGetAll());
        model->headerData(1,Qt::Horizontal);
        tblV->setModel(model);
        initGUI();
        initConnect();
    }

    ~ActivityGUI() override{
        serv.removeObserver(this);
    }

private:
    Service &serv;

    QTableView* tblV = new QTableView;
    MyTableModel* model;


//    QTableWidget* listWidget = new QTableWidget{10,1};
    QBoxLayout* abuttonLayout = new QVBoxLayout{};

    QPushButton* addBtn = new QPushButton{"&Add"};
    QPushButton* modifyBtn = new QPushButton{"&Modify"};
    QPushButton* deleteBtn = new QPushButton{"&Delete"};
    QPushButton* filterByTypeBtn = new QPushButton{"&Filter by type"};
    QPushButton* sortByTitleBtn = new QPushButton{"&Sort by title"};
    QPushButton* sortByDescriptionBtn = new QPushButton{"&Sort by Description"};
    QPushButton* sortByTypeAndDurationBtn = new QPushButton{"&Sort by type and duration"};
    QPushButton* currentActivitiesBtn = new QPushButton{"&Current activities"};
    QPushButton* undoBtn = new QPushButton{"&Undo"};

    //QPushButton* addbtn = new QPushButton{"&Delete"};

    QLineEdit* titleTxt = new QLineEdit;
    QLineEdit* descriptionTxt = new QLineEdit;
    QLineEdit* typeTxt = new QLineEdit;
    QLineEdit* durationTxt = new QLineEdit;

    QLineEdit* filterTypeTxt = new QLineEdit;

    QPushButton* addCurrentBtn = new QPushButton{"&Add"};
    QPushButton* deleteCurrentBtn = new QPushButton{"&Delete"};
    QPushButton* generateCurrentBtn = new QPushButton{"&Generate current activities"};
    QLineEdit* currentTitleTxt = new QLineEdit;
    QLineEdit* currentGenerationsTxt = new QLineEdit;

    QPushButton* readCurrentBtn = new QPushButton{"&Current activities histogram"};

    void initGUI();

    void loadData(const vector<Activity>& activities);

    void initConnect();

    void update() override;
};

class CurrentActivitiesGUI: public QWidget, public Observer{
public:
    CurrentActivitiesGUI(Service &service): serv(service){

        loadData();
        initGUI();
        initConnect();
    }
    ~CurrentActivitiesGUI() override{
        serv.removeObserver(this);
    }
private:
    Service &serv;

    void initGUI();

    void loadData();

    void initConnect();

    QTableWidget* currentListWidget = new QTableWidget{10,4};
    QLineEdit* currentTitleTxt = new QLineEdit;
    QLineEdit* currentGenerationsTxt = new QLineEdit;
    QPushButton* addCurrentBtn = new QPushButton{"&Add"};
    QPushButton* deleteCurrentBtn = new QPushButton{"&Delete"};
    QPushButton* generateCurrentBtn = new QPushButton{"&Generate current activities"};
    QPushButton* exportCurrentBtn1 = new QPushButton{"&Export current activities to HTML"};
    QPushButton* exportCurrentBtn2 = new QPushButton{"&Export current activities to CVS"};

    QLineEdit* filenameTxt = new QLineEdit;

    void update() override;
};

class readActivitiesGUI: public QWidget, public Observer{
public:
    readActivitiesGUI(Service &service): serv(service){
        serv.addObserver(this);
    }

    ~readActivitiesGUI() override{
        serv.removeObserver(this);
    }
private:
    Service &serv;

    void update() override;

    void paintEvent(QPaintEvent* ev) override;
};

#endif //LAB6_7_ACTIVITYGUI_H
