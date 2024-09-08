//
// Created by bmaco on 03.04.2024.
//

#ifndef LAB6_7_REPOSITORY_H
#define LAB6_7_REPOSITORY_H

#include <vector>
#include "../domain/activity.h"
#include "../except/Exceptions.h"
//#include "vector.h"
#include <unordered_map>

using namespace std;

class AbsRepository{
public:
    AbsRepository() = default;

    AbsRepository(const AbsRepository &other) = delete;

    virtual ~AbsRepository() = default;

    virtual void add(const Activity &activity) = 0;

    virtual void del(const Activity &activity) = 0;

    virtual void modify(const Activity &activity) = 0;

    virtual const vector<Activity> &getAll() = 0;

    virtual const Activity& search(const string &title) = 0;
};

class Repository: public AbsRepository{
private:
    vector<Activity> activities;
public:
    Repository() = default;

    Repository(const Repository &other) = delete;

    void add(const Activity &activity) override;

    void del(const Activity &activity) override;

    void modify(const Activity &activity) override;

    const vector<Activity> &getAll() override;

    int getPosition(Activity &activity);

    const Activity& search(const string &title) override;

};

class FileRepository: public Repository{
private:
    string filename;
    void loadFromFile();
    void writeToFile();
public:
    explicit FileRepository(string filename): Repository(), filename(filename){
        loadFromFile();
    }

    FileRepository(const FileRepository &other) = delete;

    void clearFile();

    void add(const Activity &activity) override;

    void del(const Activity &activity) override;

    void modify(const Activity &activity) override;

    void setFile(const string& file);


};

class ProbRepository: public AbsRepository{
private:
    float probability;
    unordered_map<string, Activity> activities;
    vector<Activity> all;
public:
    explicit ProbRepository(float probability): AbsRepository(), probability(probability){}

    ProbRepository(const ProbRepository &other) = delete;

    void add(const Activity &activity) override;

    void del(const Activity &activity) override;

    void modify(const Activity &activity) override;

    const vector<Activity> &getAll() override;

    const Activity& search(const string &title) override;
};

void testLoadWrite();

void testAdd();

void testDel();

void testModify();

void testSearch();

#endif //LAB6_7_REPOSITORY_H
