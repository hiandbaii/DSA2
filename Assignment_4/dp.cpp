//David Li - DSA2

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <string>
#include <cstdlib>
#include <stack>
#include <locale>

using namespace std;


int pathMat[100][100];//Assume 99 char words as longest
string outString;

bool fill(string A,string B,string Merge){
	
	for (int i = 0; i<100; i++){
		for (int j = 0; j<100;j++){
				pathMat[i][j] = 0;
		}
	}
	
	int sizeA = A.size();
	int sizeB = B.size();
	int sizeM = Merge.size();
	stringstream outputStream;
	stack<char> decision;
	
	if (sizeA + sizeB != sizeM){
		return false;
	}else if(A[0]!=Merge[0] && B[0]!=Merge[0]){
		return false;
	}else if (A[sizeA-1]!=Merge[sizeM-1] && B[sizeB-1]!=Merge[sizeM-1]){
		return false;
	}else{
		pathMat[sizeB][sizeA] = 1;
		pathMat[0][0] = 1;
	}
	
	
	for (int i = 0; i <= sizeB; i++){
		for (int j = 0; j <= sizeA; j++){
			if (i == 0 && j == 0){
				continue;
			}else if (i == sizeB && j == sizeA){
				continue;
			}

			if ( (i == 0) && (pathMat[i][j-1] == 1) && (A[j]==Merge[i+j] || B[i]==Merge[i+j]) ){
				pathMat[i][j] = 1;
			}else if( (j == 0) && (pathMat[i-1][j] == 1) &&(A[j]==Merge[i+j] || B[i]==Merge[i+j]) ){
				pathMat[i][j] = 1;
			}else if ((pathMat[i-1][j] == 1 || pathMat[i][j-1] == 1) && (A[j]==Merge[i+j] || B[i]==Merge[i+j])){
				pathMat[i][j] = 1;
			}
			
		}
	}
	// cout << endl;
	// for (int i = 0; i <= sizeB; i++){
	// 	for (int j = 0; j <= sizeA; j++){ 
	// 		cout << pathMat[i][j] << ",";
	// 	}
	// 	cout << endl;
	// }

	int i = sizeB;
	int j = sizeA;
	
	while (i > 0 || j > 0){
		if (pathMat[i-1][j] == 1){
			decision.push(tolower(B[i-1]));
			i = i-1;
		}else if (pathMat[i][j-1] == 1){
			decision.push(toupper(A[j-1]));
			j = j-1;
		}else{
			return false;
		}

		if (j < 0 || i < 0){
			return false;
		}
	}

	while (!decision.empty()){
		outputStream << decision.top();
		decision.pop();
	}
	outString = outputStream.str();

	return true;
	
	
}


int main(){	
	
	//~File IO
	string inFile, outFile;
	cout << "Enter name of input file: ";
	cin >> inFile;
	cout << "Enter name of output file: ";
	cin >> outFile;

	ifstream input;
	input.open(inFile.c_str());
	if (!input) {
		cerr << "Error: could not open " << inFile << endl;
		exit(1);
	}
	string line;
    string wordA,wordB,wordMerged;
    // input.close();
    
    ofstream output(outFile.c_str());

	while (getline(input, line)){
		stringstream ssA(line);
		ssA >> wordA;
		getline(input, line);
		stringstream ssB(line);
		ssB >> wordB;
		getline(input, line);
		stringstream ssC(line);
		ssC >> wordMerged;
		
		
		if (fill(wordA,wordB,wordMerged)){
			output << outString << endl;
			// cout << outString << endl;
		}else{
			output << "*** NOT A MERGE ***" << endl;
			// cout << "*** NOT A MERGE ***" << endl;
		};
		
	}	

	output.close();
	return 0;
}
