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

void Hashtable::set_mode(int mode) {
	if(!mode) {
		this->method = "linearprobing";
	} else {
		this->method = "doublehashing";
	}
}

double Hashtable::get_load_factor() {
	return (double)this->num_students / this->TABLE_SIZE;
}

void Hashtable::print() {
	for(int i = 0; i < this->TABLE_SIZE; i++) {
		if(this->table[i].key >= 0) {
			cout << "(" << this->table[i].key;
			cout << "," << this->table[i].student.getName() << ",";
			cout << std::fixed << setprecision(1) << this->table[i].student.getGPA();
			cout << ")";
		}
	}

	cout << endl;
}

void Hashtable::insert(int perm, Student s) {
	int insert_result = this->insert_helper(perm,s);

	if(!insert_result) {
		cout << "item already present" << endl;
	} else {
		cout << "item successfully inserted" << endl;
	}
}


/// INSERT HELPER
int Hashtable::insert_helper(int perm, Student s) {

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
			i++;
			if(this->hash2(perm) == 0) {
				hash = (originalSpot + i) % this->TABLE_SIZE;
			} else {
				hash = (originalSpot + (i * this->hash2(perm))) % this->TABLE_SIZE;
			}
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
		}

		return 1;
	} else {
		// Student already added
		return 0;
	}
}

/// LOOKUP STUDENT
void Hashtable::lookup(int perm) {
	pair<HashEntry,int> lookup_result = this->lookup_helper(perm);

	if(lookup_result.second == -20) {
		cout << "item not found" << endl;
	} else {
		cout << "item found; " << lookup_result.first.student.getName() << " " << lookup_result.second << endl;
	}
}


///LOOKUP HELPER
pair<HashEntry, int> Hashtable::lookup_helper(int perm) {
	// Essentially a helper for code re-use on delete as well.
	// No print statements, just find Student and return it, if there
	int hash = this->hash1(perm);
	int original_spot = hash;
	if(this->method == "linearprobing") {
		// 
		while(this->table[hash].key != -20 && this->table[hash].key != perm) {
			if(hash == this->TABLE_SIZE - 1) {
				hash = 0;
			} else {
				hash++;
			}
		}
	} else {
		int i = 0;
		while(this->table[hash].key != -20 && this->table[hash].key != perm) {
			i++;
			if(this->hash2(perm) == 0) {
				hash = (original_spot + i) % this->TABLE_SIZE;
			} else {
				hash = (original_spot + (i * this->hash2(perm))) % this->TABLE_SIZE;
			}
		}
	}

	return make_pair(this->table[hash],hash);
}

void Hashtable::remove(int perm) {
	// Use the lookup helper to remove the item from the hash table
	pair<HashEntry, int> lookup_result = this->lookup_helper(perm);

	if(lookup_result.first.key == -20) {
		cout << "item not present in the table" << endl;
	} else {
		Student s;
		this->table[lookup_result.second].key = -10;
		this->table[lookup_result.second].student = s;
		this->num_students--;
		cout << "item successfully deleted" << endl;
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
		int dummy = this->insert_helper(temp[i].key,temp[i].student);
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


