#include <bits/stdc++.h>
using namespace std;

class Node{
  	public:
		int wordCount;
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

		int InsertWord(string& word){
			int count = 0;
			Node* current = root;
			for(int i = 0; i < word.size(); i++){
				
				if(!exists(current, word[i])){
					current -> letters[word[i]] = new Node();
				}
				current = current -> letters[word[i]];
				current->wordCount++;
				count = max(count, current->wordCount * (i + 1));
			}
			return count;
		}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t, n;
	string str;
	cin >> t;
	while(t--){
		int ans = 0;
		cin >> n;
		Trie * arbol = new Trie();
		while(n--){
			cin >> str;
			ans = max(ans, arbol->InsertWord(str));
		}
		cout << ans << "\n";
	}
	return 0;
}