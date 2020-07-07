#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<cmath>
#include<unordered_set>

using namespace std;

int totalSize;
vector<double> x, y;

void readInputAndPrepare() {
	ifstream inputFile("nn.txt");
	int n;
	inputFile >> n;
	for (int i = 0; i < n; i++) {
		int num;
		double a, b;
		inputFile >> num;
		inputFile >> a;
		inputFile >> b;
		x.push_back(a);
		y.push_back(b);
	}
	inputFile.close();
	cout << "points length : " << n << endl;
}

double sqDist(double x1, double y1, double x2, double y2) {
	double dx = x1 - x2;
	double dy = y1 - y2;
	return dx * dx + dy * dy;
}

double nn(int curPoint) {
	double result = 0;
	unordered_set<int> visited;
	visited.insert(curPoint);
	while (visited.size() < x.size()) {
		if (visited.size() % 500 == 0)
			cout << "# of visited cities : " << visited.size() << endl;
		int closestPoint = -1;
		double closestSqDist;
		for (int i = 0; i < x.size(); i++) {
			if (visited.find(i) != visited.end()) continue;
			double curSqDist = sqDist(x[curPoint], y[curPoint], x[i], y[i]);
			if (closestPoint == -1 || curSqDist < closestSqDist) {
				closestPoint = i;
				closestSqDist = curSqDist;
			}
		}
		result += sqrt(closestSqDist);
		curPoint = closestPoint;
		visited.insert(closestPoint);
	}
	result += sqrt(sqDist(x[curPoint], y[curPoint], x[0], y[0]));
	return result;
}

int main() {
	readInputAndPrepare();
	cout << setprecision(15) << nn(0) << endl;
	return 0;
}
