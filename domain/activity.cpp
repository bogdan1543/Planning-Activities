//
// Created by bmaco on 03.04.2024.
//

#include <cassert>
#include "activity.h"



string Activity::getTitle() const {
    return title;
}

string Activity::getDescription() const {
    return description;
}

string Activity::getType() const {
    return type;
}

int Activity::getDuration() const {
    return duration;
}

/// Checks if a string is valid
/// \param str string
/// \return true/false
bool validString(string str) {
    if (str.empty()) return false;
    for (int i = 0; i < (int)str.size(); i++) {
        if (!((str.at(i) >= 'a' && str.at(i) <= 'z') || (str.at(i) >= 'A' && str.at(i) <= 'Z') ||
              str.at(i) == ' '))
            return false;
    }
    return true;
}

/// Checks if an activity is valid
/// \param title string
/// \param description string
/// \param type string
/// \param duration int
void Validator::validateActivity(std::string title, std::string description, std::string type, int duration) {
    string errors;

    if (!validString(title)) errors.append("Denumirea este invalida!\n");
    if (!validString(description)) errors.append("Destinatia este invalida!\n");
    if (!validString(type)) errors.append("Tipul este invalid!\n");
    if (duration <= 0) errors.append("Pretul este invalid!\n");
    if (!errors.empty()) throw Exception(errors);
}

//tests
void testCreateActivity() {
    Activity activity("a", "b", "c", 1);
    assert(activity.getTitle() == "a");
    assert(activity.getDescription() == "b");
    assert(activity.getType() == "c");
    assert(activity.getDuration() == 1);
    assert(validString("#") == false);
}






