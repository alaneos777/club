#include <bits/stdc++.h>
using namespace std;

string f(int n, int pos){
	string pi;
	for(char c = 'A'; c-'A' < n; ++c){
		pi += c;
	}
	swap(pi[0], pi[1]);
	int maxi = 0;
	vector<string> st;
	do{
		int cnt = 0;
		string cpy = pi;
		for(char c = 'A'; c-'A' < n; ++c){
			if(cpy[c-'A'] == c) continue;
			int idx = -1;
			for(int i = 0; i < n; ++i){
				if(cpy[i] == c){
					idx = i;
					break;
				}
			}
			if(idx != n-1){
				reverse(cpy.begin() + idx, cpy.end());
				cnt++;
			}
			reverse(cpy.begin()+(c-'A'), cpy.end());
			cnt++;
		}
		if(cnt > maxi){
			st = {pi};
			maxi = cnt;
		}else if(cnt == maxi){
			st.push_back(pi);
		}
	}while(next_permutation(pi.begin(), pi.end()));
	return st[pos-1];
}

int main(){
	cout << f(11, 2011) << "\n";
	return 0;
}