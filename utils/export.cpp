#include "export.h"
#include "../domain/activity.h"
#include <fstream>
#include <string>
#include <vector>

/*
Scrie in fisierul fName lista de animale
in format Comma Separated Values
arunca PetException daca nu poate crea fisierul
*/
void exportToCVS(const string& fName,const vector<Activity>& activities) {
    ofstream out(fName, std::ios::trunc);
    if (!out.is_open()) {
        throw Exception("Unable to open file:" + fName);
    }
    for (const auto& activity : activities) {
        out << activity.getTitle() << ",";
        out << activity.getDescription() << ",";
        out << activity.getType() << ",";
        out << activity.getDuration() << '\n';
    }
    out.close();
}
/*
Scrie in fisierul fName lista de animale
in format HTML
arunca PetException daca nu poate crea fisierul
*/
void exportToHTML(const string& fName, const vector<Activity>& activities) {
    ofstream out(fName, std::ios::trunc);
    if (!out.is_open()) {
        throw Exception("Unable to open file:" + fName);
    }
    out << "<html><body>" << '\n';
    out << "<table border=\"1\" style=\"width:100 % \">" << '\n';
    for (const auto& activity : activities) {
        out << "<tr>" << '\n';
        out << "<td>" << activity.getTitle() << "</td>"<<'\n';
        out << "<td>" << activity.getDescription() << "</td>" << '\n';
        out << "<td>" << activity.getType() << "</td>" << '\n';
        out << "<td>" << activity.getDuration() << "</td>" << '\n';
        out << "</tr>" << '\n';
    }
    out << "</table>" << '\n';
    out << "</body></html>" << '\n';
    out.close();
}