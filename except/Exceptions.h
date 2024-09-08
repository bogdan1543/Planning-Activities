//
// Created by bmaco on 03.04.2024.
//

#ifndef LAB6_7_EXCEPTIONS_H
#define LAB6_7_EXCEPTIONS_H

#include <string>

using namespace std;

class Exception {
private:
    string msg;
public:
    Exception(string msg) : msg(msg) {}

    string getMessage() const;
};



#endif //LAB6_7_EXCEPTIONS_H
