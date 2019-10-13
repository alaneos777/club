#include <bits/stdc++.h>
using namespace std;

struct Node{
	map<char, Node*> letters;
	bool isWord = false;
};

struct Trie{
	Node* root;

	Trie(){
		root = new Node();
	}

	inline bool exists(Node * actual, const char & c){
		return actual->letters.find(c) != actual->letters.end();
	}

	void InsertWord(const string& word){
		Node* current = root;
		for(auto & c : word){
			if(!exists(current, c))
				current->letters[c] = new Node();
			current = current->letters[c];
		}
		current->isWord = true;
	}

	int rec(Node * actual){
		if(actual->letters.size() == 0){
			return 1;
		}
		int r = 0;
		for(auto & par : actual->letters){
			Node * next = par.second;
			r += rec(next);
		}
		if(actual->isWord){
			r++;
		}
		if(actual != root && r >= 2){
			r -= 2;
		}
		return r;
	}

	int ans(){
		return rec(root);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int n;
		cin >> n;
		Trie trie;
		for(int i = 0; i < n; ++i){
			string cad;
			cin >> cad;
			reverse(cad.begin(), cad.end());
			trie.InsertWord(cad);
		}
		cout << "Case #" << caso << ": " << n-trie.ans() << "\n";
	}
	return 0;
}