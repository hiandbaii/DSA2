//David Li - DSA2

#include <iostream>
#include <cstring>
#include "hash.h"

hashTable::hashTable(int size) {
	this->capacity = getPrime(size);
	this->data.resize(this->capacity);
	for (int i = 0; i < this->capacity; i++) {
		this->data[i].isOccupied = false;
	}
	this->filled = 0;
}

//will use double hashing
unsigned int hashTable::hash(const std::string &key) {
	unsigned int hashValue = 0;
	int intLength = key.length() / 4 + 1;
	int extra = key.length() % intLength;

	//folds 4 chars into one int, if no char is present in slot
	//int value of char will be 0.
	for (int i = 0; i < intLength; i++) {
		char fold[5] = { };
		std::strcpy(fold, key.substr(4 * i, 4).c_str());
		for (int j = 0; j < 4; j++) {
			hashValue += fold[j] * 256 * (j + 1);
		}
	}

	hashValue %= this->capacity;
	return hashValue;
}

//djb hash function, special case of 0 undesired
unsigned int hashTable::hash2(const std::string &key) {
	unsigned int hashValue = 5381;
	for (int i = 0; i < key.size(); i++) {
		hashValue = (hashValue << 5) + hashValue + key[i];
	}
	hashValue %= this->capacity;
	if (hashValue == 0){
		hashValue =1;
	}
	return hashValue;
}

int hashTable::insert(const std::string &key, void *pv) {
	if (this->filled * 2 >= this->capacity) {
		if (!this->rehash()) {
			return 2;
		}
	}
	unsigned int index = hash(key);
	unsigned int index2 = hash2(key);
	while (data[index].isOccupied) {
		if (data[index].key == key && ~data[index].isDeleted) {
			return 1;
		}
		index += index2;
		index %= this->capacity;
	}
	data[index].isOccupied = true;
	data[index].isDeleted = false;
	data[index].key = key;
	data[index].pv = pv;
	this->filled ++;
	return 0;

}

unsigned int hashTable::getPrime(int size) {
	const unsigned int primes[] = { 24593, 49157, 98317, 196613, 393241, 786433,
			1572869, 3145739, 6291469 };
	int i;
	for (i = 0; i < sizeof(primes); i++) {
		if (size < primes[i]) {
			break;
		}
	}
	return primes[i];
}

int hashTable::findPos(const std::string &key) {
	unsigned int index = hash(key);
	unsigned int index2 = hash2(key);
	while (data[index].isOccupied) {
		if (data[index].key == key && ~data[index].isDeleted) {
			return index;
		}
		index += index2;
		index %= this->capacity;
	}
	return -1;
}

bool hashTable::contains(const std::string &key){
	if (findPos(key) == -1){
		return false;
	}
	return true;
}

bool hashTable::rehash() {
//	std::cout << "Rehash" << std::endl;
	std::vector<hashItem> prevData = this->data;
	int newSize = getPrime(this->capacity * 2);
	try {
		this->data.resize(newSize);
		this->capacity = newSize;
	} catch (std::bad_alloc &e) {
		std::cerr << "Rehash fail - " << e.what() << std::endl;
		return false;
	}
	for (int i = 0; i < this->capacity; i++) {
		this->data[i].isOccupied = false;
	}
	this->filled = 0;
	for (int i = 0; i < prevData.size(); i++) {
		if (!prevData[i].isDeleted && prevData[i].isOccupied) {
			this->insert(prevData[i].key, prevData[i].pv);
			this->filled++;
		}
	}
	return true;

}
