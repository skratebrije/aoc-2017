#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <tuple>
using namespace std;

struct Data {
	int p_x;
	int p_y;
	int p_z;
	int v_x;
	int v_y;
	int v_z;
	int a_x;
	int a_y;
	int a_z;
};

Data process(string line) {
	smatch sm;
	regex r("p=<(-?\\d+),(-?\\d+),(-?\\d+)>, v=<(-?\\d+),(-?\\d+),(-?\\d+)>, a=<(-?\\d+),(-?\\d+),(-?\\d+)>");
	regex_match(line, sm, r);
	Data d;
	d.p_x = stoi(sm[1]);
	d.p_y = stoi(sm[2]);
	d.p_z = stoi(sm[3]);
	d.v_x = stoi(sm[4]);
	d.v_y = stoi(sm[5]);
	d.v_z = stoi(sm[6]);
	d.a_x = stoi(sm[7]);
	d.a_y = stoi(sm[8]);
	d.a_z = stoi(sm[9]);
	return d;
}

void read_input_day20(vector<Data> *v) {
	ifstream file("input/day20input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			v->push_back(process(line));
		}
	}
}

void iterate(vector<Data> *v, int num_times, bool collisions) {
	for (int i=0; i<num_times; i++) {
		for (Data& d : (*v)) {
			d.v_x += d.a_x;
			d.v_y += d.a_y;
			d.v_z += d.a_z;
			d.p_x += d.v_x;
			d.p_y += d.v_y;
			d.p_z += d.v_z;
		}

		if (collisions) {
			map<tuple<int,int,int>, vector<int>> positions;
			vector<int> remove;
			for (int j=0; j<v->size(); j++) {
				Data& d = v->at(j);
				auto pos = make_tuple(d.p_x, d.p_y, d.p_z);
				if (positions.count(pos) == 0) {
					vector<int> a;
					a.push_back(j);
					positions[pos] = a;
				} else {
					positions[pos].push_back(j);
				}
			}
			for (auto p : positions) {
				if (p.second.size() > 1) {
					for (int j : p.second) {
						remove.push_back(j);
					}
				}
			}
			sort(remove.begin(), remove.end(), [](int a,int b){ return (a>b); });
			for (int j: remove) {
				v->erase(v->begin() + j);
			}
		}
	}
}

int get_closest(vector<Data> *v) {
	int closest = INT_MAX;
	int closest_index = -1;
	for (int j=0; j<v->size(); j++) {
		int dist = abs((*v)[j].p_x) + abs((*v)[j].p_y) + abs((*v)[j].p_z);
		if (dist < closest) {
			closest = dist;
			closest_index = j;
		}
	}
	return closest_index;
}

void day20() {
	vector<Data> v;
	read_input_day20(&v);
	//iterate(&v, 1000, false);
	//cout << get_closest(&v) << endl;
	iterate(&v, 1000, true);
	cout << v.size() << endl;
}
