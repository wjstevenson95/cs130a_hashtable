#include "Student.h"
#include "Hashtable.h"

#include <iostream>
#include <string>

using namespace std;

int main() {

	Hashtable h;
	Student a("asad",3.9);
	Student b("victor",3.6);
	Student c("omid",4.0);
	Student d("jin",2.5);


	h.insert(8670959,a);
	h.insert(7670931,b);
	h.insert(7636338,c);

	h.lookup(7636338);

	h.insert(5712195,d);
	h.print();

	h.remove(4444444);
	h.remove(5712195);

	h.print();
	h.remove(7636338);

	h.lookup(8670959);
	h.remove(8670959);

	h.print();

	return 0;
}