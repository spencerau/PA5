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
A faculty member can’t have an advisee not in the student table. If a faculty member is deleted, then their advisees must have their advisors 
changed, etc. Your commands will be responsible for maintaining referential integrity. If a user issues a command that would break referential 
integrity, you should warn them and abort the command, or execute the command and fix any violations as appropriate.
 
After each command is executed, the menu should be displayed again, and the user allowed to continue.
If the user selects the Exit option, prior to quitting your program should create a file, named runLog.txt, which contains the information of both 
tables at the time the program was terminated. (This is the information from option 1 and option 2, 
just printed to the file instead of the terminal).
*/

#include "Interface.h"
#include <iostream>
#include <string>

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
    string line;

    Faculty *linstead = new Faculty(000, "Linstead", "Assist Prof", "Code Monkey Dept");
    faculty->insert(linstead);
    Faculty *stevens = new Faculty(111, "Stevens", "Code Monkey", "Computer Science");
    faculty->insert(stevens);

    Student *student1 = new Student(12345, "Student1", "Freshman", "CS", 0.5, 000);
    students->insert(student1);
    linstead->addStudent(12345);

    Student *student2 = new Student(678910, "Student2", "Senior", "Code Monkey", 0.6, 111);
    students->insert(student2);
    stevens->addStudent(678910);

    Student *student3 = new Student(333, "Student3", "code monkey", "test major 12345", 1.1, 000);
    students->insert(student3);
    linstead->addStudent(333);

    while (result != 11) {
        printOptions();
        getline(cin, line);
        result = stoi(line);
        // flag: 0 = DNE, 1 = exists already
        switch (result) {
            case 1:
            {
                printAllStudents();
                break;
            }
            case 2:
            {
                printAllFaculty();
                break;
            }
            case 3:
            {
                if (!isEmpty(0)) {
                    cout << "Display Student:" << endl;
                    id = promptForStudent(0);
                    printStudent(id);
                }
                break;
            }
            case 4:
            {
                if (!isEmpty(1)) {
                    cout << "Display Faculty" << endl;
                    id = promptForFaculty(0);
                    printFaculty(id);
                }
                break;
            }
            case 5:
            {
                if (!isEmpty(1)) addStudent();
                break;
            }
            case 6:
            {
                if (!isEmpty(0)) {
                    id = promptForStudent(0);
                    deleteStudent(id);
                }
                break;
            }
            case 7:
            {
                addFaculty();
                break;
            }
            case 8: // Delete a faculty member given the id.
            {
                if (!isEmpty(1)) {
                    id = promptForFaculty(0);
                    deleteFaculty(id);
                }
                break;
            }
            case 9: // Change a student’s advisor given the student id and the new faculty id.
            {
                if (!isEmpty(0)) {
                    studentid = promptForStudent(0);
                    if (!isEmpty(1)) {
                        facultyid = promptForFaculty(0);
                        if (faculty->getSize() == 1) cout << "Error: There is only one advisor.\n" << endl;
                        else changeAdvisor(studentid, facultyid);
                    }
                }
                break;
            }
            case 10: // Remove an advisee from a faculty member given the ids
            {
                if (!isEmpty(0)) {
                    studentid = promptForStudent(0);
                    if (!isEmpty(1)) {
                        facultyid = promptForFaculty(0);
                        removeAdvisee(studentid, facultyid);
                    }
                }
                break;
            }
            case 11: // exit and print out to runLog.txt
            {
                writeToFile();
                break;
            }
            default:
            {
                cout << "That option is not valid. Please choose an option between 1 and 11." << endl;
                break;
            }
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
    //delete student;
}

void Interface::printFaculty(int id) {
    Faculty *advisor = faculty->getByID(id);
    advisor->printInfo();
    //delete advisor;
}

void Interface::addStudent() {
    int id = promptForStudent(1);

    string name;
    cout << "Enter in the Student Name" << endl;
    getline(cin, name);

    string level;
    cout << "Enter in the Class Level" << endl;
    getline(cin, level);

    string major;
    cout << "Enter in the Major" << endl;
    getline(cin, major);

    double gpa;
    cout << "Enter in the GPA" << endl;
    string line;
    getline(cin, line);
    gpa = stod(line);

    int advisorid = promptForFaculty(0);
    // add student id to advisor's advisees field
    Faculty &advisor = *faculty->getByID(advisorid);
    advisor.addStudent(id);

    cout << endl;
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
    getline(cin, name);

    string level;
    cout << "Please enter in the faculty level" << endl;
    getline(cin, level);

    string dept;
    cout << "Please enter in the department" << endl;
    getline(cin, dept);

    cout << endl;
    Faculty *newFaculty = new Faculty(id, name, level, dept);
    faculty->insert(newFaculty);
}

void Interface::deleteFaculty(int id) {
    cout << "Which Advisor would you like to switch the current Advisor's students to?" << endl;
    Faculty *newAdvisor = faculty->getByID(promptForFaculty(0));
    Faculty *oldAdvisor = faculty->getByID(id);

    DblList<int> *advisees = oldAdvisor->getAdvisees();
    while (!advisees->isEmpty()) {
        int studentID = advisees->removeBack();
        changeAdvisor(studentID, newAdvisor->getid());
    }
    delete advisees;
    faculty->removeByID(oldAdvisor->getid());
}

void Interface::changeAdvisor(int studentid, int facultyid) {
    removeAdvisee(studentid, facultyid);
    Faculty *advisor = faculty->getByID(facultyid);
    advisor->addStudent(studentid);
    Student *student = students->getByID(studentid);
    student->changeAdvisor(facultyid);
}

void Interface::removeAdvisee(int studentid, int facultyid) {
    Faculty *advisor = faculty->getByID(facultyid);
    advisor->removeStudent(studentid);
    Student &student = *students->getByID(studentid);
    student.changeAdvisor(-1);
}

int Interface::promptForStudent(int flag) {
    int id;
    string line;
    cout << "Enter in the Student ID" << endl;
    getline(cin, line);
    if (flag == 0) {
        while (!students->containsByID(id)) {
            cout << "That Student ID does not exist. Enter in a valid ID." << endl;
            string line;
            getline(cin, line);
            id = stoi(line);    
        }
    }
    else if (flag == 1) {
        while (students->containsByID(id)) {
            cout << "That Student ID already exists. Enter in a valid ID." << endl;
            string line;
            getline(cin, line);
            id = stoi(line);  
        }
    }
    return id;
}

int Interface::promptForFaculty(int flag) {
    int id;
    string line;
    cout << "Enter in the Faculty ID" << endl;
    getline(cin, line);
    id = stoi(line); 
    if (flag == 0) {
        while (!faculty->containsByID(id)) {
            cout << "That Faculty ID does not exist. Enter in a valid ID." << endl;
            string line;
            getline(cin, line);
            id = stoi(line); 
        }
    }
    else if (flag == 1) {
        while (faculty->containsByID(id)) {
            cout << "That Faculty ID already exists. Enter in a valid ID." << endl;
            string line;
            getline(cin, line);
            id = stoi(line); 
        }
    }
    return id;}

void Interface::writeToFile() {
    students->printToFile();
    faculty->printToFile();
}

bool Interface::isEmpty(int flag) {
    if (flag == 0) {
        if (students->getSize() == 0) {
            cout << "There are currently no students. Operation aborted" << endl;
            cout << endl;
            return true;
        } else return false;
    }
    if (flag == 1) {
        if (faculty->getSize() == 0) {
            cout << "There are currently no faculty. Operation aborted" << endl;
            cout << endl;
            return true;
        } else return false;
    }
}
