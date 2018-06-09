#include "Student.h"
#include "Hashtable.h"

#include <iostream>
#include <string>
#include <exception>

using namespace std;

int main() {

	// Check argc for command line arguments...
	try {

		Hashtable h;

		while(true) {
			// Get input from the command line
			string input;
			cin >> input;

			if(cin.eof()) {
				break;
			}

			else if(input == "linearprobing") {
				h.set_mode(0);
			}

			else if(input == "doublehashing") {
				h.set_mode(1);
			}

			else if(input == "insert") {
				int perm;
				double gpa;
				string name;
				cin >> perm >> name >> gpa;

				Student new_student(name,gpa);
				h.insert(perm,new_student);
			}

			else if(input == "lookup") {
				int perm;
				cin >> perm;
				h.lookup(perm);
			}

			else if(input == "delete") {
				int perm;
				cin >> perm;
				h.remove(perm);
			}

			else if(input == "print") {
				h.print();
			}

			else {
				cin.clear();
				cout << "input string format was incorrect" << endl;
			}
		}

	}
	catch(exception &ex) {
		cerr << ex.what() << endl;
	}

	return 0;
}