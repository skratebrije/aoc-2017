#include <iostream>
#include <math.h>
using namespace std;

int a_start = 783;
int b_start = 325;

int a_factor = 16807;
int b_factor = 48271;

long modulo = 2147483647;
long compare = long(pow(2,16));

int iterations = 40000000;
int iterations2 = 5000000;

int get_matches() {
	int matches = 0;
	unsigned long long a = a_start;
	unsigned long long b = b_start;
	for (int i=0; i<iterations; i++) {
		a = (a*a_factor) % modulo;
		b = (b*b_factor) % modulo;
		if (a % compare == b % compare) {
			matches++;
		}
	}
	return matches;
}

int get_matches2() {
	int matches = 0;
	unsigned long long a = a_start;
	unsigned long long b = b_start;
	for (int i=0; i<iterations2; i++) {
		a = (a*a_factor) % modulo;
		while (a % 4 != 0) {
			a = (a*a_factor) % modulo;
		}
		b = (b*b_factor) % modulo;
		while (b % 8 != 0) {
			b = (b*b_factor) % modulo;
		}

		if (a % compare == b % compare) {
			matches++;
		}
	}
	return matches;
}

void day15() {
	//cout << get_matches() << endl;
	cout << get_matches2() << endl;
	//336
}
