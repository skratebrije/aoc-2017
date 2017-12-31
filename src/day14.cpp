#include "day10.h"
#include <bitset>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <queue>
using namespace std;

string input_day14 = "ljoxqyyw";

bitset<4> hex_to_bin(char c) {
	stringstream ss;
	unsigned n;
	ss << hex << c;
	ss >> n;
	bitset<4> b(n);
	return b;
}

int get_used(set< pair<int, int> > *s) {
	int used = 0;
	for (int i=0; i<128; i++) {
		vector<int> lengths;
		string key = input_day14 + "-" + to_string(i);
		string knot = knot_hash(dense_hash(sparse_hash(transform_lengths(key))));
		for (int j=0; j<knot.length(); j++) {
			bitset<4> b = hex_to_bin(knot[j]);
			for (int k=0; k<4; k++) {
				if (b[3-k] == 1) { s->insert(make_pair(i, j*4+k)); }
			}
			used += b.count();
		}
	}
	return used;
}

void check_around(set<pair<int, int> > *s, queue<pair<int, int> > *q, pair<int, int> *p, int a, int b) {
	pair<int, int> n = make_pair(p->first + a, p->second + b);
	if (s->count(n) == 1) {
		s->erase(n);
		q->push(n);
	}
}

int get_regions(set< pair<int, int> > *s) {
	int region_num = 0;
	map<pair<int, int>, int> m;
	while (!s->empty()) {
		region_num++;
		queue<pair<int, int> > explore;
		explore.push(*(s->begin()));
		s->erase(s->begin());
		while (!explore.empty()) {
			pair<int, int> p = explore.front();
			explore.pop();
			m.insert(make_pair(make_pair(p.first, p.second), region_num));
			check_around(s, &explore, &p, 0, -1);
			check_around(s, &explore, &p, 0, 1);
			check_around(s, &explore, &p, 1, 0);
			check_around(s, &explore, &p, -1, 0);
		}
	}
	return region_num;
}

void day14() {
	set< pair<int, int> > s;
	int num_used = get_used(&s);
	//cout << num_used;
	cout << get_regions(&s);
}
