#include "heap.h"
#include <iostream>

heap::heap(int capacity) {
	this->capacity = capacity;
	this->filled = -1;
	data.resize(capacity + 1);
	mapping = new hashTable(capacity * 2);
}

int heap::insert(const std::string &id, int key, void *pv) {
	if (this->filled >= this->capacity - 1) {
		return 1;
	} else if (this->mapping->contains(id)) {
		return 2;
	} else {
		this->filled++;
		this->data[this->filled].id = id;
		this->data[filled].key = key;
		this->data[filled].pData = pv;
		this->mapping->insert(data[filled].id, &data[filled]);
		percolateUp(filled);
		return 0;
	}
}

int heap::setKey(const std::string &id, int key) {
	bool b;
	node *pNode = static_cast<node *>(this->mapping->getPointer(id, &b));
	if (b) {
		pNode->key = key;
		int posCur = pNode - &this->data[0];
		percolateUp(posCur);
		percolateDown(posCur);
		return 0;
	}
	return 1;
}
int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
	if (this->filled < 0) {
		return 1;
	}
	if (pId) {
		*pId = this->data[0].id;
	}
	if (pKey) {
		*pKey = this->data[0].key;
	}
	if (ppData) {
		*static_cast<void **>(ppData) = this->data[0].pData;
	}
	this->mapping->remove(this->data[0].id);
	this->data[0] = this->data[this->filled];
	this->filled--;
	this->mapping->setPointer(this->data[0].id, &this->data[0]);
	percolateDown(0);
	return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData) {
	bool b;
	node *pNode = static_cast<node *>(this->mapping->getPointer(id, &b));
	if (b) {
		if (pKey) {
			*pKey = pNode->key;
		}
		if (ppData) {
			*static_cast<void **>(ppData) = pNode->pData;
		}

		int posCur = pNode - &this->data[0];
		if (posCur == 0) {
			deleteMin();
		} else {
			this->mapping->remove(this->data[posCur].id);
			this->data[posCur] = this->data[filled];
			this->filled--;
			percolateDown(posCur);
			percolateUp(posCur);
		}
	} else {
		return 1;
	}
	return 0;
}

void heap::percolateUp(int posCur) {
//	std::cout << "Trying Up" << std::endl;
	node temp = this->data[posCur];
	int parent = (posCur - 1) / 2;
	while (temp.key < this->data[parent].key && posCur > 0) {
		this->data[posCur] = this->data[parent];
		this->mapping->setPointer(this->data[posCur].id, &this->data[posCur]);
		posCur = parent;
		parent = (posCur - 1) / 2;
	}
	this->data[posCur] = temp;
	this->mapping->setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateDown(int posCur) {
//	std::cout << "Trying Down" << std::endl;
	node temp = this->data[posCur];
	int child1 = 2 * posCur + 1;
	int child2 = 2 * posCur + 2;
	while (true) {
		if (child2 > this->filled) { //handle cases at end of heap
			if (child1 == this->filled) {
				if (this->data[posCur].key > this->data[child1].key) {
					this->data[posCur] = this->data[child1];
					this->mapping->setPointer(this->data[posCur].id,
							&this->data[posCur]);
					posCur = child1;
				}
			}
			break;
		}

		if (temp.key > this->data[child1].key
				|| temp.key > this->data[child2].key) {
			if (this->data[child1].key < this->data[child2].key) {
				this->data[posCur] = this->data[child1];
				this->mapping->setPointer(this->data[posCur].id,
						&this->data[posCur]);
				posCur = child1;
			} else {
				this->data[posCur] = this->data[child2];
				this->mapping->setPointer(this->data[posCur].id,
						&this->data[posCur]);
				posCur = child2;
			}
			child1 = 2 * posCur + 1;
			child2 = 2 * posCur + 2;
		} else {
			break;
		}
	}
	this->data[posCur] = temp;
	this->mapping->setPointer(data[posCur].id, &data[posCur]);
}

void heap::read() {
	if (this->filled == -1) {
		std::cout << "Heap empty" << std::endl;
	} else {
		for (int i = 0; i < this->filled + 1; i++) {
			std::cout << this->data[i].id << "/" << this->data[i].key << " ";
		}
		std::cout << std::endl;
		std::cout << this->filled << std::endl;
	}
}
