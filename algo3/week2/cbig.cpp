#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<unordered_map>

using namespace std;

struct Node {
	int val;
	int size;
	Node* parent;
	Node(int v) : val(v), size(1), parent(NULL) {}
};

vector<Node*> nodes;
vector<string> keys;
vector<pair<int, int> > edges;
unordered_map<string, vector<int> > vals;

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
	ifstream inputFile("clustering_big.txt");
	int v, bits;
	inputFile >> v;
	inputFile >> bits;
	for (int i = 0; i < v; i++)
		nodes.push_back(new Node(i));
	for (int i = 0; i < v; i++) {
		string s;
		for (int j = 0; j < bits; j++) {
			int bit;
			inputFile >> bit;
			s += (bit ? '1' : '0');
		}
		vals[s].push_back(i);
		keys.push_back(s);
	}
	inputFile.close();
	cout << "nodes length : " << nodes.size() << endl;
}

void flip(string& s, int i) {
	s[i] = s[i] == '0' ? '1' : '0';
}

void findMergingEdges() {
	// edges with dist 0
	for (auto& v : vals) {
		for (int i = 0; i < v.second.size(); i++) {
			for (int j = i + 1; j < v.second.size(); j++)
				edges.push_back(make_pair(v.second[i], v.second[j]));
		}
	}
	cout << "done calculating edges with distance = 0" << endl;
	// edges with dist 1
	for (int i = 0; i < keys.size(); i++) {
		string key = keys[i];
		for (int p = 0; p < key.length(); p++) {
			flip(key, p);
			for (int j = 0; j < vals[key].size(); j++) {
				if (i < vals[key][j])
					edges.push_back(make_pair(i, vals[key][j]));
			}
			flip(key, p);
		}
	}
	cout << "done calculating edges with distance = 1" << endl;
	// edges with dist 2
	for (int i = 0; i < keys.size(); i++) {
		string key = keys[i];
		for (int p1 = 0; p1 < key.length(); p1++) {
			flip(key, p1);
			for (int p2 = p1 + 1; p2 < key.length(); p2++) {
				flip(key, p2);
				for (int j = 0; j < vals[key].size(); j++) {
					if (i < vals[key][j])
						edges.push_back(make_pair(i, vals[key][j]));
				}
				flip(key, p2);
			}
			flip(key, p1);
		}
	}
	cout << "done calculating edges with distance = 2" << endl;
}

int maxCluster() {
	int clusters = nodes.size();
	for (int i = 0; i < edges.size(); i++) {
		int v1 = edges[i].first;
		int v2 = edges[i].second;
		if (find(v1) != find(v2)) {
			clusters--;
			merge(v1, v2);
		}
	}
	return clusters;
}

int main() {
	readInputAndPrepare();
	findMergingEdges();
	cout << "k for max spacing of 3 : " << maxCluster() << endl;
	return 0;
}
