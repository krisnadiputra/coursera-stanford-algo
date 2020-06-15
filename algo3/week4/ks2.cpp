#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<unordered_map>

using namespace std;

int totalSize;
vector<int> vals, weights;
unordered_map<int, unordered_map<int, int> > k;

void readInputAndPrepare() {
	ifstream inputFile("knapsack_big.txt");
	int n;
	inputFile >> totalSize;
	inputFile >> n;
	for (int i = 0; i < n; i++) {
		int v, w;
		inputFile >> v;
		inputFile >> w;
		vals.push_back(v);
		weights.push_back(w);
	}
	inputFile.close();
	cout << "weights length : " << weights.size() << endl;
}

int knapsack(int i, int sz) {
	if (i <= 0 || sz <= 0) return 0;
	if (k[i].find(sz) != k[i].end()) return k[i][sz];
	cout << "calculating knapsack(" << i << ", " << sz << ")" << endl;
	int take = sz < weights[i - 1] ? 0 : vals[i - 1] + knapsack(i - 1, sz - weights[i - 1]);
	int skip = knapsack(i - 1, sz);
	int res = max(take, skip);
	k[i][sz] = res;
	return res;
}

int main() {
	readInputAndPrepare();
	cout << "max value : " << knapsack(weights.size(), totalSize) << endl;
	return 0;
}

/*
k(i, s) = max(k(i - 1, s), v_i + k(i - 1, s - w_i));
*/
