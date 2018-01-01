#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;


void flip(map<string, int> *m) {
	// flips across horizontal axis
	(*m)["n"] *= -1;
	(*m)["nw"] *= -1;
	(*m)["ne"] *= -1;
}

int reduce(map<string, int> m) {
	if (m["ne"] < 0 && m["nw"] < 0) {
		flip(&m);
	}

	if (m["ne"] > 0 && m["nw"] > 0) {
		if (m["ne"] > m["nw"]) {
			m["n"] += m["nw"];
			m["ne"] -= m["nw"];
			m["nw"] = 0;

		} else {
			m["n"] += m["ne"];
			m["nw"] -= m["ne"];
			m["ne"] = 0;
		}
	}

	if (m["n"] < 0) {
		flip(&m);
	}

	if (m["ne"] < 0) {
		int adjust = min(m["n"], -1*m["ne"]);
		m["n"] -= adjust;
		m["ne"] += adjust;
		m["nw"] += adjust;
	} else if (m["nw"] < 0) {
		int adjust = min(m["n"], -1*m["nw"]);
		m["n"] -= adjust;
		m["nw"] += adjust;
		m["ne"] += adjust;
	}

	return abs(m["n"]) + abs(m["ne"]) + abs(m["nw"]);
}

int read_input_day11(map<string, int> *m, bool find_farthest) {
	ifstream file("input/day11input.txt");
	int farthest = 0;
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream instream(line);
			string token;
			while (getline(instream, token, ',')) {
				if (token == "n") {
					(*m)["n"] += 1;
				} else if (token == "s") {
					(*m)["n"] -= 1;
				} else if (token == "ne") {
					(*m)["ne"] += 1;
				} else if (token == "sw") {
					(*m)["ne"] -= 1;
				} else if (token == "nw") {
					(*m)["nw"] += 1;
				} else if (token == "se") {
					(*m)["nw"] -= 1;
				}
				if (find_farthest) {
					int current_dist = reduce(*m);
					if (current_dist > farthest) {
						farthest = current_dist;
					}
				}
			}
		}
	}

	if (find_farthest) {
		return farthest;
	} else {
		return reduce(*m);
	}
}

void initialize_map(map<string, int> *m) {
	m->insert(make_pair("n", 0));
	m->insert(make_pair("ne", 0));
	m->insert(make_pair("nw", 0));
}

void day11() {
	map<string, int> m;
	initialize_map(&m);
	cout << read_input_day11(&m, true);
}
