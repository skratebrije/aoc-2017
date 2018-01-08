#include <iostream>
#include "day18.h"
#include <math.h>
using namespace std;

long run_coprocessor(vector< vector<string> > *v) {
	map<string, long> m;
	int index = 0;
	int count_mul = 0;
	while (index >= 0 && index < v->size()) {
		vector<string> i = v->at(index);
		bool successful_jump = false;
		if (i[0] == "set") {
			m[i[1]] = get_val(i[2], &m);
		} else if (i[0] == "sub") {
			m[i[1]] -= get_val(i[2], &m);
		} else if (i[0] == "mul") {
			m[i[1]] *= get_val(i[2], &m);
			count_mul++;
		} else if (i[0] == "jnz") {
			if (get_val(i[1], &m) != 0) {
				successful_jump = true;
				index += get_val(i[2], &m);
			}
		}
		if (!successful_jump) {
			index++;
		}
	}
	return count_mul;
}

int translation() {
	// testing how many multiples of 17 from 109300 to 126300, inclusive, are not prime
	int count = 0;
	for (int i=109300; i<=126300; i+=17) {
		bool is_prime = true;
		for (int j=2; j<=(int)sqrt(i); j++) {
			if (i%j==0) {
				is_prime = false;
			}
		}
		if (!is_prime) {
			count++;
		}
	}
	return count;
}

void day23() {
	vector< vector<string> > v;
	get_input_instructions(&v, "input/day23input.txt");
	//cout << run_coprocessor(&v) << endl;
	cout << translation();
}
