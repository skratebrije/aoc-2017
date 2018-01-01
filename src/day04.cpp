#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

string reorder(string s) {
	int c[26];
	memset(c, 0, sizeof(c));
	for (int i=0; i<s.length(); i++) {
		c[s[i] - 'a'] += 1;
	}
	string rebuilt;
	for (int i=0; i<26; i++) {
		for (int j=0; j<c[i]; j++) {
			rebuilt += char(i + 'a');
		}
	}
	return rebuilt;
}

int unique_passphrases(bool check_anagrams) {
	int count = 0;
	set<string> input;
	bool all_unique = true;
	ifstream file("input/day04input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream instream(line);
			string token;
			while (getline(instream, token, ' ')) {
				if (check_anagrams) {
					token = reorder(token);
				}
				if (input.count(token) == 1) {
					all_unique = false;
				}
				input.insert(token);
			}
			if (all_unique) {
				count++;
			}
			input.clear();
			all_unique = true;
		}
	}
	return count;
}

void day4() {
	cout << unique_passphrases(true);
}
