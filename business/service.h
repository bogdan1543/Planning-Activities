//
// Created by bmaco on 03.04.2024.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H

#include <string>
#include <unordered_map>
#include "../repos/repository.h"
#include "../utils/export.h"
#include "../repos/currentActivities.h"
#include "undo.h"
#include <memory>
#include "../utils/Observer.h"

using namespace std;

class Service : public Observable{
private:
    AbsRepository &repo;

    unordered_map<string, int> report;

    currentActivities schedule;

    //undo
    vector<unique_ptr<Undo>> undoActions;
public:
    Service(AbsRepository &repository) : repo(repository) {};

    Service(const Service &other) = delete;

    void serviceAdd(const string& title, const string& description, const string& type, int duration);

    void serviceDelete(const string& title, const string& description, const string& type, int duration);

    void serviceModify(const string& title, const string& description, const string& type, int duration);

    const vector<Activity> &serviceGetAll();

    Activity serviceSearch(const string& title);

    vector<Activity> serviceGetFilteredByType(const string& type);

    vector<Activity> serviceSortedByTitle();

    vector<Activity> serviceSortedByDescription();

    vector<Activity> serviceSortedByTypeAndDuration();

    int serviceAddCurrentActivity(const string &title);

    int serviceDeleteCurrentActivities();

    int serviceGenerateCurrentActivities(int nr);

    unordered_map<string, int> serviceTypeReport();

    void serviceExportCurrentActivitiesToCVS(const string& fName) const;

    void serviceExportCurrentActivitiesToHTML(const string& fName) const;

    void serviceUndo();

    vector<Activity> serviceGetAllCurrentActivities();
};

void testServiceAdd();

void testServiceDelete();

void testServiceModify();

void testServiceSearch();

void testServiceFilter();

void testSort();

void testServiceAddCurrent();

void testServiceDeleteCurrent();

void testServiceGenerateCurrent();

void testServiceReport();

void testServiceExport();

void testServiceUndo();

#endif //LAB6_7_SERVICE_H
