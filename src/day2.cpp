#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
using namespace std;

vector< vector<int> > read_input_day2() {
	vector< vector<int> > input;
	ifstream file("src/day2input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream instream(line);
			vector<int> tokens;
			string token;
			while (getline(instream, token, '\t')) {
				tokens.push_back(stoi(token));
			}
			input.push_back(tokens);
		}
	}
	return input;
}

int get_checksum(vector< vector <int> > input) {
	int sum = 0;
	for (vector<int> row : input) {
		sum += (*max_element(row.begin(), row.end()) - *min_element(row.begin(), row.end()));
	}
	return sum;
}

int get_divisible_checksum(vector< vector <int> > input) {
	int sum = 0;
	for (vector<int> row : input) {
		for (int i=0; i<row.size(); i++) {
			for (int j=i+1; j<row.size(); j++) {
				if (row[i]%row[j] == 0) {
					sum += row[i]/row[j];
				} else if (row[j]%row[i] == 0) {
					sum += row[j]/row[i];
				}
			}
		}
	}
	return sum;
}

void day2() {
	vector< vector <int> > input = read_input_day2();
	//cout << get_checksum(input);
	cout << get_divisible_checksum(input);
}
