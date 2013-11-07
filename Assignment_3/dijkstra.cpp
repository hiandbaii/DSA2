//David Li - DSA2

#include<iostream>
#include <fstream>
#include<sstream>
#include<ctime>
#include<cmath>
#include<string>
#include <cstdlib>

#include "graph.h"

using namespace std;

void loadGraph(graph &myGraph) {
	//Load graph from file
	string filename;
	cout << "Name of graph file: ";
	cin >> filename;

	ifstream input;
	input.open(filename.c_str());
	if (!input) {
		cerr << "Error: could not open " << filename << endl;
		exit(1);
	}

	string line;
	while (!input.eof()){
		getline(input, line);
		stringstream ss(line);
		string prevNode, nextNode, cost_str;
		ss >> prevNode >> nextNode >> cost_str;

		int cost = atoi(cost_str.c_str());

		myGraph.insert_graphEdge(prevNode,nextNode,cost);
	}

}

int main() {
	bool canStart = false;
	string startNode , outFile_name;
	ofstream outFile;
	graph myGraph(500);
	loadGraph(myGraph);

	while (!canStart) {
		cout << "Enter a valid vertex id for the starting vertex: ";
		cin >> startNode;
		canStart = myGraph.contains_graphNode(startNode);
	}

	clock_t t1 = clock();
	myGraph.dijkstra(startNode);
	clock_t t2 = clock();

	double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to apply Dijkstra's algorithm: "<< timeDiff << endl
			<<"Enter name of output file: ";
	cin >> outFile_name;

	outFile.open(outFile_name.c_str());
	myGraph.read(outFile);


	return 0;
}
