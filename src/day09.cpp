#include <iostream>
#include <fstream>
using namespace std;

int parse(bool count_garbage) {
	ifstream file("src/day09input.txt");
	char ch;
	int num_open_parens = 0;
	bool in_garbage = false;
	bool ignore_next = false;
	int sum = 0;
	int garbage_sum = 0;
	while (file >> ch) {
		if (ignore_next) {
			ignore_next = false;
		} else if (ch == '!') {
			ignore_next = true;
		} else if (in_garbage && ch == '>') {
			in_garbage = false;
		} else if (in_garbage) {
			garbage_sum++;
		} else if (ch == '<') {
			in_garbage = true;
		} else if (ch == '{') {
			num_open_parens++;
			sum += num_open_parens;
		} else if (ch == '}') {
			num_open_parens--;
		}
	}
	// cout << "have " << num_open_parens << " open parens at end \n";
	if (count_garbage) {
		return garbage_sum;
	} else {
		return sum;
	}
}

void day9() {
	cout << parse(true);
}
