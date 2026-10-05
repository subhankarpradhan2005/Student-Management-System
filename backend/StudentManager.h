#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include <vector>
#include <string>

using namespace std;

class StudentManager {

private:
    vector<Student> students;

public:

    // CRUD operations
    bool addStudent(int id, string name, int age,
                    string course, float marks);

    vector<Student> getStudents();

    Student* findStudent(int id);

    bool updateStudent(int id, string name, int age,
                       string course, float marks);

    bool deleteStudent(int id);

    // File handling
    void saveToFile();
    void loadFromFile();
};

#endif