//
// Created by bmaco on 27.05.2024.
//

#ifndef LAB6_7_OBSERVER_H
#define LAB6_7_OBSERVER_H


#include <vector>
#include <iostream>

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
private:
    std::vector<Observer*> observers;
protected:
    void notify();
public:
    void addObserver(Observer *observer);

    void removeObserver(Observer *observer);
};


#endif //LAB6_7_OBSERVER_H
