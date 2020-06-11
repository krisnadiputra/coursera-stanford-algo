#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

struct Node {
	int val;
	int size;
	Node* parent;
	Node(int v) : val(v), size(1), parent(NULL) {}
};

vector<Node*> nodes;
vector<pair<int, pair<int, int> > > edges;

int find(int v) {
	Node* curNode = nodes[v];
	while (curNode->parent) curNode = curNode->parent;
	return curNode->val;
}

void merge(int v1, int v2) {
	int s1 = find(v1);
	int s2 = find(v2);
	if (s1 == s2) return;
	if (nodes[s1]->size > nodes[s2]->size) {
		nodes[s2]->parent = nodes[s1];
		nodes[s1]->size += nodes[s2]->size;
	} else {
		nodes[s1]->parent = nodes[s2];
		nodes[s2]->size += nodes[s1]->size;
	}
 }

void readInputAndPrepare() {
	ifstream inputFile("clustering1.txt");
	int v;
	inputFile >> v;
	for (int i = 0; i < v; i++)
		nodes.push_back(new Node(i));
	for (int i = 0; i < v; i++) {
		for (int j = i + 1; j < v; j++) {
			int v1, v2, cost;
			inputFile >> v1;
			inputFile >> v2;
			inputFile >> cost;
			edges.push_back(make_pair(cost, make_pair(v1 - 1, v2 - 1)));
		}
	}
	inputFile.close();
	cout << "nodes length : " << nodes.size() << endl;
}

int maxSpaceCluster(int k) {
	int clusters = nodes.size();
	for (int i = 0; i < edges.size(); i++) {
		// cout << i << " " << edges[i].first << endl;
		int v1 = edges[i].second.first;
		int v2 = edges[i].second.second;
		if (find(v1) != find(v2)) {
			clusters--;
			merge(v1, v2);
			if (clusters == k - 1) return edges[i].first;
		}
	}
}

int main() {
	readInputAndPrepare();
	sort(edges.begin(), edges.end());
	cout << "max space of 4-cluster : " << maxSpaceCluster(4) << endl;
	return 0;
}
