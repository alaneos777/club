#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(string & text, string & pattern){
	vector<int> aux(pattern.size());
	int j = 0, i = 1;
	while(i < pattern.size()){
		if(pattern[i] == pattern[j]){
			aux[i++] = ++j;
		}else{
			if(j == 0){
				aux[i++] = 0;
			}else{
				j = aux[j - 1];
			}
		}
	}

	vector<int> ans;
	i = j = 0;
	while(i < text.size() && j < pattern.size()){
		if(text[i] == pattern[j]){
			i++, j++;
			if(j == pattern.size()){
				ans.push_back(i - j);
				j = aux[j - 1];
			}
		}else{
			if(j == 0){
				i++;
			}else{
				j = aux[j - 1];
			}
		}
	}

	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--){
		string a, b;
		cin >> a >> b;
		vector<int> positions = kmp(a, b);
		if(positions.size() == 0){
			cout << "Not Found\n";
		}else{
			cout << positions.size() << "\n";
			for(int pos : positions){
				cout << pos + 1 << " ";
			}
			cout << "\n";
		}
		if(t > 0) cout << "\n";
	}
	return 0;
}