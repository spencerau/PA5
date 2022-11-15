/*
Your program will keep references to both the faculty and student tables in memory. These references are simply ScapegoatST instances.
Once the tables have been created, a menu should be presented to the user to allow them to manipulate the database. The choices should include:
1. Print all students and their information (sorted by ascending id #)
2. Print all faculty and their information (sorted by ascending id #)
3. Find and display student information given the students id
4. Find and display faculty information given the faculty id
5. Add a new student
6. Delete a student given the id
7. Add a new faculty member
8. Delete a faculty member given the id.
9. Change a student’s advisor given the student id and the new faculty id.
10. Remove an advisee from a faculty member given the ids
11. Exit
When a command is selected, you should prompt the user for the required data, and execute the command. If there are any errors, you should inform 
the user describing what the error is and abort the command.

All of the above commands should enforce referential integrity. That is to say, a student can not have an advisor that is not in the faculty table. 
A faculty member can’t have an advisee not in the student table. If a faculty member is deleted, then their advisees must have their advisors changed, 
etc. Your commands will be responsible for maintaining referential integrity. If a user issues a command that would break referential integrity, 
you should warn them and abort the command, or execute the command and fix any violations as appropriate.
 
After each command is executed, the menu should be displayed again, and the user allowed to continue.
If the user selects the Exit option, prior to quitting your program should create a file, named runLog.txt, which contains the information of both 
tables at the time the program was terminated. (This is the information from option 1 and option 2, just printed to the file instead of the terminal).
*/

#include "Interface.h"
#include <iostream>

using namespace std;

Interface::Interface() {
    this->students = new ScapegoatST<Student*>();
    this->faculty = new ScapegoatST<Faculty*>();
}

Interface::~Interface() {
    delete students;
    delete faculty;
}

void Interface::run() {
    int result = -1;
    while (result != 11) {
        printOptions();
        cin >> result;

        switch (result) {
            case 1:
                printAllStudents();
                break;
            case 2:
                printAllFaculty();
                break;
            case 3:
                cout << "Enter in the Student ID You Wish to Display:" << endl;
                int id;
                cin >> id;
                printStudent(id);
                break;
            case 4:
                cout << "Enter in the Faculty ID You Wish to Display:" << endl;
                int id;
                cin >> id;
                printFaculty(id);
                break;
            case 5:
                addStudent();
                break;
            case 6:
                cout << "Enter in the Student ID You Wish to Delete" << endl;
                int id;
                cin >> id;
                deleteStudent(id);
                break;
            case 7:
                addFaculty();
                break;
            case 8:
                cout << "Enter in the Faculty ID You Wish to Delete" << endl;
                int id;
                cin >> id;
                deleteFaculty(id);
                break;
            case 9:
                cout << "Enter in the Student ID" << endl;
                int studentid;
                cin >> studentid;
                cout << "Enter in the Faculty ID" << endl;
                int facultyid;
                cin >> facultyid;
                changeAdvisor(studentid, facultyid);
                break;
            case 10:
                cout << "Enter in the Student ID" << endl;
                int studentid;
                cin >> studentid;
                cout << "Enter in the Faculty ID" << endl;
                int facultyid;
                cin >> facultyid;
                removeAdvisee(studentid, facultyid);
                break;
            case 11:
                // print out to runLog.txt
                writeToFile();
                break;
            default:
                cout << "That option is not valid. Please choose an option between 1 and 11." << endl;
                break;
        }
    }

}

void Interface::printOptions() {
    cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the students id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Add a new student" << endl;
    cout << "6. Delete a student given the id" << endl;
    cout << "7. Add a new faculty member" << endl;
    cout << "8. Delete a faculty member given the id." << endl;
    cout << "9. Change a student’s advisor given the student id and the new faculty id." << endl;
    cout << "10. Remove an advisee from a faculty member given the ids" << endl;
    cout << "11. Exit" << endl;
}

void Interface::printAllStudents() {

}

void Interface::printAllFaculty() {

}

void Interface::printStudent(int id) {

}

void Interface::printFaculty(int id) {

}

void Interface::addStudent() {
    int id;
    cout << "" << endl;
    cin >> id;

    string name;
    cout << "" << endl;
    cin >> name;

    string level;
    cout << "" << endl;
    cin >> level;

    string major;
    cout << "" << endl;
    cin >> major;

    double gpa;
    cout << "" << endl;
    cin >> gpa;

    int advisor;
    cout << "" << endl;
    cin >> advisor;

    Student *newStudent = new Student(id, name, level, major, gpa, advisor);
    students->insert(newStudent);
}

void Interface::deleteStudent(int id) {

}

void Interface::addFaculty() {
    int id;
    cout << "" << endl;
    cin >> id;

    string name;
    cout << "" << endl;
    cin >> name;

    string level;
    cout << "" << endl;
    cin >> level;

    string dept;
    cout << "" << endl;
    cin >> dept;

    Faculty *newFaculty = new Faculty(id, name, level, dept);
    faculty->insert(newFaculty);
}

void Interface::deleteFaculty(int id) {

}

void Interface::changeAdvisor(int studentid, int facultyid) {

}

void Interface::removeAdvisee(int studentid, int facultyid) {

}

void Interface::writeToFile() {

}