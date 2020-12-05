#include <iostream>
#include "Student.h"
using namespace std;

class Faculty{
public:

    // Constructor
    Faculty();

    // Overloaded Constructor
    Faculty(int id, string name, string status, string department);

    // Variables
    string facName;
    int facID;
    string facStatus;
    string facDepartment;
    DoubleLinkedList<int> *facAdvisees;

    // Methods
    void toString();
    void ShowFacultyInfo(Faculty* f);


    // Overloaded Ops
    bool operator>(Faculty fac);
    bool operator<(Faculty fac);
    bool operator!=(Faculty fac);
    bool operator=(Faculty fac);
    friend ostream& operator<<(ostream& fileStream, Faculty& fac);

};
