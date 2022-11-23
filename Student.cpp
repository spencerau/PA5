/*
Student records will be stored in a Student class.  Student records contain a unique student ID (an integer), a string name field, 
a string level field (Freshman, Sophomore, etc.), a string major field, a double GPA field, and an integer advisor field, which will contain 
the Faculty ID of their advisor. These are the only fields the class contains.
*/

#include <string>
#include "Student.h"
#include <iostream>

using namespace std;

Student::Student(int id, string name, string level, string major, double GPA, int advisor) {
    this->id = id;
    this->name = name;
    this->level = level;
    this->major = major;
    this->GPA = GPA;
    this->advisor = advisor;
}

Student::~Student() {

}

int Student::getid() {
    //std::cout << "getid called, returning: " << id << "\n";
    return id;
}

int Student::getAdvisor() {
    return advisor;
}

void Student::changeAdvisor(int advisor) {
    this->advisor = advisor;
}

void Student::printInfo() {
    cout << "Student Name: " << name << endl;
    cout << "Student ID: " << id << endl;
    cout << "Level: " << level << endl;
    cout << "Major: " << major << endl;
    cout << "GPA: " << GPA << endl;
    cout << "Advisor: " << advisor << endl;
    cout << endl;
}

void Student::printToFile(ofstream &writer) {
    writer << "Student Name: " << name << endl;
    writer << "Student ID: " << id << endl;
    writer << "Level: " << level << endl;
    writer << "Major: " << major << endl;
    writer << "GPA: " << GPA << endl;
    writer << "Advisor: " << advisor << endl;
    writer << endl; 
}


bool Student::operator == (Student &rhs) {
    return id == rhs.getid();
}

bool Student::operator > (Student &rhs) {
    return id > rhs.getid();
}

bool Student::operator < (Student &rhs) {
    return id < rhs.getid();

}