#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <tuple>
using namespace std;

int read_input_day13(map<int, tuple<int, int, int> > *m) {
	//tuple contains <position, range, delta>
	int max_depth = 0;
	ifstream file("input/day13input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream instream(line);
			string token;
			bool got_depth = false;
			int depth;
			int range;
			while (getline(instream, token, ' ')) {
				if (!got_depth) {
					depth = stoi(token.substr(0, token.length()-1));
					got_depth = true;
				} else {
					range = stoi(token);
				}
			}
			m->insert(make_pair(depth, make_tuple(1, range, 1)));
			if (depth > max_depth) {
				max_depth = depth;
			}
		}
	}
	return max_depth;
}

int trespass(map<int, tuple<int, int, int> > m, int max_depth) {
	int sum = 0;

	for (int packet = 0; packet <= max_depth; packet++) {
		// check for collision
		if (m.count(packet) == 1) {
			if (get<0>(m[packet]) == 1) {
				sum += get<1>(m[packet])*packet;
			}
		}

		// update scanner positions
		for (pair<int, tuple<int, int, int>& > p : m) {
			if (get<1>(p.second) > 1) {
				get<0>(p.second) += get<2>(p.second);
				if (get<0>(p.second) == 1) {
					get<2>(p.second) = 1;
				} else if (get<0>(p.second) == get<1>(p.second)) {
					get<2>(p.second) = -1;
				}
			}
		}
	}

	return sum;
}

int get_min_delay(map<int, tuple<int, int, int> > *m) {
	int delay = -1;
	bool collision = true;
	while (collision) {
		delay++;
		collision = false;
		for (pair<int, tuple<int, int, int> > p : *m) {
			if ((delay + p.first) % (2*(get<1>(p.second)-1)) == 0) {
				collision = true;
				break;
			}
		}
	}
	return delay;
}

void day13() {
	map<int, tuple<int, int, int> > m;
	int max_depth = read_input_day13(&m);
	//cout << trespass(m, max_depth);
	cout << get_min_delay(&m);
}
