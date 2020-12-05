#pragma once
#include "Database.h"
#include <fstream>
using namespace std;

class FileIO{
public:

    // Files for our trees
    static const string facultyFileString;
    static const string studentFileString;


    // Methods
    static void WriteStuTree(BST<Student*>* mS, string sFileName = studentFileString);
    static void WriteFacTree(BST<Faculty*>* mF, string fFileName = facultyFileString);
    static BST<Student*>* ReadStuTree(string sFileName = studentFileString);
    static BST<Faculty*>* ReadFacTree(string fFileName = facultyFileString);
    static BST<Student*>* FromStuTree(ifstream& inputFile);
    static BST<Faculty*>* FromFacTree(ifstream& inputFile);
    static void FromStuTreeNode(BST<Student*>* bst, TreeNode<Student*>* node, ifstream& inputFile);
    static void FromFacTreeNode(BST<Faculty*>* bst, TreeNode<Faculty*>* node, ifstream& inputFile);
    static BST<Faculty*>* readFacultyBackup(int backupNum);
    static BST<Student*>* readStudentBackup(int backupNum);
    static void BackupFacultyTree(BST<Faculty*>* facultyTree, int backupFolderNum);
    static void BackupStudentTree(BST<Student*>* studentTree, int backupFolderNum);

};
