//
// Created by bmaco on 03.04.2024.
//

#include <cassert>
#include <random>
#include <algorithm>
#include <fstream>
#include "service.h"



/// Add an activity
/// \param title string
/// \param description string
/// \param type string
/// \param duration int
void Service::serviceAdd(const string& title, const string& description, const string& type, int duration) {
    Validator valid;
    valid.validateActivity(title, description, type, duration);

    Activity activity(title, description, type, duration);

    repo.add(activity);
    undoActions.push_back(make_unique<UndoAdd>(repo, activity));
    notify();
}

/// Get all activities
/// \return List of activities
const vector<Activity> &Service::serviceGetAll() {
    return repo.getAll();
}

/// Delete an activity
/// \param title string
/// \param description string
/// \param type string
/// \param duration int
void Service::serviceDelete(const string& title, const string& description, const string& type, int duration) {
    Validator valid;
    valid.validateActivity(title, description, type, duration);

    Activity activity(title, description, type, duration);
    auto ac_type = serviceSearch(title).getType();

    repo.del(activity);


    undoActions.push_back(make_unique<UndoDelete>(repo, activity));

    notify();
}


/// Modify an activity
/// \param title string
/// \param description string
/// \param type string
/// \param duration int
void Service::serviceModify(const string& title, const string& description, const string& type, int duration) {
    Validator valid;
    valid.validateActivity(title, description, type, duration);

    Activity activity(title, description, type, duration);
    auto old_activity = repo.search(activity.getTitle());
    auto old_type = old_activity.getType();

    repo.modify(activity);


    undoActions.push_back(make_unique<UndoModify>(repo, old_activity));

    notify();
}

/// Search an activity
/// \param title
/// \return
Activity Service::serviceSearch(const string& title){
    Validator valid;
    valid.validateActivity(title, "description", "type", 1);

    return repo.search(title);
}

/// Filter activities by type
/// \param type
/// \return
vector<Activity> Service::serviceGetFilteredByType(const string& type){
    vector<Activity> rez;
    vector activities = repo.getAll();
    rez.resize(activities.size());
    auto end_it = copy_if(activities.begin(), activities.end(), rez.begin(), [type] (const Activity &activity) {
        return type == activity.getType();
    });
    rez.resize(distance(rez.begin(), end_it));
    return rez;
}

int cmpTitle(const Activity& a, const Activity& b) {
    if (a.getTitle() < b.getTitle())
        return 1;
    return 0;
}

int cmpDescription(const Activity& a, const Activity& b){
    if(a.getDescription() < b.getDescription())
        return 1;
    return 0;
}
int cmpType(const Activity& a, const Activity& b){
    if(a.getType() < b.getType())
        return 1;
    else if(a.getType() == b.getType())
        if(a.getDuration() < b.getDuration())
            return 1;
    return 0;
}


/// Sory activities by title
/// \return
vector<Activity> Service::serviceSortedByTitle() {
    vector<Activity> rez = repo.getAll();

    sort(rez.begin(), rez.end(), cmpTitle);
    if (!rez.empty())
        return rez;

}


/// Sort activities by description
/// \return
vector<Activity> Service::serviceSortedByDescription(){
    vector<Activity> rez = repo.getAll();
    sort(rez.begin(), rez.end(), cmpDescription);
    if (!rez.empty())
        return rez;
}

/// Sort activities by type and duration
/// \return
vector<Activity> Service::serviceSortedByTypeAndDuration(){
    vector<Activity> rez = repo.getAll();
    sort(rez.begin(), rez.end(), cmpType);

    if (!rez.empty())
        return rez;
}


/// Add activity to current list
/// \param title string
/// \return size of Current list of activities
int Service::serviceAddCurrentActivity(const string& title){
    Validator valid;
    valid.validateActivity(title,"description","type",1);

    auto activity = repo.search(title);
    schedule.add(activity);

    notify();

    return schedule.size();
}

/// Delete list of current activities
/// \return size of Current list of activities
int Service::serviceDeleteCurrentActivities(){
    schedule.clear();
    notify();
    return schedule.size();
}


/// Generate activities to current list
/// \param title string
/// \return size of Current list of activities
int Service::serviceGenerateCurrentActivities(int nr){
    auto activities = repo.getAll();
    schedule.generate(nr, activities);
    notify();
    return schedule.size();
}

/// Activities type report
/// \return unordered map of activities type
unordered_map<string, int> Service::serviceTypeReport(){
    auto lst = serviceGetAll();
    for(const auto& activity : lst){
        report[activity.getType()]++;
    }
    return report;
}

/// Export to cvs
/// \param fName
void Service::serviceExportCurrentActivitiesToCVS(const string& fName) const {
    exportToCVS(fName, schedule.list());

}

/// Export to html
/// \param fName
void Service::serviceExportCurrentActivitiesToHTML(const string& fName) const {
    exportToHTML(fName, schedule.list());
}

vector<Activity> Service::serviceGetAllCurrentActivities(){
    return schedule.list();
}

/// Undo last action
void Service::serviceUndo(){
    if(undoActions.empty())
        throw Exception("Nothing to undo");
    undoActions.back()->doUndo();
    undoActions.pop_back();
    notify();
}


