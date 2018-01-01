#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

void get_input_day18(vector< vector<string> > *v) {
	ifstream file("input/day18input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			vector<string> instruction;
			istringstream instream(line);
			string token;
			while (getline(instream, token, ' ')) {
				instruction.push_back(token);
			}
			v->push_back(instruction);
		}
	}
}

long get_val(string s, map<string, long> *m) {
	if (isdigit(s[s.length()-1]) > 0) {
		return stoi(s);
	} else {
		if(m->count(s) == 1) {
			return m->at(s);
		} else {
			return 0;
		}
	}
}

long perform_sound_instructions(vector< vector<string> > *v) {
	map<string, long> m;
	long last_sound;
	long index = 0;
	while (index >= 0 && index < v->size()) {
		bool successful_jump = false;
		vector<string> i = v->at(index);
		if (i[0] == "snd") {
			last_sound = get_val(i[1], &m);
		} else if (i[0] == "set") {
			m[i[1]] = get_val(i[2], &m);
		} else if (i[0] == "add") {
			m[i[1]] += get_val(i[2], &m);
		} else if (i[0] == "mul") {
			m[i[1]] *= get_val(i[2], &m);
		} else if (i[0] == "mod") {
			m[i[1]] = m[i[1]] % get_val(i[2], &m);
		} else if (i[0] == "rcv") {
			if (get_val(i[1], &m) != 0) {
				return last_sound;
			}
		} else if (i[0] == "jgz") {
			if (get_val(i[1], &m) > 0) {
				successful_jump = true;
				index += get_val(i[2], &m);
			}
		}
		if (!successful_jump) {
			index++;
		}
	}
	return -1;
}

int do_instruction(vector<string> i, map<string, long> *m, queue<long> *my_queue, queue<long> *other_queue) {
	if (i[0] == "snd") {
		other_queue->push(get_val(i[1], m));
	} else if (i[0] == "set") {
		(*m)[i[1]] = get_val(i[2], m);
	} else if (i[0] == "add") {
		(*m)[i[1]] += get_val(i[2], m);
	} else if (i[0] == "mul") {
		(*m)[i[1]] *= get_val(i[2], m);
	} else if (i[0] == "mod") {
		(*m)[i[1]] = (*m)[i[1]] % get_val(i[2], m);
	} else if (i[0] == "rcv") {
		(*m)[i[1]] = my_queue->front();
		my_queue->pop();
	} else if (i[0] == "jgz") {
		if (get_val(i[1], m) > 0) {
			return get_val(i[2], m);
		}
	}
	return 1;
}

int perform_pair_instructions(vector< vector<string> > *v) {
	map<string, long> a_m;
	a_m["p"] = 0;
	map<string, long> b_m;
	b_m["p"] = 1;
	queue<long> a_q;
	queue<long> b_q;
	bool a_lock = false;
	bool b_lock = false;
	bool a_done = false;
	bool b_done = false;
	long a_index = 0;
	long b_index = 0;
	int b_send = 0;

	while (!((a_lock && b_lock) || (a_done && b_done))) {
		if (!a_done) {
			vector<string> i_a = v->at(a_index);
			if (i_a[0] == "rcv" && a_q.size() == 0) {
				a_lock = true;
			} else {
				a_index += do_instruction(i_a, &a_m, &a_q, &b_q);
				if (a_index < 0 || a_index >= v->size()) {
					a_done = true;
				}
			}
		}

		if (!b_done) {
			vector<string> i_b = v->at(b_index);
			if (i_b[0] == "rcv" && b_q.size() == 0) {
				b_lock = true;
			} else {
				if (i_b[0] == "snd") {
					b_send++;
				}
				b_index += do_instruction(i_b, &b_m, &b_q, &a_q);
				if (b_index < 0 || b_index >= v->size()) {
					b_done = true;
				}
			}
		}
	}

	return b_send;
}

void day18() {
	vector< vector<string> > v;
	get_input_day18(&v);
	//cout << perform_sound_instructions(&v);
	cout << perform_pair_instructions(&v);
}
