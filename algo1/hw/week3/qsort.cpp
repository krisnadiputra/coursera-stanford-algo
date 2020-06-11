#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

vector<int> nums;
int res;

void swap(int i, int j) {
	if (i == j) return;
	int temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}

int findMedIndex(int l, int r) {
	int mid = (l + r) / 2;
	if (nums[mid] > nums[l] && nums[mid] < nums[r]) return mid;
	if (nums[mid] > nums[r] && nums[mid] < nums[l]) return mid;
	if (nums[r] > nums[mid] && nums[r] < nums[l]) return r;
	if (nums[r] > nums[l] && nums[r] < nums[mid]) return r;
	return l;
}

void qsort(int l, int r) {
	if (l >= r) return;
	res += (r - l);

	int piv;
	// pivot selection
	// problem 1 (first element)
	// problem 2 (last element)
	// swap(l, r);
	// problem 3 (median of three)
	int medIndex = findMedIndex(l, r);
	swap(l, medIndex);

	piv = nums[l];
	int i = l;
	for (int j = l + 1; j <= r; j++) {
		if (nums[j] < piv) {
			i++;
			swap(i, j);
		}
	}
	swap(l, i);
	qsort(l, i - 1);
	qsort(i + 1, r);
}

int main() {
	int a;
	ifstream inputFile("input.txt");
	while (inputFile >> a) {
		nums.push_back(a);
	}
	inputFile.close();
	res = 0;
	qsort(0, nums.size() - 1);
	for (int& num : nums) cout << num << endl;
	cout << res << endl;
	return 0;
}
