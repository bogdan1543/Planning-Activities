//
// Created by bmaco on 03.04.2024.
//

#include "repository.h"
#include <cassert>
#include <algorithm>
#include <fstream>

/// Add an element
/// \param activity
void Repository::add(const Activity &activity) {
    auto rez = find_if(activities.begin(),activities.end(), [title= activity.getTitle()](const Activity &a) {
        return title == a.getTitle();
    });
    if(rez != activities.end()){
        throw Exception("existing activity\n");
    }
    activities.push_back(activity);
}

/// Get position of an element in list
/// \param activity
/// \return position
int Repository::getPosition(Activity &activity) {
    for (int i = 0; i < (int)activities.size(); i++) {
        Activity &a = activities[i];
        if (a.getTitle() == activity.getTitle())
            return i;
    }
    return -1;
}

/// Delete an element
/// \param activity
void Repository::del(const Activity &activity) {
    auto rez = find_if(activities.begin(),activities.end(), [title= activity.getTitle()](const Activity &a) {
        return title == a.getTitle();
    });
    if(rez == activities.end()){
        throw Exception("non existing activity\n");
    }
    activities.erase(rez);
}


/// Modify an element in list
/// \param activity - Activity
void Repository::modify(const Activity &activity) {
    auto rez = find_if(activities.begin(),activities.end(), [title= activity.getTitle()](const Activity &a) {
        return title == a.getTitle();
    });
    if(rez == activities.end()){
        throw Exception("non existing activity\n");
    }
    activities.erase(rez);
    activities.push_back(activity);
}

/// Search for an element
/// \param title string
/// \return Activity
const Activity& Repository::search(const string& title){
    auto rez = find_if(activities.begin(),activities.end(), [title] (const Activity &activity) {
        return title == activity.getTitle();
    });
    if(rez == activities.end()){
        throw Exception("non existing activity\n");
    }
    return *rez;
}

/// Get all elements
/// \return list of elements
const vector<Activity> &Repository::getAll() {
    return activities;
}

/// Add to file
/// \param activity
void FileRepository::add(const Activity &activity){
    Repository::add(activity);
    writeToFile();
}

/// Delete from file
/// \param activity
void FileRepository::del(const Activity &activity){
    Repository::del(activity);
    writeToFile();
}

/// Modify from file
/// \param activity
void FileRepository::modify(const Activity &activity) {
    Repository::modify(activity);
    writeToFile();
}


/// Write to file
void FileRepository::writeToFile() {
    ifstream check(filename);
    if (!check.good()) {
        // Verify if the file is opened
        throw Exception("Unable to open file " + filename);
    }else {
        ofstream out(filename);
        for (const auto &activity: Repository::getAll()) {
            out << activity.getTitle() << " "
                << activity.getDescription() << " "
                << activity.getType() << " "
                << activity.getDuration() << "\n";
        }
    }
}

/// Clear file
void FileRepository::clearFile() {
    ifstream check(filename);
    if (!check.good()) {
        // Verify if the file is opened
        throw Exception("Unable to open file " + filename);
    }else{
        ofstream out(filename);
        out << "\n";
    }
}

void FileRepository::setFile(const string& file){
    filename = file;
}

void FileRepository::loadFromFile() {
    ifstream in(filename);
    if (!in.is_open()) {
        // Verify if the file is opened
        throw Exception("Unable to open file " + filename);
    }else {
        while(!in.eof()){
            string title;
            in >> title;
            string description;
            in >> description;
            string type;
            in >> type;
            int duration;
            in >> duration;
            if(in.eof()){
                //cant read the last
                break;
            }
            Activity activity(title,description,type,duration);
            Repository::add(activity);
        }
    }
    in.close();
}

/// Add to second repo
/// \param activity
void ProbRepository::add(const Activity &activity){
    if(probability > 0.5){
        throw Exception("Probability too high( >0.5)");
    }
    auto iter = activities.find(activity.getTitle());
    if(iter != activities.end()){
        throw Exception("existing activity\n");
    }
    activities.insert({activity.getTitle(), activity});
}

/// Delete from second repo
/// \param activity
void ProbRepository::del(const Activity &activity) {
    if(probability > 0.5){
        throw Exception("Probability too high( >0.5)");
    }
    auto iter = activities.find(activity.getTitle());
    if(iter == activities.end()){
        throw Exception("non existing activity\n");
    }
    activities.erase(iter);
}

/// Modify from second repo
/// \param activity
void ProbRepository::modify(const Activity &activity) {
    if(probability > 0.5){
        throw Exception("Probability too high( >0.5)");
    }
    auto iter = activities.find(activity.getTitle());
    if(iter == activities.end()){
        throw Exception("non existing activity\n");
    }
    activities[activity.getTitle()] = activity;
}

/// Get all elements from second repo
/// \return vector
const vector<Activity> &ProbRepository::getAll() {
    if(probability > 0.5){
        throw Exception("Probability too high( >0.5)");
    }
    all.clear();
    for (const auto& activity: activities)
        all.push_back((Activity)activity.second);
    return all;
}

