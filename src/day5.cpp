#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> read_input_day5() {
	vector<int> v;
	ifstream file("src/day5input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			v.push_back(stoi(line));
		}
	}
	return v;
}

int exit(vector<int> instructions, bool more_complicated) {
	int position = 0;
	int moves = 0;
	int old_position;
	while (position >= 0 && position < instructions.size()) {
		old_position = position;
		position += instructions[position];
		if (instructions[old_position] >= 3) {
			instructions[old_position] -= 1;
		} else {
			instructions[old_position] += 1;
		}
		moves++;
	}
	return moves;
}

void day5() {
	cout << exit(read_input_day5(), true);
}
