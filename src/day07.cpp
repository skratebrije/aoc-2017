#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

void read_input_day7(map<string, string> *m, map<string, pair<int, vector<string> > > *mr) {
	ifstream file("input/day07input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream instream(line);
			string token;
			int weight;
			bool got_node = false;
			bool got_weight = false;
			bool in_leaves = false;
			string node;
			vector<string> leaves;
			while (getline(instream, token, ' ')) {
				if (!got_node) {
					node = token;
					got_node = true;
				} else if (!got_weight) {
					weight = stoi(token.substr(1, token.length()-2));
					got_weight = true;
				} else if (token == "->") {
					in_leaves = true;
				} else if (in_leaves) {
					// chop off ending comma if present
					if (token[token.length()-1] == ',') {
						token = token.substr(0, token.length()-1);
					}
					// key is leaf, value is parent
					// cout << "inserting leaf " << token << " to parent " << node << endl;
					m->insert(make_pair(token, node));
					leaves.push_back(token);
				}
			}
			mr->insert(make_pair(node, make_pair(weight, leaves)));
		}
	}
}

int subtree_weight(map< string, pair< int, vector<string> > > *mr, string node) {
	if (mr->at(node).second.size() == 0) {
		return mr->at(node).first;
	} else {
		int weight = mr->at(node).first;
		for (string subnode : mr->at(node).second) {
			weight += subtree_weight(mr, subnode);
		}
		return weight;
	}
}

int unbalanced(map< string, pair< int, vector<string> > > *mr, string node, int normal_sibling_weights) {
	cout << "looking at node " << node << endl;

	// create map of child subtree weights
	// key is weight of child subtree, value is vector of child node names with that weight
	map<int, vector<string> > freq;
	for (string subnode : mr->at(node).second) {
		int weight = subtree_weight(mr, subnode);
		if (freq.count(weight) == 1) {
			freq.at(weight).push_back(subnode);
		} else {
			vector<string> v;
			v.push_back(subnode);
			freq.insert(make_pair(weight, v));
		}
	}

	// the node itself is the problem if the children are balanced, otherwise continue
	// looking for the problem node in the oddball child subtree
	if (freq.size() == 2) {
		// the children of this node are unbalanced
		cout << "children are unbalanced" << endl;
		pair<int, vector<string> > outsider;
		pair<int, vector<string> > normal;
		for (pair<int, vector<string>> p : freq) {
			if (p.second.size() == 1) {
				outsider = p;
			} else {
				normal = p;
			}
		}
		return unbalanced(mr, outsider.second[0], normal.first);
	} else {
		// the node passed in is the problem; need to compare it to siblings
		cout << "children are fine; this node is the problem" << endl;
		int adjust = normal_sibling_weights - subtree_weight(mr, node);
		return mr->at(node).first + adjust;
	}
}

string get_root(map<string,string> m) {
	string arbitrary_node = m.begin()->first;
	while (m.count(arbitrary_node) == 1) {
		// cout << "currently at " << arbitrary_node << endl;
		arbitrary_node = m.at(arbitrary_node);
	}
	return arbitrary_node;
}

void day7() {
	map<string, string> m;
	map< string, pair< int,vector<string> > > mr;
	read_input_day7(&m, &mr);
	string root = get_root(m);
	//cout << root;
	cout << unbalanced(&mr, root, 0);
}