//tests
void testServiceAdd() {
    Repository repo;
    Service serv(repo);

    serv.serviceAdd("a", "a", "a", 1);
    const auto &activities = serv.serviceGetAll();
    assert(activities.size() == 1);

}

void testServiceDelete() {
    Repository repo;
    Service serv(repo);

    serv.serviceAdd("a", "a", "a", 1);
    serv.serviceDelete("a", "a", "a", 1);
    const auto &activities = serv.serviceGetAll();
    assert(activities.empty());
}

void testServiceModify() {
    Repository repo;
    Service serv(repo);

    serv.serviceAdd("a", "a", "a", 1);
    serv.serviceModify("a", "a", "a", 1);
    const auto &activities = serv.serviceGetAll();
    assert(activities.size() == 1);
}

void testServiceSearch() {
    Repository repo;
    Service serv(repo);

    Activity a("a", "a", "a", 1);
    serv.serviceAdd("a", "a", "a", 1);
    Activity a_found = serv.serviceSearch("a");
    assert(a_found == a);
}

void testServiceFilter(){
    Repository repo;
    Service serv(repo);
    serv.serviceAdd("a", "a", "a", 1);
    serv.serviceAdd("b", "a", "a", 1);
    vector<Activity> list = serv.serviceGetFilteredByType("a");
    assert(list.size() == 2);
}

void testSort(){
    Repository repo;
    Service serv(repo);

    vector sorted = serv.serviceSortedByTitle();
    assert(sorted.empty());
    sorted = serv.serviceSortedByDescription();
    assert(sorted.empty());
    sorted = serv.serviceSortedByTypeAndDuration();
    assert(sorted.empty());


    serv.serviceAdd("b", "y", "b", 2);
    serv.serviceAdd("c", "z", "a", 2);
    serv.serviceAdd("a", "x", "a", 1);
    sorted = serv.serviceSortedByTitle();
    assert(sorted[0].getTitle() == "a");
    assert(sorted.size() == 3);

    sorted = serv.serviceSortedByDescription();
    assert(sorted[2].getDescription() == "z");

    serv.serviceAdd("r", "x", "c", 1);
    sorted = serv.serviceSortedByTypeAndDuration();

    assert(sorted[0].getDuration() == 1);
}

void testServiceAddCurrent(){
    Repository repo;
    Service serv(repo);
    serv.serviceAdd("a", "a", "a", 1);
    serv.serviceAdd("b", "a", "a", 1);
    auto size = serv.serviceAddCurrentActivity("a");
    assert(size == 1);
}

void testServiceDeleteCurrent(){
    Repository repo;
    Service serv(repo);
    serv.serviceAdd("a", "a", "a", 1);
    serv.serviceAdd("b", "a", "a", 1);
    serv.serviceAddCurrentActivity("a");
    auto size = serv.serviceDeleteCurrentActivities();
    assert(!size);
}

void testServiceGenerateCurrent(){
    Repository repo;
    Service serv(repo);
    serv.serviceAdd("a", "a", "a", 1);
    serv.serviceAdd("b", "a", "a", 1);
    auto size = serv.serviceGenerateCurrentActivities(4);
    assert(size == 4);
}

void testServiceReport(){
    Repository repo;
    Service serv(repo);

    serv.serviceAdd("a", "a", "a", 1);
    const auto &activities = serv.serviceTypeReport();
    assert(activities.size() == 1);

}

void testServiceExport(){
    Repository repo;
    Service serv(repo);
    serv.serviceAdd("aaa", "bbb","ccc", 3);
    serv.serviceAdd("ccc", "bbb","aaa", 2);
    serv.serviceAdd("bbb", "bbb","bbb", 1);
    serv.serviceGenerateCurrentActivities(3);
    serv.serviceExportCurrentActivitiesToCVS("test.cvs");
    std::ifstream in("test.cvs");
    assert(in.is_open());
    int countLines = 0;
    while (!in.eof()) {
        string line;
        in >> line;
        countLines++;
    }
    in.close();
    assert(countLines == 4);//+ blank line
    serv.serviceExportCurrentActivitiesToHTML("test.html");
    in.open("test.html");
    assert(in.is_open());


    try {
        serv.serviceExportCurrentActivitiesToCVS("test/Export.cvs");
    }
    catch (Exception&) {
        assert(true);
    }
    try {
        serv.serviceExportCurrentActivitiesToHTML("a/b/c/Export.html");
    }
    catch (Exception&) {
        assert(true);
    }
}

void testServiceUndo(){
    Repository repo;
    Service serv(repo);
    serv.serviceAdd("aaa", "bbb","ccc", 3);
    serv.serviceAdd("ccc", "bbb","aaa", 2);
    serv.serviceAdd("bbb", "bbb","bbb", 1);
    serv.serviceUndo();
    assert(serv.serviceGetAll().size() == 2);
    serv.serviceDelete("aaa", "bbb","ccc", 3);
    serv.serviceUndo();
    serv.serviceModify("aaa", "nnn","nnn", 2);
    serv.serviceUndo();
    assert(serv.serviceSearch("aaa").getDescription() == "bbb");
    serv.serviceUndo();
    serv.serviceUndo();
    assert(serv.serviceGetAll().empty());
    try {
        serv.serviceUndo();
    }
    catch (Exception& exception) {
        assert(exception.getMessage() == "Nothing to undo");
    }
}