#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<set>
#include<unordered_set>

using namespace std;

typedef long long ll;

struct Node {
	int val;
	// cost, address
	vector<pair<int, Node*> > nexts;
	Node(int v) : val(v) {}
};

int v, e;
vector<Node*> nodes;

void readInputAndPrepare() {
	ifstream inputFile("input.txt");
	inputFile >> v;
	inputFile >> e;
	for (int i = 0; i < v; i++)
		nodes.push_back(new Node(i));
	for (int i = 0; i < e; i++) {
		int v1, v2, cost;
		inputFile >> v1;
		inputFile >> v2;
		inputFile >> cost;
		nodes[v1 - 1]->nexts.push_back(make_pair(cost, nodes[v2 - 1]));
		nodes[v2 - 1]->nexts.push_back(make_pair(cost, nodes[v1 - 1]));
	}
	inputFile.close();
	cout << "nodes length : " << nodes.size() << endl;
}

ll calcMSTPrim() {
	ll res = 0;
	unordered_set<Node*> visited;
	vector<int> costs = vector<int> (v, INT_MAX);
	// cost, address
	set<pair<int, Node*> > candidates;
	// set starting node
	visited.insert(nodes[0]);
	costs[0] = 0;
	for (auto& next : nodes[0]->nexts) {
		costs[next.second->val] = next.first;
		candidates.insert(next);
	}
	while (!candidates.empty()) {
		pair<int, Node*> closestElement = *candidates.begin();
		Node* curNode = closestElement.second;
		res += closestElement.first;
		candidates.erase(candidates.begin());
		visited.insert(curNode);
		for (auto& next : curNode->nexts) {
			if (visited.find(next.second) != visited.end()) continue;
			int newCost = next.first;
			if (costs[next.second->val] <= newCost) continue;
			// checking if the data is in the set
			if (costs[next.second->val] != INT_MAX)
				candidates.erase(make_pair(costs[next.second->val], next.second));
			candidates.insert(make_pair(newCost, next.second));
			costs[next.second->val] = newCost;
		}
	}
	return res;
}

int main() {
	readInputAndPrepare();
	cout << "MST length : " << calcMSTPrim() << endl;
	return 0;
}
