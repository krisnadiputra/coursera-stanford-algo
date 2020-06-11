// should compile with below command due to stack memory limit
// g++ -Wl,-stack_size,10000000 -o scc scc.cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<unordered_set>

using namespace std;

struct Node {
	int val;
	vector<Node*> outs;
	vector<Node*> revOuts;
	Node(int v) : val(v) {}
};

int size = 875714, t = 0, ctr;
vector<Node*> nodes(size, NULL), sortedNodes(size, NULL);
vector<bool> visited;
vector<int> sccSizes;

void createNodes() {
	for (int i = 0; i < size; i++)
		nodes[i] = new Node(i);
}

void buildGraph() {
	ifstream inputFile("input.txt");
	string line;
	while (getline(inputFile, line)) {
		stringstream iss(line);
		int tail, head;
		iss >> tail;
		iss >> head;
		nodes[tail - 1]->outs.push_back(nodes[head - 1]);
		nodes[head - 1]->revOuts.push_back(nodes[tail - 1]);
	}
	inputFile.close();
}

void dfs(bool reverse, Node* curNode) {
	if (visited[curNode->val]) return;
	visited[curNode->val] = 1;
	vector<Node*> nexts = reverse ? curNode->revOuts : curNode->outs;
	for (Node* next : nexts)
		dfs(reverse, next);
	if (reverse) sortedNodes[t++] = curNode;
	else ctr++;
}

void DFSLoop(string command) {
	cout << "starting to " << command << "..." << endl;
	visited = vector<bool> (size, 0);
	for (int i = size - 1; i >= 0; i--) {
		if (command == "sort") dfs(1, nodes[i]);
		else {
			ctr = 0;
			dfs(0, sortedNodes[i]);
			if (ctr > 0) sccSizes.push_back(ctr);
		}
	}
}

int main() {
	createNodes();
	buildGraph();
	DFSLoop("sort");
	DFSLoop("find");
	sort(sccSizes.begin(), sccSizes.end());
	for (int& s : sccSizes)
		cout << s << endl;
	cout << "total SCCs : " << sccSizes.size() << endl;
	return 0;
}
