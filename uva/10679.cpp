#include <bits/stdc++.h>
using namespace std;

bool kmp(string & text, string & pattern){
	vector<int> aux(pattern.size());
	int j = 0, i = 1;
	while(i < pattern.size()){
		if(pattern[i] == pattern[j]){
			aux[i++] = j++;
		}else{
			if(j == 0){
				aux[i++] = 0;
			}else{
				j = aux[j - 1];
			}
		}
	}

	i = j = 0;
	while(i < text.size() && j < pattern.size()){
		if(text[i] == pattern[j]){
			i++, j++;
		}else{
			if(j == 0){
				i++;
			}else{
				j = aux[j - 1];
			}
		}
	}

	return j == pattern.size();
}

int main(){
	ios_base::sync_with_stdio(0);
	int k;
	cin >> k;
	while(k--){
		string s;
		int q;
		cin >> s >> q;
		while(q--){
			string t;
			cin >> t;
			if(kmp(s, t)){
				cout << "y\n";
			}else{
				cout << "n\n";
			}
		}
	}
	return 0;
}