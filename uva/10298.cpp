#include <bits/stdc++.h>
using namespace std;

int kmpTable(string & pattern){
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
	return aux.back();
}

int main(){
	ios_base::sync_with_stdio(0);
	string s;
	while(cin >> s && s != "."){
		int len = kmpTable(s);
		int n = s.size();
		if(n % (n - len) == 0){
			cout << n / (n - len) << "\n";
		}else{
			cout << "1\n";
		}
	}
	return 0;
}