#ifndef LAB6_7_EXPORT_H
#define LAB6_7_EXPORT_H

#include <string>
#include <vector>
#include "../domain/activity.h"

/*
Scrie in fisierul fName lista de animale
in format Comma Separated Values
arunca PetException daca nu poate crea fisierul
*/
void exportToCVS(const string& fName,const vector<Activity>& activities);

/*
Scrie in fisierul fName lista de animale
in format HTML
arunca PetException daca nu poate crea fisierul
*/
void exportToHTML(const string& fName, const vector<Activity>& activities);

#endif //LAB6_7_EXPORT_H
