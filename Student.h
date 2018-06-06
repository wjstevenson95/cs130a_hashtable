#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student {

public:
	Student(); // default constructor
	Student(string name, double gpa); // secondary constructor
	
	// getter methods
	double getGPA() const;
	string getName() const;

	// setter methods
	void setGPA(double new_gpa);
	void setName(string new_name);

private:
	string name;
	double gpa;
};


#endif
