//
// Created by bmaco on 24.04.2024.
//

#ifndef LAB6_7_CURRENTACTIVITIES_H
#define LAB6_7_CURRENTACTIVITIES_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "../domain/activity.h"

class currentActivities{
private:
    vector<Activity> current_activities;
public:
    currentActivities() = default;

    void add(const Activity& activity);

    void clear();

    int size();

    void generate(int nr, vector<Activity> activities);

    [[nodiscard]] const vector<Activity>& list() const;
};

#endif //LAB6_7_CURRENTACTIVITIES_H
