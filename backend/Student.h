#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student {

private:
    int id;
    string name;
    int age;
    string course;
    float marks;

public:

    Student(int id, string name, int age, string course, float marks);

    // Getters
    int getId() const;
    string getName() const;
    int getAge() const;
    string getCourse() const;
    float getMarks() const;

    // Setters
    void setName(string name);
    void setAge(int age);
    void setCourse(string course);
    void setMarks(float marks);
};

#endif