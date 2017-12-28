#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
using namespace std;

vector<int> lengths = {18,1,0,161,255,137,254,252,14,95,165,33,181,168,2,188};
string input = "18,1,0,161,255,137,254,252,14,95,165,33,181,168,2,188";
vector<int> add_lengths = {17,31,73,47,23};

void initialize_vals(vector<int> *v) {
	for (int i=0; i<256; i++) {
		v->push_back(i);
	}
}

void transform_lengths(vector<int> *l) {
	for (char c : input) {
		l->push_back(c);
	}
	for (int i : add_lengths) {
		l->push_back(i);
	}
}

void swap(vector<int> *v, int start, int length) {
	int temp;
	for (int i=0; i<floor(length/2); i++) {
		temp = (*v)[(start+i)%v->size()];
		(*v)[(start+i)%v->size()] = (*v)[(start+length-1-i)%v->size()];
		(*v)[(start+length-1-i)%v->size()] = temp;
	}
}

int compute_hash() {
	int pos = 0;
	int skip = 0;
	vector<int> vals;
	initialize_vals(&vals);

	for (int length: lengths) {
		swap(&vals, pos, length);
		pos = (pos+length+skip) % vals.size();
		skip++;
	}

	return vals[0]*vals[1];
}

vector<int> sparse_hash() {
	int pos = 0;
	int skip = 0;
	vector<int> vals;
	vector<int> ascii_lengths;
	initialize_vals(&vals);
	transform_lengths(&ascii_lengths);

	for (int i=0; i<64; i++) {
		for (int length: ascii_lengths) {
			swap(&vals, pos, length);
			pos = (pos+length+skip) % vals.size();
			skip++;
		}
	}
	return vals;
}

int compute_xor(vector<int> *vals, int start, int end) {
	int product = (*vals)[start] ^ (*vals)[start+1];
	for (int i=2; i<(end-start); i++) {
		product = product ^ (*vals)[start+i];
	}
	return product;
}

vector<int> dense_hash(vector<int> vals) {
	vector<int> dense_vals;
	for (int i=0; i<16; i++) {
		dense_vals.push_back(compute_xor(&vals, 16*i, 16*(i+1)));
	}
	return dense_vals;
}

string knot_hash(vector<int> vals) {
	stringstream ss;
	for (int i=0; i<vals.size(); i++) {
		ss << setfill('0') << setw(2) << hex << vals[i];
	}
	return ss.str();
}

void day10() {
	//cout << compute_hash();
	cout << knot_hash(dense_hash(sparse_hash()));
}
