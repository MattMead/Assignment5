#include <iostream>
#include "File.h"
using namespace std;

int main(){
  // New database object
  Database db = Database();
  bool keepGoing = true;

  while(keepGoing){
    // displaying menu and prompting user for a choice
    int choice = 0;
    cout << "Select what you want to do: " << endl;
    cout << endl;
    cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the students id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "6. Given a faculty id, print ALL the names and info of his/her advisees." << endl;
    cout << "7. Add a new student" << endl;
    cout << "8. Delete a student given the id" << endl;
    cout << "9. Add a new faculty member" << endl;
    cout << "10. Delete a faculty member given the id" << endl;
    cout << "11. Change a student’s advisor given the student id and the new faculty id." << endl;
    cout << "12. Remove an advisee from a faculty member given the ids" << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;
    cout << endl;

    cin >> choice;

    // Prints out all students and their information
    if(choice == 1){
      db.studentMaster->printOutTree();
    }

    // Prints out all faculty and their information
    else if(choice == 2){
      db.facultyMaster->printOutTree();
    }

    // Displays a given student's information from their student ID
    else if(choice == 3){
      cout << "Enter the ID number of the student you are searching for: " << endl;
      int IDnum;
      cin >> IDnum;
      Student* ourStudent = db.FindStudentID(IDnum);
      ourStudent->ShowStudentInfo(ourStudent);
    }

    // Displays a given facultys information from their faculty ID
    else if(choice == 4){
      cout << "Okay, enter the ID number of the faculty you are looking for: " << endl;
      int IDnum;
      cin >> IDnum;
      Faculty* ourFaculty = db.FindFacultyID(IDnum);
      ourFaculty->ShowFacultyInfo(ourFaculty);
    }

    // Using student ID to find that students advisor and print out that advisor's information
    else if(choice == 5){
      int stuID;
      cout << "Enter student's ID number: " << endl;
      cin >> stuID;
      Faculty* advisor = db.RetrieveStudentAdvisorInfo(stuID);
      advisor->toString();
    }

    // Using faculty ID to display the information of their advisees
    else if(choice == 6){
      cout << "Enter the Faculty ID: " << endl;
      int facID;
      cin >> facID;
      while(!db.facultyMaster -> Search(facID)){
        cout << "This Advisor ID Number is not valid. Try again. " << endl;
        cin >> facID;
      }
      // Retrieving the facult member from the facultyMaster tree
      // Then going through the faculty's advisee list to display all students information
      Faculty* outF = db.facultyMaster->printNode(facID);
      DoubleListNode<int>* current = outF->facAdvisees->front;
      for(int i = 0; i < outF->facAdvisees->getSize(); ++i){
        int stuId = current->data;
        Student* outS = db.studentMaster->printNode(stuId);
        outS->ShowStudentInfo(outS);
        current = current->next;
      }
    }

    // Adding a student to our studentMasterTree
    else if(choice == 7){
      Student* myStu = db.RetrieveStudentInfo();
      db.AddStudent(myStu);
      // backup the tree after we make any sort modification so we can go back if needed
      db.BackingUpStudent();
      db.BackingUpFaculty();
      db.constant++;
    }

    // deleting a student from the studentMaster tree
    else if(choice == 8){
      int stuID = 0;
      cout << "Enter the ID of the student you want to delete: " << endl;
      cin >> stuID;
      // making sure the student exists
      while(!db.studentMaster -> Search(stuID)){
        cout << "Student ID number could not be found. Try again." << endl;
        cin >> stuID;
      }
      db.DeleteStudent(stuID);
      db.BackingUpStudent();
      db.BackingUpFaculty();
      db.constant++;
    }

    // Adds a new faculty member to the facultyMaster Tree
    else if(choice == 9){
      Faculty* fac = db.RetrieveFacultyInfo();
      db.AddFaculty(fac);
      // backing up both facultyMaster and studentMaster trees after every modification
      db.BackingUpStudent();
      db.BackingUpFaculty();
      db.constant++;
    }

    // Deletes a faculty member from the facultyMaster tree
    else if(choice == 10){
      int facID = 0;
      cout << "Enter the ID of the faculty member you want to delete: " << endl;
      cin >> facID;
      //making sure the faulty ID exists
      while(!db.facultyMaster -> Search(facID)){
        cout << "Faculty ID number not found. Try again." << endl;
        cin >> facID;
      }
      Faculty* ourFac = db.facultyMaster->printNode(facID);
      int stuID = 0;

      // Here we have to assign all the advisees of that original advisor to a new advisor
      // We will assign them to the root of their facultyMaster tree
      DoubleListNode<int>* current = ourFac->facAdvisees->front;
      Faculty* fRoot = db.facultyMaster->root->value;
      if(ourFac == fRoot){
        db.DeleteFaculty(facID);
      }
      for(int i = 0; i < ourFac->facAdvisees->getSize(); ++i){
        stuID = current->data;
        Student* stuNode = db.studentMaster->printNode(stuID);
        stuNode->advisorID = fRoot->facID;
        fRoot->facAdvisees->insertAtBack(stuNode->studID);
        current = current->next;
      }
      if(ourFac!=fRoot){
        db.DeleteFaculty(facID);
      }
      //backing up tree
      db.BackingUpStudent();
      db.BackingUpFaculty();
      db.constant++;
    }

    // Changing a student to another advisor
    else if(choice == 11){
      int stuID;
      int facID;
      cout << "Enter the Student ID: " << endl;
      cin >> stuID;
      cout << "Enter new Advisor's ID: " << endl;
      cin >> facID;

      // need to make sure the student already exists
      while(!db.studentMaster -> Search(stuID)){
        cout << "This is not a valid Student ID Number. Try again. " << endl;
        cin >> stuID;
      }
      // need to make sure that the faculty exists as well
      while(!db.facultyMaster -> Search(facID)){
        cout << "This is not a valid Advisor ID Number. Try again. " << endl;
        cin >> facID;
      }
      db.ChangeStudentsFacultyID(stuID, facID);

      // backing up the trees again
      db.BackingUpStudent();
      db.BackingUpFaculty();
      db.constant++;
    }

    // Remove a student from their advisors list
    else if(choice == 12){
      int stuID;
      int facID;
      cout << "Enter the Student ID: " << endl;
      cin >> stuID;
      cout << "Enter the Advisor ID: " << endl;
      cin >> facID;
      // need to make sure student exists
      while(!db.studentMaster -> Search(stuID)){
        cout << "This is not a valid Student ID Number. Try again. " << endl;
        cin >> stuID;
      }
      // need to make sure student exists
      while(!db.facultyMaster -> Search(facID)){
        cout << "This is not a valid Faculty ID Number. Try again. " << endl;
        cin >> facID;
      }

      // remove student from advisor's list and making the root the students new advisor
      Faculty* ourFac = db.facultyMaster->printNode(facID);
      ourFac->facAdvisees->deletePosition(ourFac->facAdvisees->Find(stuID));
      Student* stuNode = db.studentMaster->printNode(stuID);
      Faculty* fRoot = db.facultyMaster->root->value;
      stuNode->advisorID = fRoot->facID;
      fRoot->facAdvisees->insertAtBack(stuNode->studID);


      // backing up ther faculty and student trees
      db.BackingUpStudent();
      db.BackingUpFaculty();
      db.constant++;
    }

    // Rollback
    else if(choice == 13){
      db.BringBackFaculty();
      db.BringBackStudent();
      cout << "Rolling back the database." << endl;
    }

    // Quit
    else if (choice == 14){
      keepGoing = false;
    }
    else{
      cout << "Not a valid option. Quiting Now." << endl;
      keepGoing = false;
    }
  }
  db.~Database();

}
