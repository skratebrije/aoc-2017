#include <iostream>
#include <map>
using namespace std;

int num_steps = 12173597;

void step(map<int, bool> *m, int *pos, char *state) {
	switch (*state) {
	case 'A':
		if (m->count(*pos) == 0 || !m->at(*pos)) {
			(*m)[*pos] = true;
			(*pos)++;
			*state = 'B';
			break;
		} else {
			(*m)[*pos] = false;
			(*pos)--;
			*state = 'C';
		}
		break;
	case 'B':
		if (m->count(*pos) == 0 || !m->at(*pos)) {
			(*m)[*pos] = true;
			(*pos)--;
			*state = 'A';
		} else {
			(*m)[*pos] = true;
			(*pos)++;
			*state = 'D';
		}
		break;
	case 'C':
		if (m->count(*pos) == 0 || !m->at(*pos)) {
			(*m)[*pos] = true;
			(*pos)++;
			*state = 'A';
		} else {
			(*m)[*pos] = false;
			(*pos)--;
			*state = 'E';
		}
		break;
	case 'D':
		if (m->count(*pos) == 0 || !m->at(*pos)) {
			(*m)[*pos] = true;
			(*pos)++;
			*state = 'A';
		} else {
			(*m)[*pos] = false;
			(*pos)++;
			*state = 'B';
		}
		break;
	case 'E':
		if (m->count(*pos) == 0 || !m->at(*pos)) {
			(*m)[*pos] = true;
			(*pos)--;
			*state = 'F';
		} else {
			(*m)[*pos] = true;
			(*pos)--;
			*state = 'C';
		}
		break;
	case 'F':
		if (m->count(*pos) == 0 || !m->at(*pos)) {
			(*m)[*pos] = true;
			(*pos)++;
			*state = 'D';
		} else {
			(*m)[*pos] = true;
			(*pos)++;
			*state = 'A';
		}
		break;
	}
}

int run_machine() {
	int pos = 0;
	char state = 'A';
	map<int, bool> m;
	for (int i=0; i<num_steps; i++) {
		step(&m, &pos, &state);
	}

	int checksum = 0;
	for (auto p : m) {
		if (p.second) {
			checksum++;
		}
	}
	return checksum;
}

void day25() {
	cout << run_machine() << endl;
}
