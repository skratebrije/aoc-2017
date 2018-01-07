#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <vector>
using namespace std;

void read_input_day22(map<pair<int,int>, char> *m) {
	ifstream file("input/day22input.txt");
	if (file.is_open()) {
		string line;
		int row = 0;
		while (getline(file, line)) {
			for (int col=0; col<line.size(); col++) {
				if (line[col]=='#') { 	//infected
					m->insert(make_pair(make_pair(row,col),'i'));
				} else {					//clean
					m->insert(make_pair(make_pair(row,col),'c'));
				}
			}
			row++;
		}
	}
}

int grow(int times, map<pair<int,int>, char> *m, bool evolved_mode) {
	int side = (int) sqrt(m->size());
	pair<int,int> p = make_pair((int)side/2, (int)side/2);
	vector< pair<int,int> > deltas;
	deltas.push_back(make_pair(-1,0)); 	//up
	deltas.push_back(make_pair(0,1));	//right
	deltas.push_back(make_pair(1,0));	//down
	deltas.push_back(make_pair(0,-1));	//left
	int dir = 0;
	int infections = 0;

	for (int i=0; i<times; i++) {
		if (evolved_mode) {
			if (m->count(p) == 0 || m->at(p)=='c') {		//clean, weaken and turn left
				dir = (dir+3)%4;
				(*m)[p] = 'w';
			} else if (m->at(p)=='i') {					//infected, flag and turn right
				dir = (dir+1)%4;
				m->at(p) = 'f';
			} else if (m->at(p)=='w') {					//weakened, infect and no turn
				m->at(p) = 'i';
				infections++;
			} else {										//flagged, clean and reverse
				dir = (dir+2)%4;
				m->at(p) = 'c';
			}
		} else {
			if (m->count(p) == 1 && m->at(p)=='i') {		//infected, clear and turn right
				dir = (dir+1)%4;
				m->at(p) = 'c';
			} else {										//clear, infect and turn left
				dir = (dir+3)%4;
				(*m)[p] = 'i';
				infections++;
			}
		}
		p.first += deltas[dir].first;
		p.second += deltas[dir].second;
	}

	return infections;
}

void day22() {
	map<pair<int,int>,char> m;
	read_input_day22(&m);
	//cout << grow(10000, &m, false);
	cout << grow(10000000, &m, true);
}
