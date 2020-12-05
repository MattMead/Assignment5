#include <iostream>
#include "Student.h"
using namespace std;

// Student Constructor
Student::Student(){
    studID = 0;
    studName = "";
    gradeLevel = "";
    studMajor = "";
    studGPA = 0.0;
    advisorID = 0;
}

// Overloaded Student Constructor
Student::Student(int id, string name, string grade, string major, double gpa, int advisor){
    studID = id;
    studName = name;
    studMajor = major;
    studGPA = gpa;
    gradeLevel = grade;
    advisorID = advisor;
}

// Prints our all of the student info
void Student::toString(){
    cout << "Student ID: " << studID << endl;
    cout << "Student Name: " << studName << endl;
    cout << "Student Grade Level: " << gradeLevel << endl;
    cout << "Student Major: " << studMajor << endl;
    cout << "Student GPA: " << studGPA << endl;
    cout << "Student Advisor ID Number: " << advisorID << endl;
}

// Displays all the desrciptors of a student
void Student::ShowStudentInfo(Student* s){
    cout << "Student ID: " << s->studID << endl;
    cout << "Student Name: " << s->studName << endl;
    cout << "Student Grade Level: " << s->gradeLevel << endl;
    cout << "Student Major: " << s->studMajor << endl;
    cout << "Student GPA: " << s->studGPA << endl;
    cout << "Student Advisor ID Number: " << s->advisorID << endl;
}

// Overloaded > Op
bool Student::operator<(Student stud){
    if(stud.studID > this -> studID){
        return true;
    }
    else{
        return false;
    }
}

// Overloaded < Op
bool Student::operator>(Student stud){
    if(stud.studID < this -> studID){
        return true;
    }
    else{
        return false;
    }
}

// Overloaded != Op
bool Student::operator!=(Student stud){
    if(stud.studID!= this -> studID){
        return true;
    }
    else{
        return false;
    }
}


// Overloaded Equals Op
bool Student::operator=(Student stud){
    if(stud.studID == this -> studID){
        return true;
    }
    else{
        return false;
    }
}


//Overloads << Op
ostream& operator<<(ostream& fileStream, Student& stud){
    fileStream << stud.studID << endl;
    fileStream << stud.studName << endl;
    fileStream << stud.gradeLevel << endl;
    fileStream << stud.studMajor << endl;
    fileStream << stud.studGPA << endl;
    fileStream << stud.advisorID << endl;
    return fileStream;
}
