#include <iostream>
#include <vector>
using namespace std;

int steps = 356;

int circular() {
	vector<int> v;
	v.push_back(0);
	int p = 0;
	for (int i=1; i<=2017; i++) {
		p = (p+steps) % v.size() + 1;
		v.insert(v.begin()+p, i);
	}
	return v[(p+1)%2018];
}

int longer() {
	int p = 0;
	int latest = 0;
	for (int i=1; i<=50000000; i++) {
		p = (p+steps) % i;
		if (p == 0) {
			latest = i;
		}
		p++;
	}
	return latest;
}

void day17() {
	//cout << circular();
	cout << longer();
}
