//
// Created by bmaco on 03.04.2024.
//

#ifndef LAB6_7_ACTIVITY_H
#define LAB6_7_ACTIVITY_H

#include <string>
#include <iostream>
#include "../except/Exceptions.h"

using namespace std;

class Validator {
public:
    void validateActivity(string title, string description, string type, int duration);
};

class Activity {
private:
    string title;
    string description;
    string type;
    int duration;
public:
    string getTitle() const;

    string getDescription() const;

    string getType() const;

    int getDuration() const;

    Activity() = default;

    Activity(string title, string description, string type, int duration) : title(title), description(description),
                                                                            type(type), duration(duration) {}

    Activity(const Activity &other): title(other.title), description(other.description), type(other.type), duration(other.duration) {}




    int operator==(const Activity &other){
        return other.title == title && other.description == description && other.type == type && other.duration == duration;
    }
};

void testCreateActivity();

#endif //LAB6_7_ACTIVITY_H
