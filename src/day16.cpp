#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <vector>
using namespace std;

long abillion = pow(10, 9);

void initialize(vector<char> *v) {
	for (char i='a'; i<='p'; i++) {
		v->push_back(i);
	}
}

void spin(vector<char> *v, int amount) {
	for (int i=0; i<amount; i++) {
		v->insert(v->begin(), v->back());
		v->pop_back();
	}
}

void exchange(vector<char> *v, int pos1, int pos2) {
	char temp = v->at(pos1);
	v->at(pos1) = v->at(pos2);
	v->at(pos2) = temp;
}

void partner(vector<char> *v, char p1, char p2) {
	for (int i=0; i<v->size(); i++) {
		if (v->at(i) == p1) {
			v->at(i) = p2;
		} else if (v->at(i) == p2) {
			v->at(i) = p1;
		}
	}
}

void perform(vector<char> *v, string token) {
	if (token[0] == 's') {
		spin(v, stoi(token.substr(1,token.size()-1)));
	} else if (token[0] == 'x') {
		int backslash = token.find("/");
		exchange(v, stoi(token.substr(1,backslash-1)), stoi(token.substr(backslash+1,token.size()-backslash-1)));
	} else if (token[0] == 'p') {
		partner(v, token[1], token[3]);
	}
}

string perform_once() {
	vector<char> v;
	initialize(&v);
	cout << "starting vector: " << string(v.begin(),v.end()) << endl;

	ifstream file("src/day16input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream instream(line);
			string token;
			while (getline(instream, token, ',')) {
				perform(&v, token);
			}
		}
	}

	return string(v.begin(),v.end());
}

string perform_many(long times) {
	vector<char> v;
	vector<string> orders;
	initialize(&v);

	long i;
	for (i=0; i<times; i++) {
		ifstream file("src/day16input.txt");
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				istringstream instream(line);
				string token;
				while (getline(instream, token, ',')) {
					perform(&v, token);
				}
			}

		}
		file.close();
		string order = string(v.begin(), v.end());
		if (orders.size() > 0 && orders[0] == order) {
			break;
		} else {
			orders.push_back(order);
		}
	}
	return orders[(times-1)%i];
}

void day16() {
	//cout << perform_once();
	cout << perform_many(abillion);
}
