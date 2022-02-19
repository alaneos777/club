#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct Node{
  	bool isWord = false;
	map<char, Node*> letters;
	bool win, lose;
	void calc(){
		if(letters.size() == 0){
			win = false;
			lose = true;
		}else{
			win = false;
			lose = false;
			for(auto[_, v] : letters){
				v->calc();
				win |= !(v->win);
				lose |= !(v->lose);
			}
		}
	}
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
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	Trie t;
	while(n--){
		string s;
		cin >> s;
		t.InsertWord(s);
	}
	t.root->calc();
	bool win = t.root->win;
	bool lose = t.root->lose;
	if(!win){
		cout << "Second\n";
	}else if(win && lose){
		cout << "First\n";
	}else if(win && !lose){
		if(k%2 == 1){
			cout << "First\n";
		}else{
			cout << "Second\n";
		}
	}
	return 0;
}