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

#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "Student.h"
#include "Faculty.h"
#include "ScapegoatST.h"

using namespace std;

class Interface {
public:
    Interface();
    ~Interface();
    void run();
    
private:
    ScapegoatST<Student*> *students;
    ScapegoatST<Faculty*> *faculty;

    void printOptions();
    void printAllStudents();
    void printAllFaculty();
    void printStudent(int id);
    void printFaculty(int id);
    void addStudent();
    void deleteStudent(int id);
    void addFaculty();
    void deleteFaculty(int id);
    void changeAdvisor(int studentid, int facultyid);
    void removeAdvisee(int studentid, int facultyid);
    int promptForStudent(int flag);
    int promptForFaculty(int flag);
    void writeToFile();
    bool isEmpty(int flag);
};


#endif