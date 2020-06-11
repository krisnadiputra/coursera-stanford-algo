#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<unordered_set>
#include<algorithm>

using namespace std;

typedef long long ll;

vector<ll> nums;

int main() {
	ll num;

	// reading data from file
	ifstream inputFile("input.txt");
	while (inputFile >> num)
		nums.push_back(num);
	inputFile.close();

	cout << "data length : " << nums.size() << endl;
	sort(nums.begin(), nums.end());

	int l = 0, r = nums.size() - 1;
	unordered_set<ll> resSet;
	while (l < r) {
		ll sum = nums[l] + nums[r];
		if (sum > 10000) r--;
		else if (sum < -10000) l++;
		else {
			for (int i = r; i > l; i--) {
				sum = nums[l] + nums[i];
				if (sum < -10000) break;
				if (nums[l] == nums[i]) continue;
				resSet.insert(sum);
			}
			l++;
		}
	}

	cout << resSet.size() << endl;
	return 0;
}
