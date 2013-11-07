//David Li - DSA2

#include <iostream>
#include <fstream>
#include <limits>
#include <stack>
#include "heap.h"
#include "graph.h"

#define INF std::numeric_limits<int>::max();

//Constructor
graph::graph(int capacity) {
	graphNodes = new hashTable(capacity * 2);
}
;

bool graph::insert_graphNode(std::string nodeId) {
	if (this->graphNodes->contains(nodeId)) {
		return false;
	} else {
		graphNode *newNode = new graphNode;
		newNode->graphNode_id = nodeId;
		this->nodeList.push_back(newNode);
		this->graphNodes->insert(nodeId, newNode);
		return true;
	}
}
;

bool graph::contains_graphNode(std::string nodeId) {
	return this->graphNodes->contains(nodeId);
}
;

void graph::insert_graphEdge(std::string prevNode, std::string nextNode,
		int cost) {
	this->insert_graphNode(prevNode);
	this->insert_graphNode(nextNode);
	graphNode *prev = static_cast<graphNode *>(this->graphNodes->getPointer(prevNode));
	graphNode *next = static_cast<graphNode *>(this->graphNodes->getPointer(nextNode));

//	std::cout << prevNode <<" " <<nextNode <<" " << cost << std::endl;
	graphEdge *newEdge = new graphEdge();
	newEdge->cost = cost;
	newEdge->next = next;

	prev->adjacencyList.push_back(newEdge);

}
;

void graph::dijkstra(std::string srcNode) {
	heap unvisitedNodes(this->nodeList.size());
	graphNode *v;
	int altDist;
	for (std::list<graphNode *>::iterator it = this->nodeList.begin();
			it != nodeList.end(); it++) {
		std::cout << (*it)->graphNode_id << ", ";
	}
	std::cout << std::endl;
	for (std::list<graphNode *>::iterator it = this->nodeList.begin();
			it != nodeList.end(); it++) {
		if ((*it)->graphNode_id == srcNode) {
			(*it)->distance = 0;
		} else {
			(*it)->distance = std::numeric_limits<int>::max();
		}
		(*it)->prev = NULL;
		(*it)->visited = false;
		unvisitedNodes.insert((*it)->graphNode_id, (*it)->distance, (*it));
	}

	while (unvisitedNodes.deleteMin(NULL, NULL, &v) == 0) {
		v->visited = true;
		if (v->distance == std::numeric_limits<int>::max()) {
			continue;
		} else {
			for (std::list<graphEdge *>::iterator it = v->adjacencyList.begin();
					it != v->adjacencyList.end(); it++) {
				altDist = v->distance + (*it)->cost;
				if (altDist < ((*it)->next)->distance) {
					((*it)->next)->distance = altDist;
					((*it)->next)->prev = v;
					unvisitedNodes.setKey(((*it)->next)->graphNode_id, altDist);
				}
			}

		}
	}

}
;

void graph::read(std::ofstream &outputFile) {
	for (std::list<graphNode *>::iterator it = this->nodeList.begin();
			it != this->nodeList.end(); it++) {
		outputFile << (*it)->graphNode_id << ": ";
		if ((*it)->distance == std::numeric_limits<int>::max()) {
			outputFile << "NO PATH" << std::endl;
		} else {
			outputFile << (*it)->distance << " [";
			std::stack<std::string> readPath;

			readPath.push((*it)->graphNode_id);
			graphNode *v = (*it);
			while (v->prev != NULL) {
				v = v->prev;
				readPath.push(v->graphNode_id);

			}
			outputFile << readPath.top();
			readPath.pop();
			while (!readPath.empty()) {
				outputFile << ", " << readPath.top();
				readPath.pop();
			}
			outputFile << ']' << std::endl;
		}
	}

}
;