/// Search an element in second repo
/// \param title
/// \return
const Activity &ProbRepository::search(const string &title) {
    if(probability > 0.5){
        throw Exception("Probability too high( >0.5)");
    }
    auto iter = activities.find(title);
    if(iter == activities.end()){
        throw Exception("non existing activity\n");
    }
    return activities[title];
}


//tests
void testLoadWrite(){

    FileRepository frepository("test_current_activities.txt");
    assert(frepository.getAll().size() == 1);
    frepository.add(Activity("b","a","a",1));
    assert(frepository.getAll().size() == 2);
    frepository.clearFile();

    frepository.setFile("non_existing_file.txt");

    try {
        frepository.clearFile();
    } catch (Exception &exception) {
        assert(exception.getMessage() == "Unable to open file non_existing_file.txt");
    }
    try {
        frepository.add(Activity("c","a","a",1));
    } catch (Exception &exception) {
        assert(exception.getMessage() == "Unable to open file non_existing_file.txt");
    }


}

void testAdd(){
    Repository repository;
    Activity activity("A", "b", "c", 3);
    repository.add(activity);

    try {
        repository.add(activity);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "existing activity\n");
    }


    FileRepository frepository("test_current_activities.txt");
    frepository.add(activity);
    assert(frepository.getAll().size() == 1);

    try {
        frepository.add(activity);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "existing activity\n");
    }
    frepository.clearFile();

    ProbRepository probRepository(0.5);
    probRepository.add(activity);
    assert(probRepository.getAll().size() == 1);

    try {
        probRepository.add(activity);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "existing activity\n");
    }

    ProbRepository probRepository2(1);
    try {
        probRepository2.add(activity);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "Probability too high( >0.5)");
    }
}


void testDel() {
    Repository repository;
    Activity activity("A", "b", "c", 3);
    repository.add(activity);

    Activity activity1("x", "y", "z", 2);

    try {
        repository.del(activity1);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "non existing activity\n");
    }

    assert(repository.getPosition(activity1) == -1);

    repository.del(activity);
    const auto &activities = repository.getAll();
    assert(activities.empty());

    try {
        repository.del(activity);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "non existing activity\n");
    }
    Activity activity2("B", "b", "c", 3);
    repository.add(activity);
    repository.add(activity1);
    repository.add(activity2);
    repository.del(activity1);


    FileRepository frepository("test_current_activities.txt");
    frepository.setFile("test_current_activities.txt");
    frepository.add(activity);

    frepository.del(activity);
    assert(frepository.getAll().empty());

    try {
        frepository.del(activity);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "non existing activity\n");
    }

    frepository.clearFile();

    ProbRepository probRepository(0.5);
    probRepository.add(activity);

    probRepository.del(activity);

    try {
        probRepository.del(activity);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "non existing activity\n");
    }

    ProbRepository probRepository2(1);
    try {
        probRepository2.del(activity);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "Probability too high( >0.5)");
    }
}

void testModify() {
    Repository repository;
    Activity activity("A", "b", "c", 3);
    repository.add(activity);

    Activity activity1("A", "y", "z", 2);
    Activity activity2("c", "d", "e", 4);

    try {
        repository.modify(activity2);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "non existing activity\n");
    }

    repository.modify(activity1);
    auto activities = repository.getAll();
    auto activities1 = repository.getAll();
    activities1 = activities;
    auto i = repository.getPosition(activity1);
    assert(activity1 == activities[i]);

    FileRepository frepository("test_current_activities.txt");
    frepository.setFile("test_current_activities.txt");
    frepository.add(activity);

    try {
        frepository.modify(activity2);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "non existing activity\n");
    }
    frepository.modify(activity1);


    activities = frepository.getAll();
    i = frepository.getPosition(activity1);
    assert(activity1 == activities[i]);
    frepository.del(activity1);
    frepository.clearFile();

    frepository.add(Activity("a","a","a",2));

    ProbRepository probRepository(0.5);
    probRepository.add(activity);

    probRepository.modify(activity1);

    try {
        probRepository.modify(activity2);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "non existing activity\n");
    }

    ProbRepository probRepository2(1);
    try {
        probRepository2.modify(activity);
    } catch (Exception &exception) {
        assert(exception.getMessage() == "Probability too high( >0.5)");
    }
}

void testSearch() {
    Repository repository;
    Activity activity("A", "b", "c", 3);
    repository.add(activity);
    Activity activityFound = repository.search("A");
    assert(activityFound == activity);

    try {
        repository.search("B");
    } catch (Exception &exception) {
        assert(exception.getMessage() == "non existing activity\n");
    }

    ProbRepository probRepository(0.5);
    probRepository.add(activity);

    probRepository.search(activity.getTitle());

    try {
        probRepository.search("faina");
    } catch (Exception &exception) {
        assert(exception.getMessage() == "non existing activity\n");
    }

    ProbRepository probRepository2(1);
    try {
        probRepository2.search(activity.getTitle());
    } catch (Exception &exception) {
        assert(exception.getMessage() == "Probability too high( >0.5)");
    }
    try {
        probRepository2.getAll();
    } catch (Exception &exception) {
        assert(exception.getMessage() == "Probability too high( >0.5)");
    }

}


