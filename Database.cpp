#include <iostream>
#include "File.h"
#include <string>


using namespace std;

// Constructor
Database::Database(){
  studentMaster = FileIO::ReadStuTree();
  facultyMaster = FileIO::ReadFacTree();
  constant = 0;
}

// Destructor
Database::~Database(){
  FileIO::WriteStuTree(studentMaster);
  FileIO::WriteFacTree(facultyMaster);
}

//Locates faculty with the specified ID in the facultyMaster tree
Faculty* Database::FindFacultyID(int facID){
  return facultyMaster->printNode(facID);
}


//Finds a students advisor based on their ID and returns that advisors info
Faculty* Database::RetrieveStudentAdvisorInfo(int studID){
  Student* s = FindStudentID(studID);
  int advisorid = s->advisorID;
  return FindFacultyID(advisorid);
}

// Prints all faculty and all of their info as well
void Database::PrintFaculty(){
  facultyMaster->printOutTree();
}

// Adds a new faulty member to facultyMaster tree
void Database::AddFaculty(Faculty* f){
  facultyMaster->insert(f->facID, f);
}

// Deletes a faculty member from the facultyMaster tree based on the faculty ID
Faculty* Database::DeleteFaculty(int facID){
  bool wasItDeleted = false;
  Faculty* deletedFaculty = facultyMaster->printNode(facID);
  wasItDeleted = facultyMaster->deleteNode(facID);
  if(wasItDeleted){
    cout << "Faculty was Deleted Successfully" << endl;
    return deletedFaculty;
  }
  else{
    cout << "Could not Delete the Faculty." << endl;
    return NULL;
  }
}

// Changes a students faculty advisor from ID to a different faculty advisor from ID
void Database::ChangeStudentsFacultyID(int stuID, int facID){
  // student whos faculty advisor we wish to change
  Student* oldStudent = studentMaster->printNode(stuID);
  int oldAdvisor = oldStudent -> advisorID;
  Faculty* oldf = facultyMaster->printNode(oldAdvisor);

  // Here we are removing a student from their current faculty advisors list
  //changin them to have a new advisor
  // Then adding them to the advisor list of their new faculty advisor
  int deletedId = oldf->facAdvisees->Remove(stuID)->data;
  oldStudent -> advisorID = facID;
  Faculty* newFaculty = facultyMaster->printNode(facID);
  newFaculty->facAdvisees->insertAtBack(stuID);
  cout << "Advisor has been changed." << endl;
}


// //Retrieves the faculty information from the database user
Faculty* Database::RetrieveFacultyInfo(){
  bool correctinfo = true;
  int iD = 0;
  string name;
  string status;
  string department;

  cout << "Enter Faculty's ID Number: " << endl;
  //making sure ID number is valid
  try{
  cin >> iD;
  }
  catch(runtime_error e){
    cout << "This is not a valid ID number!" << endl;
    try{
      cin >> iD;
    }
    catch(runtime_error error2){
      correctinfo = false;
    }
  }
  cout << "Enter Faculty's name: " << endl;
  cin.ignore();
  getline(cin, name);
  cout << "Enter Faculty's status: " << endl;
  getline(cin, status);
  cout << "Enter Faculty's department: " << endl;
  getline(cin, department);

  //we can now make a new faculty object using the correct info entered by the user
  if(correctinfo){
    Faculty* fac = new Faculty(iD, name, status, department);
    return fac;
  }
  else{
    return NULL;
  }
}

// Backs up the facultyMaster tree
void Database::BackingUpFaculty(){
  constant = constant % 5;
  FileIO::BackupFacultyTree(facultyMaster, constant);
}

// Bring back the previous facultyMaster tree
void Database::BringBackFaculty(){
  constant = (constant % 5) - 1;
  facultyMaster = FileIO::readFacultyBackup(constant);
}

//Prints the student tree
void Database::PrintStudents(){
  studentMaster->printOutTree();
}


//Adds a new student
//also adds student to the advisors advisees list
void Database::AddStudent(Student* s){
  studentMaster->insert(s->studID, s);
  int idAdvisor = s->advisorID;
  Faculty* advisor = facultyMaster->printNode(idAdvisor);
  advisor->facAdvisees->insertAtBack(s->studID);
}


//Retrieves the student information from the database user
Student* Database::RetrieveStudentInfo(){
  int iD;
  string name;
  string grade;
  string major;
  double gpa;
  int advisorID;
  cout << "Enter the Student's ID Number: " << endl;
  cin >> iD;
  cout << "Enter the Student's name: " << endl;
  cin.ignore();
  getline(cin, name);
  cout << "Enter Student's grade level: " << endl;
  getline(cin, grade);
  cout << "Enter Student's major: " << endl;
  getline(cin, major);
  cout << "Enter Student's GPA: " << endl;
  cin >> gpa;
  cout << "Enter Student's Advisor's ID Number: " << endl;
  cin >> advisorID;
  // checking to see if the faculty ID actually exists
  while(!facultyMaster->Search(advisorID)){
    cout << "The advisor ID you entered does not exist. Try again." << endl;
    cin >> advisorID;
  }
  // new student made with info entered above
  Student* stu = new Student(iD, name, grade, major, gpa, advisorID);
  return stu;
}


//Locates student with the specified ID in the studenMaster tree
Student* Database::FindStudentID(int studID){
  return studentMaster->printNode(studID);
}

// Locates a student with the specified ID and deletes them fron the studentMaster tree
Student* Database::DeleteStudent(int studID){
  bool wasItDeleted = false;
  Student* deletedStudent = studentMaster->printNode(studID);
  int advisorid = deletedStudent->advisorID;

  // using the advisor ID to also take this student off the advisees list
  Faculty* advisor = facultyMaster->printNode(advisorid);
  advisor->facAdvisees->Remove(studID);
  wasItDeleted = studentMaster->deleteNode(studID);
  if(wasItDeleted){
    cout << "Student was Deleted Successfully" << endl;
  }
  else{
    cout << "Could not Delete the Student" << endl;
    return NULL;
  }
}

// Backs up the studentMaster tree
void Database::BackingUpStudent(){
  constant = constant % 5;
  FileIO::BackupStudentTree(studentMaster, constant);
}

// Bring Back the previous studentMaster tree
void Database::BringBackStudent(){
  constant = (constant % 5) - 1;
  studentMaster = FileIO::readStudentBackup(constant);
}
