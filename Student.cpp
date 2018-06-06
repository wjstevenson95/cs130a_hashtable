#include "Student.h"

#include <iostream>
#include <string>

using namespace std;

Student::Student() {
	this->name = "";
	this->gpa = 0.0;
}

Student::Student(string name, double gpa) {
	this->name = name;
	this->gpa = gpa;
}

string Student::getName() const {
	return this->name;
}

double Student::getGPA() const {
	return this->gpa;
}

void Student::setGPA(double new_gpa) {
	this->gpa = new_gpa;
}

void Student::setName(string new_name) {
	this->name = new_name;
}