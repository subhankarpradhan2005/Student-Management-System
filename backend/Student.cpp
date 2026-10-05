#include "Student.h"

Student::Student(int id, string name, int age, string course, float marks) {
    this->id = id;
    this->name = name;
    this->age = age;
    this->course = course;
    this->marks = marks;
}

int Student::getId() const {
    return id;
}

string Student::getName() const {
    return name;
}

int Student::getAge() const {
    return age;
}

string Student::getCourse() const {
    return course;
}

float Student::getMarks() const {
    return marks;
}

void Student::setName(string name) {
    this->name = name;
}

void Student::setAge(int age) {
    this->age = age;
}

void Student::setCourse(string course) {
    this->course = course;
}

void Student::setMarks(float marks) {
    this->marks = marks;
}