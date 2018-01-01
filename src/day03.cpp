#include <map>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

int manhattan_distance() {
	int val = 347991;
	int ceiling = ceil(sqrt(val));
	if (ceiling % 2 == 0) {
		ceiling += 1;
	}
	int len = ceiling-1;

	int dist_from_corner = (int)(pow(ceiling,2)-val)%len;
	int discount = fmin(dist_from_corner, len - dist_from_corner);

	int final_dist = len - discount;
	return final_dist;
}

vector< pair<int, int> > get_surrounding_coords(pair<int, int> p) {
	vector< pair<int, int> > v;
	v.push_back(make_pair(p.first + 1, p.second + 1));
	v.push_back(make_pair(p.first + 1, p.second));
	v.push_back(make_pair(p.first + 1, p.second - 1));
	v.push_back(make_pair(p.first, p.second + 1));
	v.push_back(make_pair(p.first, p.second - 1));
	v.push_back(make_pair(p.first - 1, p.second + 1));
	v.push_back(make_pair(p.first - 1, p.second));
	v.push_back(make_pair(p.first - 1, p.second - 1));
	return v;
}

pair<int, int> get_coord(int index) {
	int ceiling = ceil(sqrt(index));
	if (ceiling % 2 == 0) {
		ceiling += 1;
	}
	int len = ceiling-1;
	pair<int, int> p = make_pair(len/2, -len/2);

	int dist_remain = pow(ceiling,2)-index;
	if (dist_remain <= len) {
		p.first = p.first - dist_remain;
		return p;
	}
	if (dist_remain <= len*2) {
		p.first = p.first - len;
		p.second = p.second + (dist_remain - len);
		return p;
	}
	if (dist_remain <= len*3) {
		p.first = p.first - len;
		p.second = p.second + len;
		p.first = p.first + (dist_remain - len*2);
		return p;
	}
	else {
		p.second = p.second + len;
		p.second = p.second - (dist_remain - len*3);
		return p;
	}
}

int sums() {
	int stop = 347991;

	map<pair<int,int>,int> m;
	int index = 1;
	int insert = 1;
	m.insert(make_pair(make_pair(0,0), insert));

	while (insert < stop) {
		index++;
		pair<int,int> position = get_coord(index);
		cout << "get coord for " << index << " is " << position.first << ", " << position.second << endl;
		vector< pair<int,int> > surrounding = get_surrounding_coords(position);
		insert = 0;
		for (pair<int,int> p : surrounding) {
			if (m.count(p) == 1) {
				insert += m.at(p);
			}
		}
		m.insert(make_pair(position, insert));
		cout << insert << endl;
	}

	return insert;
}

void day3() {
	//cout << manhattan_distance();
	cout << sums();
}
