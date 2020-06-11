// please compile with c++ 11
// g++ -std=c++11 -o dijkstra dijkstra.cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<set>
#include<unordered_set>

using namespace std;

struct Node {
	int val;
	// dist, address
	vector<pair<int, Node*> > nexts;
	Node(int v) : val(v) {}
};

int graphSize = 200;
int defDistance = 1000000;

vector<Node*> nodes (graphSize);
vector<int> distances(graphSize, defDistance);
vector<int> indexes = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};

void createNodes() {
	for (int i = 0; i < graphSize; i++)
		nodes[i] = new Node(i);
}

void buildGraph() {
	ifstream inputFile("input.txt");
	string line;
	while (getline(inputFile, line)) {
		stringstream iss(line);
		int tail;
		iss >> tail;
		string headData;
		while (iss >> headData) {
			int commaPos = headData.find(',');
			int head = stoi(headData.substr(0, commaPos));
			int dist = stoi(headData.substr(commaPos + 1));
			nodes[tail - 1]->nexts.push_back(make_pair(dist, nodes[head - 1]));
		}
	}
	inputFile.close();
}

void runDijkstra() {
	unordered_set<Node*> visited;
	// dist, address
	set<pair<int, Node*> > candidates;
	// set starting node
	visited.insert(nodes[0]);
	distances[0] = 0;
	for (auto& next : nodes[0]->nexts) {
		distances[next.second->val] = next.first;
		candidates.insert(next);
	}
	while (!candidates.empty()) {
		pair<int, Node*> closestElement = *candidates.begin();
		Node* curNode = closestElement.second;
		candidates.erase(candidates.begin());
		visited.insert(curNode);
		for (auto& next : curNode->nexts) {
			if (visited.find(next.second) != visited.end()) continue;
			int newDistance = distances[curNode->val] + next.first;
			if (distances[next.second->val] < newDistance) continue;
			// checking if the data is in the set
			if (distances[next.second->val] != defDistance)
				candidates.erase(make_pair(distances[next.second->val], next.second));
			candidates.insert(make_pair(newDistance, next.second));
			distances[next.second->val] = newDistance;
		}
	}
}

int main() {
	createNodes();
	buildGraph();
	runDijkstra();
	for (int i = 0; i < distances.size(); i++) {
		cout << i << " : " << distances[i] << endl;
	}
	for (int& index : indexes) {
		cout << distances[index - 1] << ",";
	}
	cout << endl;
	return 0;
}
