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

void Faculty::addStudent(int id) {
    students->addBack(id);
}

void Faculty::removeStudent(int id) {
    for (int i = 0; i < students->getSize(); i++) {
        if (students->get(i) == id) students->remove(i);
    }
}

bool Faculty::hasStudent(int id) {
    if (students->contains(id)) return true;
    else return false;
}