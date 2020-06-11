#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

int nodes;
vector<pair<int, int> > inputEdges;

void readFileToVector() {
	ifstream inputFile("input.txt");
	string line;
	nodes = 0;
	while (getline(inputFile, line)) {
		stringstream iss(line);
		int number, firstNo, count = 0;
		nodes++;
		while (iss >> number) {
			if (count == 0) firstNo = number;
			else if (firstNo < number)
				inputEdges.push_back(make_pair(firstNo, number));
			count++;
		}
	}
	inputFile.close();
}

int randomContract(vector<pair<int, int> > edges) {
	for (int i = 0; i < nodes - 2; i++) {
		vector<pair<int, int> > updatedEdges;
		int index = rand() % edges.size();
		int n1 = edges[index].first;
		int n2 = edges[index].second;
		// n2 merges into n1
		for (pair<int, int>& edge : edges) {
			pair<int, int> newEdge;
			newEdge.first = edge.first == n2 ? n1 : edge.first;
			newEdge.second = edge.second == n2 ? n1 : edge.second;
			if (newEdge.first != newEdge.second)
				updatedEdges.push_back(newEdge);
		}
		edges = updatedEdges;
	}
	return edges.size();
}

int main() {
	readFileToVector();
	cout << "edge size: " << inputEdges.size() << endl;
	int n = nodes * nodes * 10;
	int res = INT_MAX;
	srand(time(0));
	for (int i = 0; i < n; i++) {
		if (i % 100 == 0)
			cout << "processed " << i << " times..." << endl;
		int remEdges = randomContract(inputEdges);
		if (remEdges < res) {
			res = remEdges;
			cout << "result updated : " << res << endl;
		}
	}
	cout << res << endl;
	return 0;
}
