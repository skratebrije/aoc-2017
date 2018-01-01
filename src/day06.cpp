#include <iostream>
#include <map>
#include <vector>
using namespace std;

vector<int> v = {2,8,8,5,4,2,3,1,5,5,1,2,15,13,5,14};

int redistribute(bool total) {
	map< vector<int>, int > m;
	int moves = 0;
	m.insert(make_pair(v, moves));
	bool saw_repeat = false;
	int max_position;
	int redistribute;

	while (!saw_repeat) {
		max_position = max_element(v.begin(), v.end()) - v.begin();
		redistribute = v[max_position];
		v[max_position] = 0;
		for (int i=1; i<=redistribute; i++) {
			v[(max_position + i) % v.size()] += 1;
		}
		moves++;
		if (m.count(v) == 1) {
			saw_repeat = true;
		} else {
			m.insert(make_pair(v, moves));
		}
	}
	if (total) {
		return moves;
	}
	else {
		return moves - m.at(v);
	}
}

void day6() {
	cout << redistribute(false);
}
