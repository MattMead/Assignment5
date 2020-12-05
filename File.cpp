#include "File.h"
#include <stdio.h>
#include <fstream>
using namespace std;

// making the files that will have both the student tree and faculty tree
const string FileIO::studentFileString = "StudentTable.txt";
const string FileIO::facultyFileString = "FacultyTable.txt";


// Writes the studentMaster tree to the file
void FileIO::WriteStuTree(BST<Student*>* sM, string sFileName){
    sM->TreeToFile(sFileName);
}

// Writes the facultyMaster tree to the file
void FileIO::WriteFacTree(BST<Faculty*>* fM, string fFileName){
    fM->TreeToFile(fFileName);
}

// Reads in the tree from the student file
BST<Student*>* FileIO::ReadStuTree(string sFileName){
    ifstream fileStream;
    fileStream.open(sFileName);
    BST<Student*>* studentTree;
    if(fileStream.is_open() == false){
        return new BST<Student*>();
    }
    studentTree = FromStuTree(fileStream);
    fileStream.close();
    return studentTree;
}

// Reads in the tree from the faculty file
BST<Faculty*>* FileIO::ReadFacTree(string fFileName){
    ifstream fileStream;
    fileStream.open(fFileName);
    BST<Faculty*>* facultyTree;
    if(fileStream.is_open() == false){
        return new BST<Faculty*>();
    }
    facultyTree = FromFacTree(fileStream);
    fileStream.close();
    return facultyTree;
}


// Brings back the studentMaster tree from the file
BST<Student*>* FileIO::FromStuTree(ifstream& inputFile){
    BST<Student*>* newTree = new BST<Student*>();
    string line;
    getline(inputFile, line);
    FromStuTreeNode(newTree, newTree->root, inputFile);
    return newTree;
}

//  method that reads the data from the file
BST<Faculty*>* FileIO::FromFacTree(ifstream& inputFile){
    BST<Faculty*>* newTree = new BST<Faculty*>();
    string line;
    getline(inputFile, line);
    FromFacTreeNode(newTree, newTree->root, inputFile);
    return newTree;
}

// Goes through student file and adds to the studentMaster tree
void FileIO::FromStuTreeNode(BST<Student*>* bst, TreeNode<Student*>* node, ifstream& inputFile){
    const string endNode = "||";
    int key;
    int id;
    string name;
    string grade;
    string major;
    double gpa;
    int advisorid;
    string input = "null";

    getline(inputFile, input);
    while(input == ""){
        getline(inputFile, input);
        if(inputFile.eof() == true){
            return;
        }
    }

    if(input == endNode){
        return;
    }

    key = stoi(input);
    getline(inputFile, input);
    if(input == endNode)
        return;

    id = stoi(input);
    getline(inputFile, input);
    if(input == endNode){
        return;
    }

    name = input;
    getline(inputFile, input);
    if(input == endNode){
        return;
    }

    grade = input;
    getline(inputFile, input);
    if(input == endNode){
        return;
    }

    major = input;
    getline(inputFile, input);
    if(input == endNode){
        return;
    }

    gpa = stod(input);
    getline(inputFile, input);
    if(input == endNode){
        return;
    }

    advisorid = stoi(input);
    Student* stu = new Student(id, name, grade, major, gpa, advisorid);
    node = new TreeNode<Student*>(id, stu);
    bst->insert(id, stu);
    FromStuTreeNode(bst, node->left, inputFile);
    FromStuTreeNode(bst, node->right, inputFile);
}


// Goes through student file and adds to the facultyMaster tree
void FileIO::FromFacTreeNode(BST<Faculty*>* bst, TreeNode<Faculty*>* node, ifstream& inputFile){
    const string endNode = "||"; // marker to end a faculty object
    int key;
    int id;
    string name;
    string status;
    string department;
    string input = "null";

    getline(inputFile, input);
    while(input == ""){
        getline(inputFile, input);
        if(inputFile.eof() == true){
            return;
        }
    }

    if(input == endNode){
        return;
    }

    key = stoi(input);
    getline(inputFile, input);
    if(input == endNode){
        return;
    }

    id = stoi(input);
    getline(inputFile, input);
    if(input == endNode){
        return;
    }

    name = input;
    getline(inputFile, input);
    if(input == endNode){
        return;
    }

    status = input;
    getline(inputFile, input);
    if(input == endNode){
        return;
    }

    department = input;
    Faculty* newFaculty = new Faculty(id, name, status, department);
    node = new TreeNode<Faculty*>(id, newFaculty);

    do{
        int tempid = 0;
        getline(inputFile, input);
        if(input == endNode){
            return;
        }

        try{
            tempid = stoi(input);
        }
        catch(invalid_argument e){
            break;
        }

        newFaculty->facAdvisees->insertAtBack(tempid);
    }
    while(input != "");
    bst->insert(id, newFaculty);
    FromFacTreeNode(bst, node->left, inputFile);
    FromFacTreeNode(bst, node->right, inputFile);
}



// Brings back previous studentMaster tree
BST<Student*>* FileIO::readStudentBackup(int backUpNum){
    string studentBackUp = "StudentBackUpNum" + to_string(backUpNum);
    BST<Student*>* studentTreeBack = new BST<Student*>;
    studentTreeBack = ReadStuTree(studentBackUp);
    return studentTreeBack;
}

// Brings back previous facultyMaster tree
BST<Faculty*>* FileIO::readFacultyBackup(int backUpNum){
    string facultyBackUp = "FacultyBackUpNum" + to_string(backUpNum);
    BST<Faculty*>* facultyTreeBack = new BST<Faculty*>;
    facultyTreeBack = ReadFacTree(facultyBackUp);
    return facultyTreeBack;
}

// Rollback function for studentMaster Tree
void FileIO::BackupStudentTree(BST<Student*>* studentTree, int backupFolder){
    string backupNumString = to_string(backupFolder);
    string studentBackUpString = "StudentBackUpNum" + backupNumString;
    WriteStuTree(studentTree, studentBackUpString);
}

// Rollback function for facultyMaster Tree
void FileIO::BackupFacultyTree(BST<Faculty*>* facultyTree, int backupFolder){
    string backupNumString = to_string(backupFolder);
    string facultyBackUpString = "FacultyBackUpNum" + backupNumString;
    WriteFacTree(facultyTree, facultyBackUpString);
}
