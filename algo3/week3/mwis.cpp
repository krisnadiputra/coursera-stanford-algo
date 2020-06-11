#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

typedef long long ll;

vector<int> weights;
vector<ll> maxWeights;
vector<bool> included;
vector<int> indexes = {0, 1, 2, 3, 16, 116, 516, 996};

void readInputAndPrepare() {
	ifstream inputFile("mwis.txt");
	int n;
	inputFile >> n;
	for (int i = 0; i < n; i++) {
		int w;
		inputFile >> w;
		weights.push_back(w);
	}
	inputFile.close();
	cout << "weights length : " << weights.size() << endl;
}

void findMaxWeights() {
	for (int i = 0; i < weights.size(); i++) {
		ll inc = weights[i] + (i - 2 < 0 ? 0 : maxWeights[i - 2]);
		ll skip = (i - 1 < 0 ? 0 : maxWeights[i - 1]);
		maxWeights.push_back(max(inc, skip));
	}
	cout << "mwis : " << maxWeights.back() << endl;
}

void findIndependentSet() {
	included = vector<bool> (weights.size(), 0);
	int i = weights.size() - 1;
	while (i >= 0) {
		ll inc = weights[i] + (i - 2 < 0 ? 0 : maxWeights[i - 2]);
		ll skip = (i - 1 < 0 ? 0 : maxWeights[i - 1]);
		if (inc > skip) {
			included[i] = 1;
			i--;
		}
		i--;
	}
}

int main() {
	readInputAndPrepare();
	findMaxWeights();
	findIndependentSet();
	for (int& id : indexes)
		cout << included[id];
	cout << endl;
	return 0;
}
