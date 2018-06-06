#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Student.h"
#include <string>
#include <iostream>

using namespace std;

struct HashEntry {
	int key;
	Student student;
};


class Hashtable {

public:
	Hashtable(); // contsructor
	~Hashtable(); // destructor

	int hash1(int key); // Hash1 (linear probing)
	int hash2(int key); // Hash2 for double hashing

	void insert(int perm, Student s);
	int insert_helper(int perm, Student s);
	void lookup(int perm);
	pair<HashEntry,int> lookup_helper(int perm);
	void remove(int perm);
	void print();

	double get_load_factor();
	bool is_prime(int num);
	void resize_table();

private:
	HashEntry* table;
	int TABLE_SIZE;
	int num_students;
	string method;

};


#endif
