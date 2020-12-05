#include <iostream>
#include "BST.h"
using namespace std;

class Student{
public:

    // Constructor
    Student();

    // Overloaded Constructor
    Student(int id, string name, string grade, string major, double gpa, int advisor);

    // Variables
    string studName;
    string studMajor;
    double studGPA;
    int studID;
    string gradeLevel;
    int advisorID;


    // Methods
    void toString();
    void ShowStudentInfo(Student* s);


    // Overloaded Ops
    bool operator>(Student stud);
    bool operator<(Student stud);
    bool operator!=(Student stud);
    bool operator=(Student stud);
    friend ostream& operator<<(ostream& fileStream, Student& stud);

};
