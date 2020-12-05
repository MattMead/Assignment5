#include <iostream>
#include "Faculty.h"
using namespace std;

// Constructor
Faculty::Faculty(){
    facName = "";
    facID = 0;
    facStatus = "";
    facDepartment = "";
    facAdvisees = new DoubleLinkedList<int>();
}

// Overloaded Constructor
Faculty::Faculty(int id, string name, string status, string department){
    facName = name;
    facID = id;
    facStatus = status;
    facDepartment = department;
    facAdvisees = new DoubleLinkedList<int>();
}

//method to display the faculty and all of their information
void Faculty::ShowFacultyInfo(Faculty* f){
    cout << "Faculty ID: " << f->facID << endl;
    cout << "Faculty Name: " << f->facName << endl;
    cout << "Faculty Status: " << f->facStatus << endl;
    cout << "Faculty Department: " << f->facDepartment << endl;
    cout << "Advisees: ";
    DoubleListNode<int> *current = facAdvisees->front;
    for(int i = 0; i < facAdvisees->getSize(); ++i){
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Prints all of the faculty information
void Faculty::toString(){
    cout << "Faculty ID: " << facID << endl;
    cout << "Faculty Name: " << facName << endl;
    cout << "Faculty Status: " << facStatus << endl;
    cout << "Faculty Department: " << facDepartment << endl;
    cout << "Advisees: ";
    DoubleListNode<int> *current = facAdvisees->front;
    for(int i = 0; i < facAdvisees->getSize(); ++i){
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Overloaded < Op
bool Faculty::operator<(Faculty fac){
    if(fac.facID > this -> facID){
        return true;
    }
    else{
        return false;
    }
}

// Overloaded > Op
bool Faculty::operator>(Faculty fac){
    if(fac.facID < this -> facID){
        return true;
    }
    else{
        return false;
    }
}

// Overloaded != Op
bool Faculty::operator!=(Faculty fac){
    if(fac.facID!= this -> facID){
        return true;
    }
    else{
        return false;
    }
}

// Overloaded Equals Op
bool Faculty::operator=(Faculty fac){
    if(fac.facID == this -> facID){
        return true;
    }
    else{
        return false;
    }
}

// Overloaded << Op
ostream& operator<<(ostream& fileStream, Faculty& fac){
    fileStream << fac.facID << endl;
    fileStream << fac.facName << endl;
    fileStream << fac.facStatus << endl;
    fileStream << fac.facDepartment << endl;
    fileStream << *(fac.facAdvisees) << endl;
    return fileStream;
}
