#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <regex>
using namespace std;

string start = ".#...####";

void read_input_day21(map<string, string> *m) {
	ifstream file("input/day21input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			smatch sm;
			regex r("([./#]+)\\s=>\\s([./#]+)");
			regex_match(line, sm, r);
			m->insert(make_pair(sm[1], sm[2]));
		}
	}
}

string flip_x_2(string s) {
	string base = "";
	return base + s[2] + s[3] + '/' + s[0] + s[1];
}

string flip_y_2(string s) {
	string base = "";
	return base + s[1] + s[0] + '/' + s[3] + s[2];
}

string flip_x_3(string s) {
	string base = "";
	return base + s[6] + s[7] + s[8] + '/' + s[3] + s[4] + s[5] + '/' + s[0] + s[1] + s[2];
}

string flip_y_3(string s) {
	string base = "";
	return base + s[2] + s[1] + s[0] + '/' + s[5] + s[4] + s[3] + '/' + s[8] + s[7] + s[6];
}

vector<string> get_transformations(string s) {
	vector<string> v;
	string base = "";

	// s0 s1
	// s2 s3
	if (s.size() == 4) {
		v.push_back(base + s[0] + s[1] + '/' + s[2] + s[3]);	// s
		v.push_back(flip_x_2(s));
		v.push_back(flip_y_2(s));
		string r = base + s[1] + s[3] + s[0] + s[2]; // CCW 90
		v.push_back(flip_x_2(r));
		v.push_back(flip_y_2(r));
		r = base + s[3] + s[2] + s[1] + s[0]; // CCW 180
		v.push_back(flip_x_2(r));
		v.push_back(flip_y_2(r));
		r = base + s[2] + s[0] + s[3] + s[1]; // CCW 270
		v.push_back(flip_x_2(r));
		v.push_back(flip_y_2(r));
	}

	// s0 s1 s2
	// s3 s4 s5
	// s6 s7 s8
	if (s.size() == 9) {
		v.push_back(base + s[0] + s[1] + s[2] + '/' + s[3] + s[4] + s[5] + '/' + s[6] + s[7] + s[8]); // s
		v.push_back(flip_x_3(s));
		v.push_back(flip_y_3(s));
		string r = base + s[2] + s[5] + s[8] + s[1] + s[4] + s[7] + s[0] + s[3] + s[6]; // CCW 90
		v.push_back(flip_x_3(r));
		v.push_back(flip_y_3(r));
		r = base + s[8] + s[7] + s[6] + s[5] + s[4] + s[3] + s[2] + s[1] + s[0]; // CCW 180
		v.push_back(flip_x_3(r));
		v.push_back(flip_y_3(r));
		r = base + s[6] + s[3] + s[0] + s[7] + s[4] + s[1] + s[8] + s[5] + s[2]; // CCW 270
		v.push_back(flip_x_3(r));
		v.push_back(flip_y_3(r));
	}
	return v;
}

string lookup(string s, map<string, string> *m) {
	vector<string> transformations = get_transformations(s);
	for (string a : transformations) {
		if (m->count(a) == 1) {
			return m->at(a);
		}
	}
	return "x";
}

vector<string> divide(string s) {
	vector<string> v;
	string base = "";
	if (s.size()%4 == 0) {
		int b = (int) sqrt(s.size()/4);
		for (int j=0; j<b; j++) {
			for (int i=0; i<b; i++) {
				v.push_back(base + s[j*2*2*b+i*2] + s[j*2*2*b+i*2+1] + s[(j*2+1)*2*b+i*2] + s[(j*2+1)*2*b+i*2+1]);
			}
		}
	} else {
		int b = (int) sqrt(s.size()/9);
		for (int j=0; j<b; j++) {
			for (int i=0; i<b; i++) {
				v.push_back(base + s[j*3*3*b+i*3] + s[j*3*3*b+i*3+1] + s[j*3*3*b+i*3+2] + s[(j*3+1)*3*b+i*3] + s[(j*3+1)*3*b+i*3+1] + s[(j*3+1)*3*b+i*3+2] + s[(j*3+2)*3*b+i*3] + s[(j*3+2)*3*b+i*3+1] + s[(j*3+2)*3*b+i*3+2]);
			}
		}
	}
	return v;
}

string combine(vector<string> v) {
	int b = (int) sqrt(v.size());
	int square;
	if (v[0].size() == 11) {
		square = 3;
	} else if (v[0].size() == 19) {
		square = 4;
	}

	string s;
	for (int i=0; i<b; i++) {
		for (int k=0; k<square; k++) {
			for (int j=0; j<b; j++) {
				s += v[i*b+j].substr(k*(square+1), square);
			}
		}
	}
	return s;
}

string expand(int times, map<string, string> *m) {
	string s = start;
	for (int i=0; i<times; i++) {
		vector<string> divided = divide(s);
		vector<string> replacements;
		for (string a: divided) {
			replacements.push_back(lookup(a, m));
		}
		s = combine(replacements);
	}
	return s;
}

int count_on(string s) {
	int count = 0;
	for (char c : s) {
		if (c == '#') {
			count++;
		}
	}
	return count;
}

void day21() {
	map<string, string> m;
	read_input_day21(&m);
	//cout << count_on(expand(5, &m));
	cout << count_on(expand(18, &m));
}
