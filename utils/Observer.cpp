//
// Created by bmaco on 27.05.2024.
//

#include <algorithm>
#include "Observer.h"

void Observable::notify() {
    for(auto obs : observers){
        obs->update();
    }
}

void Observable::addObserver(Observer *observer) {
    observers.push_back(observer);
}

void Observable::removeObserver(Observer *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}
