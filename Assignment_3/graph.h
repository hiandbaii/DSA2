#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <list>
#include "hash.h"



class graph{

private:
	class graphEdge;
	class graphNode;

public:
	//Constructor
	graph(int capacity=500);

	//true if node not already in graph
	bool insert_graphNode(std::string nodeId);

	//true if in graph
	bool contains_graphNode(std::string nodeId);

	//insert graphEdge into adjacency list
	void insert_graphEdge(std::string prevNode, std::string nextNode, int cost);

	//do dijkstra's
	void dijkstra(std::string srcNode);

	//read out graph, intended for djkstra's
	void read(std::ofstream& outFile);

private:

	class graphNode {
		public:
		std::string graphNode_id;
		graphNode* prev;
		bool visited;
		int distance;
		std::list <graphEdge *> adjacencyList;
	};

	class graphEdge{
	public:
		graphNode *next;
		int cost;
	};

	std::list<graphNode *>nodeList;
	hashTable *graphNodes;


};
#endif /* GRAPH_H_ */
