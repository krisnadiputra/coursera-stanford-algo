#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

int vertices;
int result = INT_MAX;
vector<vector<int> > DPLayer1, DPLayer2;

void readInputAndPrepare() {
	ifstream inputFile("g3.txt");
	int edges;
	inputFile >> vertices;
	inputFile >> edges;
	DPLayer1 = vector<vector<int> > (vertices, vector<int> (vertices, INT_MAX));
	DPLayer2 = vector<vector<int> > (vertices, vector<int> (vertices));
	for (int i = 0; i < vertices; i++)
		DPLayer1[i][i] = 0;
	for (int i = 0; i < edges; i++) {
		int tail, head, length;
		inputFile >> tail;
		inputFile >> head;
		inputFile >> length;
		if (tail == head && length >= 0) continue;
		DPLayer1[tail - 1][head - 1] = length;
		if (tail != head && length < result)
			result = length;
	}
	inputFile.close();
	cout << "vertices length : " << vertices << endl;
}

void floydWarshall() {
	vector<vector<int> > &curr = DPLayer2, &prev = DPLayer1, &temp = DPLayer1;
	for (int k = 0; k < vertices; k++) {
		cout << "k = " << k << endl;
		for (int i = 0; i < vertices; i++) {
			for (int j = 0; j < vertices; j++) {
				int update = prev[i][j];
				if (prev[i][k] != INT_MAX && prev[k][j] != INT_MAX)
					update = min(update, prev[i][k] + prev[k][j]);
				curr[i][j] = update;
				if (i == j && update < 0) {
					cout << "Negative cycle found!" << endl;
					cout << "Vertex " << i << " is negative." << endl;
					return;
				}
				if (i != j)
					result = min(result, update);
			}
		}
		temp = curr; curr = prev; prev = temp;
	}
}

int main() {
	readInputAndPrepare();
	floydWarshall();
	cout << "shortest shortest distance: " << result << endl;
	return 0;
}
