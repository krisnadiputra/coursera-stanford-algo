#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<queue>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

struct Node {
	Node* left, *right;
	Node(Node* l = NULL, Node* r = NULL) : left(l), right(r) {}
};

vector<Node*> nodes;
priority_queue<pii, vector<pii>, greater<pii> > pq;
int maxDepth = 0, minDepth = INT_MAX;

void readInputAndPrepare() {
	ifstream inputFile("huffman.txt");
	int n;
	inputFile >> n;
	for (int i = 0; i < n; i++) {
		int freq;
		inputFile >> freq;
		nodes.push_back(new Node());
		pq.push(make_pair(freq, i));
	}
	inputFile.close();
	cout << "nodes length : " << nodes.size() << endl;
}

Node* buildTree() {
	while (pq.size() > 1) {
		ll mergedFreq = pq.top().first;
		int id1 = pq.top().second;
		pq.pop();
		mergedFreq += pq.top().first;
		int id2 = pq.top().second;
		pq.pop();
		Node* parent = new Node(nodes[id1], nodes[id2]);
		nodes.push_back(parent);
		pq.push(make_pair(mergedFreq, nodes.size() - 1));
	}
	cout << "total freq : " << pq.top().first << endl;
	return nodes[pq.top().second];
}

void traverse(Node* curNode, int level) {
	if (curNode == NULL) return;
	if (curNode->left == NULL && curNode->right == NULL) {
		maxDepth = max(maxDepth, level);
		minDepth = min(minDepth, level);
	}
	traverse(curNode->left, level + 1);
	traverse(curNode->right, level + 1);
}

int main() {
	readInputAndPrepare();
	Node* root = buildTree();
	traverse(root, 0);
	cout << "max depth : " << maxDepth << endl;
	cout << "min depth : " << minDepth << endl;
	return 0;
}
