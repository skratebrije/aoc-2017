#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

enum state_names {
	INDEX,
	TO,
	LIST
};

void update_sets(map<int, int> *m, vector<set <int> > *v, set<int> *group) {
	set<int> seen;
	set<int> superset;
	for (int i: *group) {
		if (m->count(i) == 1) {
			seen.insert(m->at(i));
		}
		superset.insert(i);
	}
	for (int i: seen) {
		for (int j: v->at(i)) {
			superset.insert(j);
		}
	}

	// create new vector with superset and remaining groups
	vector<set <int> > new_v;
	new_v.push_back(superset);
	for (int i=0; i<v->size(); i++) {
		if (seen.count(i) == 0) {
			new_v.push_back(v->at(i));
		}
	}
	*v = new_v;

	// reset map
	map<int, int> new_m;
	for (int i=0; i<v->size(); i++) {
		for (int j: v->at(i)) {
			new_m.insert(make_pair(j,i));
		}
	}
	*m = new_m;
}

int read_input_day12(bool total_groups) {
	map<int, int> m;
	vector<set <int> > v;
	ifstream file("input/day12input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream instream(line);
			string token;
			int state = INDEX;
			set<int> group;
			while (getline(instream, token, ' ')) {
				switch (state) {
				case INDEX:
					group.insert(stoi(token));
					state = TO;
					break;
				case TO:
					state = LIST;
					break;
				case LIST:
					if (token[token.length()-1] == ',') {
						token = token.substr(0, token.length()-1);
					}
					group.insert(stoi(token));
				}
			}
			update_sets(&m, &v, &group);
		}
	}

	if (total_groups) {
		return v.size();
	} else {
		return v[m[0]].size();
	}
}

void day12() {
	cout << read_input_day12(true);
}
