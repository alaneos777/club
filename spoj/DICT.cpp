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

		void InsertWord(string& word){
			Node* current = root;
			for(int i = 0; i < word.size(); i++){
				
				if(!exists(current, word[i])){
					current -> letters[word[i]] = new Node();
				}
				current = current -> letters[word[i]];
			}
			current -> isWord = true;
		}
	
		bool FindWord(string& word){
			Node* current = root;
			for(int i = 0; i < word.size(); i++){
				if(!exists(current, word[i]))
					return false;
				current = current -> letters[word[i]];
			}
			return current -> isWord;
		}	

		void printRec(Node * actual, string acum, int & count, bool first){
			if(actual->isWord && !first){
				cout << acum << "\n";
				count++;
			}
			for(pair<const char, Node*> & next : actual->letters){
				printRec(next.second, acum + next.first, count, false);
			}
		}

		int printWords(string & prefix){
			int count = 0;
			Node * actual = root;
			for(int i = 0; i < prefix.size(); i++){
				if(!exists(actual, prefix[i])) return 0;
				actual = actual->letters[prefix[i]];
			}
			printRec(actual, prefix, count, true);
			return count;
		}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	Trie * arbol = new Trie();
	int n, k;
	cin >> n;
	string word;
	for(int i = 0; i < n; i++){
		cin >> word;
		arbol->InsertWord(word);
	}
	cin >> k;
	for(int i = 1; i <= k; i++){
		cin >> word;
		cout << "Case #" << i << ":\n";
		int count = arbol->printWords(word);
		if(count == 0){
			cout << "No match.\n";
		}
	}
	return 0;
}