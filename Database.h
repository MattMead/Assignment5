#include <iostream>
#include "Faculty.h"

using namespace std;

class Database{
public:
    //Student Tree
    BST<Student*> *studentMaster;

    // Faculty Tree
    BST<Faculty*> *facultyMaster;

    //Constructor
    Database();

    //Destructor
    ~Database();

    // Variables
    int constant;

    // Student Methods
    void PrintStudents();
    void AddStudent(Student* s);
    Student* RetrieveStudentInfo();
    Student* FindStudentID(int studentID);
    Student* DeleteStudent(int studentID);
    void BackingUpStudent();
    void BringBackStudent();

    // faculty Methods
    void PrintFaculty();
    void AddFaculty(Faculty* f);
    Faculty* RetrieveFacultyInfo();
    Faculty* FindFacultyID(int facultyID);
    Faculty* DeleteFaculty(int facultyID);
    Faculty* RetrieveStudentAdvisorInfo(int studentID);
    void ChangeStudentsFacultyID(int stuID, int facID);
    void BackingUpFaculty();
    void BringBackFaculty();

};
