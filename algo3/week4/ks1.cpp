#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

int totalSize;
vector<int> vals, weights;

void readInputAndPrepare() {
	ifstream inputFile("knapsack1.txt");
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

int knapsack() {
	vector<vector<int> > k (weights.size() + 1, vector<int> (totalSize + 1, 0));
	for (int i = 1; i <= weights.size(); i++) {
		for (int sz = 1; sz <= totalSize; sz++) {
			int take = sz < weights[i - 1] ? 0 : vals[i - 1] + k[i - 1][sz - weights[i - 1]];
			int skip = k[i - 1][sz];
			k[i][sz] = max(skip, take);
		}
	}
	return k[weights.size()][totalSize];
}

int main() {
	readInputAndPrepare();
	cout << "max value : " << knapsack() << endl;
	return 0;
}

/*
k(i, s) = max(k(i - 1, s), v_i + k(i - 1, s - w_i));
*/
