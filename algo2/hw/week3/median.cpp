#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<queue>

using namespace std;

priority_queue<int> lo;
priority_queue<int, vector<int>, greater<int> > hi;

int main() {
	int num, res = 0;
	ifstream inputFile("input.txt");
	while (inputFile >> num) {
		// inserting to heap
		if (lo.empty() || lo.top() >= num) lo.push(num);
		else hi.push(num);
		// rebalancing
		if (lo.size() > hi.size() && lo.size() - hi.size() > 1) {
			hi.push(lo.top());
			lo.pop();
		} else if (hi.size() > lo.size()) {
			lo.push(hi.top());
			hi.pop();
		}
		// getting the median
		res = (res + lo.top()) % 10000;
	}
	inputFile.close();
	cout << res << endl;
	return 0;
}
