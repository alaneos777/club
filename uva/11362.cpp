#include <bits/stdc++.h>
using namespace std;

class Node{
  	public:
		bool isWord;
		map <char, Node*> letters;
};

class Trie{
	private:
	Node* root;

	public:
		Trie(){
			root = new Node();
		}

		bool exists(Node * actual, char & c){
			return actual->letters.find(c) != actual->letters.end();
		}

		bool InsertWord(string& word){
			Node* current = root;
			for(int i = 0; i < word.size(); i++){
				
				if(!exists(current, word[i])){
					current -> letters[word[i]] = new Node();
				}
				if(current->isWord) return false;
				current = current -> letters[word[i]];

			}
			current -> isWord = true;
			return current->letters.size() == 0;
		}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t, n;
	string number;
	cin >> t;
	while(t--){
		cin >> n;
		Trie * arbol = new Trie();
		bool consistent = true;
		while(n--){
			cin >> number;
			if(consistent){
				consistent = arbol->InsertWord(number);
			}
		}
		if(consistent) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}