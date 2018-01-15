#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <set>
#include <vector>
using namespace std;

void read_input_day24(set< pair<int,int> > *s) {
	ifstream file("input/day24input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			smatch sm;
			regex r("(\\d+)/(\\d+)");
			if (regex_match(line, sm, r)) {
				s->insert(make_pair(stoi(sm[1]), stoi(sm[2])));
			}
		}
	}
}

void initialize_paths(map< int, set< vector< int > > > *m, set< pair<int,int> > *s) {
	set< vector< int > > start_set;
	for (pair<int,int> p : *s) {
		if (p.first == 0) {
			vector<int> v;
			v.push_back(p.first);
			v.push_back(p.second);
			start_set.insert(v);
		} else if (p.second == 0) {
			vector<int> v;
			v.push_back(p.second);
			v.push_back(p.first);
			start_set.insert(v);
		}
	}
	m->insert(make_pair(1, start_set));
}

bool unused(vector<int> *v, pair<int, int> *p) {
	for (int i=0; i<v->size()-1; i++) {
		if (v->at(i) == p->first && v->at(i+1) == p->second) {
			return false;
		}
		if (v->at(i) == p->second && v->at(i+1) == p->first) {
			return false;
		}
	}
	return true;
}

bool extend_paths(map< int, set< vector< int > > > *m, set< pair<int,int> > *s, int last_length) {
	set< vector< int > > next_set;
	for (auto bridge : m->at(last_length)) {
		for (auto possible : *s) {
			if (unused(&bridge, &possible)) {
				if (possible.first == bridge.back()) {
					vector<int> v(bridge);
					v.push_back(possible.second);
					next_set.insert(v);
				} else if (possible.second == bridge.back()) {
					vector<int> v(bridge);
					v.push_back(possible.first);
					next_set.insert(v);
				}
			}
		}
	}
	if (next_set.size() == 0) {
		return false;
	} else {
		m->insert(make_pair(last_length+1, next_set));
		return true;
	}
}

int get_path_strength(vector< int > *v) {
	int sum = 0;
	for (int i=0; i<v->size(); i++) {
		sum += v->at(i);
		if (i>0 && i<v->size()-1) {
			sum += v->at(i);
		}
	}
	return sum;
}

int get_strongest_path(map< int, set< vector< int > > > *m) {
	int best = 0;
	for (auto p : *m) {
		for (auto v : p.second) {
			int strength = get_path_strength(&v);
			if (strength > best) {
				best = strength;
			}
		}
	}
	return best;
}

int get_strongest_of_longest_paths(map< int, set< vector< int > > > *m) {
	int longest_length = 0;
	for (auto p : *m) {
		if (p.first > longest_length) {
			longest_length = p.first;
		}
	}

	int best = 0;
	for (auto v : m->at(longest_length)) {
		int strength = get_path_strength(&v);
		if (strength > best) {
			best = strength;
		}
	}
	return best;
}

int build_bridges(set< pair<int,int> > *s, map< int, set< vector< int > > > *m) {
	initialize_paths(m, s);
	int last_length = 1;
	while (true) {
		if (!extend_paths(m, s, last_length)) {
			break;
		}
		last_length++;
	}
}

void day24() {
	set< pair<int,int> > s;
	map< int, set< vector< int > > > m;
	read_input_day24(&s);
	build_bridges(&s, &m);
	//cout << get_strongest_path(&m) << endl;
	cout << get_strongest_of_longest_paths(&m) << endl;
}
