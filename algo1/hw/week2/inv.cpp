#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

vector<int> nums;

long long countInversions(int l, int r) {
	// cout << l << " " << r << endl;
	if (l >= r) return 0;
	int mid = (l + r) / 2;
	long long lInvs = countInversions(l, mid);
	long long rInvs = countInversions(mid + 1, r);

	// merging part and calculating inversions from both sides
	vector<int> left(mid - l + 1);
	vector<int> right(r - mid);
	copy(next(nums.begin(), l), next(nums.begin(), mid + 1), left.begin());
	copy(next(nums.begin(), mid + 1), next(nums.begin(), r + 1), right.begin());
	int pi = l, li = 0, ri = 0;
	long long invs = 0;
	while (li < left.size() || ri < right.size()) {
	   if (li < left.size() && ri < right.size()) {
	       if (right[ri] < left[li]) {
	           invs += (left.size() - li);
	           nums[pi] = right[ri++];
	       } else nums[pi] = left[li++];
	   } else if (li < left.size()) {
	       nums[pi] = left[li++];
	   } else nums[pi] = right[ri++];
	   pi++;
	}
	return invs + lInvs + rInvs;
}

int main() {
	int a;
	ifstream inputFile("input2.txt");
	while (inputFile >> a) {
		nums.push_back(a);
	}
	inputFile.close();
	cout << countInversions(0, nums.size() - 1) << endl;
	return 0;
}
