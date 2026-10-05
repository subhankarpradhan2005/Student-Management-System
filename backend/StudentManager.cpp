#include "StudentManager.h"
#include <fstream>
#include <sstream>

using namespace std;

// Add Student
bool StudentManager::addStudent(
    int id,
    string name,
    int age,
    string course,
    float marks
) {
    // Check duplicate ID
    for (const Student& student : students) {
        if (student.getId() == id) {
            return false;
        }
    }

    // Validate age
    if (age <= 0 || age > 100) {
        return false;
    }

    // Validate marks
    if (marks < 0 || marks > 100) {
        return false;
    }

    Student student(id, name, age, course, marks);

    students.push_back(student);

    saveToFile();

    return true;
}


// Get all students
vector<Student> StudentManager::getStudents() {
    return students;
}


// Find student by ID
Student* StudentManager::findStudent(int id) {

    for (Student& student : students) {

        if (student.getId() == id) {
            return &student;
        }
    }

    return nullptr;
}


// Update Student
bool StudentManager::updateStudent(
    int id,
    string name,
    int age,
    string course,
    float marks
) {
    Student* student = findStudent(id);

    if (student == nullptr) {
        return false;
    }

    // Validate age
    if (age <= 0 || age > 100) {
        return false;
    }

    // Validate marks
    if (marks < 0 || marks > 100) {
        return false;
    }

    student->setName(name);
    student->setAge(age);
    student->setCourse(course);
    student->setMarks(marks);

    saveToFile();

    return true;
}


// Delete Student
bool StudentManager::deleteStudent(int id) {

    for (auto it = students.begin(); it != students.end(); ++it) {

        if (it->getId() == id) {

            students.erase(it);

            saveToFile();

            return true;
        }
    }

    return false;
}


// Save students to file
void StudentManager::saveToFile() {

    ofstream file("../data/students.dat");

    if (!file) {
        return;
    }

    for (const Student& student : students) {

        file << student.getId() << "|"
             << student.getName() << "|"
             << student.getAge() << "|"
             << student.getCourse() << "|"
             << student.getMarks()
             << "\n";
    }

    file.close();
}


// Load students from file
void StudentManager::loadFromFile() {

    ifstream file("../data/students.dat");

    if (!file) {
        return;
    }

    students.clear();

    string line;

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string id;
        string name;
        string age;
        string course;
        string marks;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, age, '|');
        getline(ss, course, '|');
        getline(ss, marks, '|');

        Student student(
            stoi(id),
            name,
            stoi(age),
            course,
            stof(marks)
        );

        students.push_back(student);
    }

    file.close();
}