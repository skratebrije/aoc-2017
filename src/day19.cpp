#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;

void read_input_day19(vector< vector<char> > *v) {
	ifstream file("input/day19input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			vector<char> v_internal;
			for (char c: line) {
				v_internal.push_back(c);
			}
			v->push_back(v_internal);
		}
	}
}

int find_start(vector<char> *v0) {
	for (int i=0; i<v0->size(); i++) {
		if (v0->at(i) == '|') {
			return i;
		}
	}
	return -1;
}

bool in_bounds(pair<int, int> *p, vector< vector<char> > *v) {
	return (p->first >= 0 && p->first < v->size() && p->second >= 0 && p->second < v->at(0).size());
}

// return '!' if out of bounds or not allowed
char get(pair<int, int> *p, vector< vector<char> > *v, pair<int, int> *bad) {
	if (!in_bounds(p,v)) {
		return '!';
	}
	if (p->first == bad->first && p->second == bad->second) {
		return '!';
	}
	return v->at(p->first).at(p->second);
}

bool get_next_position(pair<int, int> *cur, pair<int, int> *next, vector< vector<char> > *v, char look_for_dir, pair<int, int> *bad) {
	if (look_for_dir == '|') {
		// try up
		next->first = cur->first-1;
		next->second = cur->second;
		while (true) {
			char c = get(next, v, bad);
			if (c=='!' || c==' ') {
				break;
			}
			if (c==look_for_dir || c=='+' || isalpha(c)) {
				return true;
			}
			next->first-=1;
		}

		// try down
		next->first = cur->first+1;
		while (true) {
			char c = get(next, v, bad);
			if (c=='!' || c==' ') {
				break;
			}
			if (c==look_for_dir || c=='+' || isalpha(c)) {
				return true;
			}
			next->first+=1;
		}
	} else {
		// try left
		next->first = cur->first;
		next->second = cur->second-1;
		while (true) {
			char c = get(next, v, bad);
			if (c=='!' || c==' ') {
				break;
			}
			if (c==look_for_dir || c=='+' || isalpha(c)) {
				return true;
			}
			next->second-=1;
		}

		// try right
		next->second = cur->second+1;
		while (true) {
			char c = get(next, v, bad);
			if (c=='!' || c==' ') {
				break;
			}
			if (c==look_for_dir || c=='+' || isalpha(c)) {
				return true;
			}
			next->second+=1;
		}
	}

	return false;
}

pair<string, int> trace(vector< vector<char> > *v) {
	string s = "";
	pair<int, int> p = make_pair(-1, find_start(&(v->at(0))));
	pair<int, int> p_bad = make_pair(-2, find_start(&v->at(0)));
	pair<int, int> last_plus = make_pair(p.first, p.second);
	char look_for_dir = '|';
	int num_steps = 0;
	while (true) {
		pair<int, int> next_p;
		if (!get_next_position(&p, &next_p, v, look_for_dir, &p_bad)) {
			num_steps += (abs(last_plus.first-p.first) + abs(last_plus.second-p.second));
			break;
		} else {
			char c = get(&next_p, v, &p_bad);
			if (c == '+') {
				look_for_dir = ((look_for_dir=='|') ? '-' : '|');
				num_steps += (abs(last_plus.first-next_p.first) + abs(last_plus.second-next_p.second));
				last_plus.first = next_p.first;
				last_plus.second = next_p.second;
			} else if (isalpha(c)) {
				s += c;
			}
		}
		p_bad.first = p.first;
		p_bad.second = p.second;
		p.first = next_p.first;
		p.second = next_p.second;
	}
	return make_pair(s, num_steps);
}

void day19() {
	vector< vector<char> > v;
	read_input_day19(&v);
	//cout << trace(&v).first << endl;
	cout << trace(&v).second << endl;
}
