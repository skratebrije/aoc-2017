#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

struct instruction {
	string reg;
	string op;
	int amount;
	string condition_reg;
	string condition_op;
	int condition_amount;
};

enum parser_state {
	REGISTER,
	OPERATION,
	AMOUNT,
	IF,
	CONDITION_REGISTER,
	CONDITION_OPERATION,
	CONDITION_AMOUNT
};

void get_input_day8(vector<instruction> *instructions) {
	ifstream file("src/day8input.txt");

	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream instream(line);
			string token;
			parser_state state = REGISTER;
			instruction i;
			while (getline(instream, token, ' ')) {
				switch (state) {
				case REGISTER:
					i.reg = token;
					state = OPERATION;
					break;
				case OPERATION:
					i.op = token;
					state = AMOUNT;
					break;
				case AMOUNT:
					i.amount = stoi(token);
					state = IF;
					break;
				case IF:
					state = CONDITION_REGISTER;
					break;
				case CONDITION_REGISTER:
					i.condition_reg = token;
					state = CONDITION_OPERATION;
					break;
				case CONDITION_OPERATION:
					i.condition_op = token;
					state = CONDITION_AMOUNT;
					break;
				case CONDITION_AMOUNT:
					i.condition_amount = stoi(token);
					break;
				}
			}
			instructions->push_back(i);
		}
	}
}

void populate_registers(vector<instruction> *instructions, map<string, int> *registers) {
	for (instruction i: *instructions) {
		if (registers->count(i.reg) == 0) {
			registers->insert(make_pair(i.reg, 0));
		}
		if (registers->count(i.condition_reg) == 0) {
			registers->insert(make_pair(i.condition_reg, 0));
		}
	}
}

int follow_instructions(vector<instruction> *instructions, map<string, int> *registers) {
	int highest_val_seen = 0;
	for (instruction i: *instructions) {
		bool condition = false;
		if (i.condition_op == ">") {
			condition = (registers->at(i.condition_reg) > i.condition_amount);
		} else if (i.condition_op == "<") {
			condition = (registers->at(i.condition_reg) < i.condition_amount);
		} else if (i.condition_op == ">=") {
			condition = (registers->at(i.condition_reg) >= i.condition_amount);
		} else if (i.condition_op == "<=") {
			condition = (registers->at(i.condition_reg) <= i.condition_amount);
		} else if (i.condition_op == "==") {
			condition = (registers->at(i.condition_reg) == i.condition_amount);
		} else if (i.condition_op == "!=" ) {
			condition = (registers->at(i.condition_reg) != i.condition_amount);
		}
		if (!condition) {
			continue;
		}
		if (i.op == "inc") {
			registers->at(i.reg) += i.amount;
		} else if (i.op == "dec") {
			registers->at(i.reg) -= i.amount;
		}
		if (registers->at(i.reg) >= highest_val_seen) {
			highest_val_seen = registers->at(i.reg);
		}
	}
	return highest_val_seen;
}

int get_largest_val(map<string, int> *registers) {
	int largest = registers->begin()->second;
	for (pair<string, int> p: *registers) {
		if (p.second > largest) {
			largest = p.second;
		}
	}
	return largest;
}

void day8() {
	vector<instruction> instructions;
	map<string, int> registers;
	get_input_day8(&instructions);
	populate_registers(&instructions, &registers);
	int highest_val = follow_instructions(&instructions, &registers);
	//cout << get_largest_val(&registers);
	cout << highest_val;
}
