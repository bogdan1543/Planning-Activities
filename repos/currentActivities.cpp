//
// Created by bmaco on 24.04.2024.
//
#include "currentActivities.h"

void currentActivities::add(const Activity &activity) {
    current_activities.push_back(activity);
}

void currentActivities::clear() {
    current_activities.clear();
}

void currentActivities::generate(int nr, vector<Activity> activities) {
    while(nr){
        std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<> dist(0, (int)activities.size()-1);
        int rndNr = dist(mt);
        current_activities.push_back(activities[rndNr]);
        nr--;
    }
}

const vector<Activity>& currentActivities::list() const {
    return current_activities;
}

int currentActivities::size() {
    return (int)current_activities.size();
}
