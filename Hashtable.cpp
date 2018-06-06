#include "Hashtable.h"
#include <string>
#include <iostream>
#include <iomanip>


// Default constructor
Hashtable::Hashtable() {
	this->TABLE_SIZE = 5;
	this->num_students = 0;
	this->method = "linearprobing";
	this->table = new HashEntry[this->TABLE_SIZE];

	// Initalize table with "dummy" students and HashEntries...
	HashEntry initial;
	Student s;
	initial.key = -20;
	initial.student = s;
	for(int i = 0; i < this->TABLE_SIZE; i++) {
		this->table[i] = initial;
	}
}

// Destructor
Hashtable::~Hashtable() {
	delete [] this->table;
}


/// Hash Functions
int Hashtable::hash1(int key) {
	return (key % 492113) % this->TABLE_SIZE;
}

int Hashtable::hash2(int key) {
	return (key % 392113) % this->TABLE_SIZE;
}


double Hashtable::get_load_factor() {
	return (double)this->num_students / this->TABLE_SIZE;
}

/// INSERT
void Hashtable::insert(int perm, Student s) {

	// Create the entry
	HashEntry new_entry;
	new_entry.key = perm;
	new_entry.student = s;

	// Hash the perm number
	int hash = this->hash1(perm);
	int originalSpot = hash;


	// Find a spot, if one exists....
	if(this->method == "linearprobing") {
		while((this->table[hash].key != -20) && (this->table[hash].key != -10) && (this->table[hash].key != perm)){
			if(hash == this->TABLE_SIZE - 1) {
				hash = 0;
			} else {
				hash++;
			}
		}
	} else {
		int i = 0;
		while((this->table[hash].key != -20) && (this->table[hash].key != -10) && (this->table[hash].key != perm)) {
			if(this->hash2(perm) == 0) {
				hash = (originalSpot + i) % this->TABLE_SIZE;
			} else {
				hash = (originalSpot + (i * this->hash2(perm))) % this->TABLE_SIZE;
			}

			i++;
		}
	}

	if(this->table[hash].key < 0) {
		// Found an empty place
		this->table[hash] = new_entry;
		this->num_students++;

		/// Check load factor
		if(this->get_load_factor() > 0.7) {
			this->resize_table();
			cout << "table doubled" << endl;
			cout << "New Table Size: " << this->TABLE_SIZE << endl;
		}

		cout << "item successfully inserted" << endl;
	} else {
		// Student already added
		cout << "item already present" << endl;
	}
}


void Hashtable::print() {
	for(int i = 0; i < this->TABLE_SIZE; i++) {
		if(this->table[i].key > -1) {
			cout << to_string(i) + ": " << this->table[i].student.getName() << " " << std::fixed << setprecision(1) << this->table[i].student.getGPA() << endl;
		} else {
			cout << to_string(i) + ":" << endl;
		}
	}
}



void Hashtable::resize_table() {
	// Store all the students temporarily
	HashEntry temp[this->TABLE_SIZE];
	for(int i = 0; i < this->TABLE_SIZE; i++) {
		temp[i] = this->table[i];
	}

	// Delete old table
	delete [] this->table;


	// Find new table size, then set it to class variable
	int new_size = (this->TABLE_SIZE * 2) + 1;
	while(!this->is_prime(new_size)) {
		new_size += 2;
	}

	cout << "new_size: " << new_size << endl;


	int old_size = this->TABLE_SIZE;
	this->TABLE_SIZE = new_size;

	// Create new table with doubled size to hold students
	HashEntry * new_table = new HashEntry[this->TABLE_SIZE];
	HashEntry filler;
	Student s;
	filler.key = -20;
	filler.student = s;
	for(int i = 0; i < this->TABLE_SIZE; i++) {
		new_table[i] = filler;
	}

	this->table = new_table;
	// reset num students so insert calls don't infinite loop on resizing
	this->num_students = 0;

	// Now add old items from temp table to new table
	for(int i = 0; i < old_size; i++) {
		this->insert(temp[i].key,temp[i].student);
	}
	

}

bool Hashtable::is_prime(int num) {
	if(num <= 3) {
		return (num > 1);
	} else if(num % 2 == 0 || num % 3 == 0) {
		return false;
	} else {
		for(int i = 5; i * i <= num; i += 6) {
			if(num % i == 0 || num % (i + 2) == 0) {
				return false;
			}
		}

		return true;
	}
}


