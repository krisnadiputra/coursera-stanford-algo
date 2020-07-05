#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<cmath>

using namespace std;

int totalSize;
vector<double> x, y;

void readInputAndPrepare() {
	ifstream inputFile("tsp.txt");
	int n;
	inputFile >> n;
	for (int i = 0; i < n; i++) {
		double a, b;
		inputFile >> a;
		inputFile >> b;
		x.push_back(a);
		y.push_back(b);
	}
	inputFile.close();
	cout << "points length : " << n << endl;
}

double dist(double x1, double y1, double x2, double y2) {
	double dx = x1 - x2;
	double dy = y1 - y2;
	return sqrt(dx * dx + dy * dy);
}

double tsp() {
	double result = 0;
	// guessed the track by plotting
	vector<int> track = {
		23, 24, 19, 16, 20, 22, 21, 17, 18, 14,
		11, 10, 9, 5, 1, 0, 4, 7, 3, 2,
		6, 8, 12, 13, 15
	};
	for (int i = 0; i < track.size(); i++) {
		int j = (i + 1) % track.size();
		result += dist(x[track[i]], y[track[i]], x[track[j]], y[track[j]]);
	}
	return result;
}

int main() {
	readInputAndPrepare();
	cout << "tsp value : " << tsp() << endl;
	return 0;
}

/*
k(i, s) = max(k(i - 1, s), v_i + k(i - 1, s - w_i));
*/
