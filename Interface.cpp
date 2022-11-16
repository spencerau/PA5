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
    int facultyid;
    int studentid;
    int id;
    while (result != 11) {
        printOptions();
        cin >> result;
        // flag: 0 = DNE, 1 = exists already
        switch (result) {
            case 1:
                printAllStudents();
                break;
            case 2:
                printAllFaculty();
                break;
            case 3:
                cout << "Enter in the Student ID You Wish to Display:" << endl;
                cin >> id;
                printStudent(id);
                break;
            case 4:
                cout << "Enter in the Faculty ID You Wish to Display:" << endl;
                cin >> id;
                printFaculty(id);
                break;
            case 5:
                addStudent();
                break;
            case 6:
                id = promptForStudent(0);
                deleteStudent(id);
                break;
            case 7:
                addFaculty();
                break;
            case 8:
                id = promptForFaculty(0);
                deleteFaculty(id);
                break;
            case 9:
                int studentid = promptForStudent(0);
                int facultyid = promptForFaculty(0);
                changeAdvisor(studentid, facultyid);
                break;
            case 10:
                studentid = promptForStudent(0);
                facultyid = promptForFaculty(0);
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
    students->printTreeInOrder();
    /*
    for (int i = 0; i < students->getSize(); i++) {
        students.
    }
    */
}

void Interface::printAllFaculty() {
    faculty->printTreeInOrder();
}

void Interface::printStudent(int id) {
    Student *student = students->getByID(id);
    student->printInfo();
    delete student;
}

void Interface::printFaculty(int id) {
    Faculty *advisor = faculty->getByID(id);
    advisor->printInfo();
    delete advisor;
}

void Interface::addStudent() {
    int id = promptForStudent(1);

    string name;
    cout << "Enter in the Student Name" << endl;
    cin >> name;

    string level;
    cout << "Enter in the Class Level" << endl;
    cin >> level;

    string major;
    cout << "Enter in the Major" << endl;
    cin >> major;

    double gpa;
    cout << "Enter in the GPA" << endl;
    cin >> gpa;

    int advisorid = promptForFaculty(0);
    // add student id to advisor's advisees field
    Faculty &advisor = *faculty->getByID(advisorid);
    advisor.addStudent(id);

    Student *newStudent = new Student(id, name, level, major, gpa, advisorid);
    students->insert(newStudent);
}

void Interface::deleteStudent(int id) {
    Student &student = *students->getByID(id);
    int advisor = student.getAdvisor();
    removeAdvisee(id, advisor);
    students->removeByID(id);
}

void Interface::addFaculty() {
    int id = promptForFaculty(1);

    string name;
    cout << "Please enter in the faculty name" << endl;
    cin >> name;

    string level;
    cout << "Please enter in the faculty level" << endl;
    cin >> level;

    string dept;
    cout << "Please enter in the department" << endl;
    cin >> dept;

    Faculty *newFaculty = new Faculty(id, name, level, dept);
    faculty->insert(newFaculty);
}

void Interface::deleteFaculty(int id) {
    cout << "Which Advisor would you like to switch the current Advisor's students to?" << endl;
    Faculty &newAdvisor = *faculty->getByID(promptForFaculty(0));
    Faculty &oldAdvisor = *faculty->getByID(id);

    DblList<int> *advisees = oldAdvisor.getAdvisees();
    while (!advisees->isEmpty()) {
        int studentID = advisees->removeBack();
        changeAdvisor(studentID, newAdvisor.getid());
    }
    delete advisees;
    faculty->removeByID(oldAdvisor.getid());
}

void Interface::changeAdvisor(int studentid, int facultyid) {
    removeAdvisee(studentid, facultyid);
    Faculty &advisor = *faculty->getByID(facultyid);
    advisor.addStudent(studentid);
    Student &student = *students->getByID(studentid);
    student.changeAdvisor(facultyid);
}

void Interface::removeAdvisee(int studentid, int facultyid) {
    Faculty &advisor = *faculty->getByID(facultyid);
    advisor.removeStudent(studentid);
    Student &student = *students->getByID(studentid);
    student.changeAdvisor(-1);
}

int Interface::promptForStudent(int flag) {
    int id;
    cout << "Enter in the Student ID" << endl;
    cin >> id;
    if (flag == 0) {
        while (!students->containsByID(id)) {
            cout << "That Student ID does not exist. Enter in a valid ID." << endl;
            cin >> id;
        }
    }
    else if (flag == 1) {
        while (students->containsByID(id)) {
            cout << "That Student ID already exists. Enter in a valid ID." << endl;
            cin >> id;
        }
    }
    return id;
}

int Interface::promptForFaculty(int flag) {
    int id;
    cout << "Enter in the Faculty ID" << endl;
    cin >> id;
    if (flag == 0) {
        while (!faculty->containsByID(id)) {
            cout << "That Faculty ID does not exist. Enter in a valid ID." << endl;
            cin >> id;
        }
    }
    else if (flag == 1) {
        while (faculty->containsByID(id)) {
            cout << "That Faculty ID already exists. Enter in a valid ID." << endl;
            cin >> id;
        }
    }
    return id;}

void Interface::writeToFile() {
    students->printToFile();
    faculty->printToFile();
}