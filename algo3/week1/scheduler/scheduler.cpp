#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>

using namespace std;

typedef long long ll;

vector<pair<int, int> > jobs;
vector<pair<int, int> > diff;
vector<pair<double, int> > rate;
int n;

bool comp(pair<int, int>& a, pair<int, int>& b) {
	return a.first > b.first
		|| (a.first == b.first && jobs[a.second].first > jobs[b.second].first);
}

ll sumOfWeightedCompletion(string v) {
	ll res = 0;
	ll currTime = 0;
	for (int i = 0; i < jobs.size(); i++) {
		int index = v == "diff" ? diff[i].second : rate[i].second;
		currTime += jobs[index].second;
		res += (currTime * jobs[index].first);
	}
	return res;
}

int main() {
	// reading data from file
	ifstream inputFile("input.txt");
	inputFile >> n;
	for (int i = 0; i < n; i++) {
		int w, l;
		inputFile >> w;
		inputFile >> l;
		jobs.push_back(make_pair(w, l));
		diff.push_back(make_pair(w - l, i));
		rate.push_back(make_pair((double) w / l, i));
	}
	inputFile.close();
	cout << "input length : " << jobs.size() << endl;

	sort(diff.begin(), diff.end(), comp);
	sort(rate.begin(), rate.end(), greater<pair<double, int> > ());

	cout << "diff : " << sumOfWeightedCompletion("diff") << endl;
	cout << "rate : " << sumOfWeightedCompletion("rate") << endl;

	return 0;
}
