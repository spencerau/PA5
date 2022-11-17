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

void Faculty::printInfo() {
    //cout << "test fuck" << endl;
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Level: " << level << endl;
    cout << "Department: " << dept << endl;
    cout << "Advisees: " << endl;
    for (int i = 0; i < students->getSize(); i++) {
        cout << students->get(i) << endl;
    }
    cout << endl;
}

void Faculty::printToFile(ofstream &writer) {
    writer << "Name: " << name << endl;
    writer << "ID: " << id << endl;
    writer << "Level: " << level << endl;
    writer << "Department: " << dept << endl;
    writer << "Advisees: " << endl;
    // this prints out a list of the advisees only be ID
    for (int i = 0; i < students->getSize(); i++) {
        writer << students->get(i) << endl;
    }
    writer << endl;
}


DblList<int>* Faculty::getAdvisees() {
    return students;
}

bool Faculty::operator == (Faculty &rhs) {
    return id == rhs.getid();
}

bool Faculty::operator > (Faculty &rhs) {
    return id > rhs.getid();
}

bool Faculty::operator < (Faculty &rhs) {
    return id < rhs.getid();

}