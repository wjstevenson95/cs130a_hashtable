#include "Student.h"
#include "Hashtable.h"

#include <iostream>
#include <string>

using namespace std;

int main() {

	Hashtable h;
	Student a("asad",3.9);
	h.insert(8670959,a);

	Student b("victor",3.6);
	h.insert(7670931,b);
	
	Student c("omid",4.0);
	h.insert(7636338,c);

	Student d("jin",2.5);
	h.insert(5712195,d);

	h.print();
	h.lookup(7636338);

	return 0;
}