#include <string>
#include "Faculty.h"
#include <iostream>

using namespace std;

Faculty::Faculty(int id, string name, string level, string dept) {
    this->id = id;
    this->name = name;
    this->level = level;
    this->dept = dept;
    this->students = new DblList<int>;
}

Faculty::~Faculty() {
    delete this->students;
}

int Faculty::getid() {
    return id;
}