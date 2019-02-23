#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s;
	cin >> s;
	int n = s.size();
	string lo = s.substr(0, n/2);
	bool same = true;
	for(int i = 0; i < (int)lo.size()-1; ++i){
		same &= (lo[i] == lo[i+1]);
	}
	if(same){
		cout << "Impossible\n";
	}else{
		bool one = false;
		for(int i = 1; i < n; ++i){
			string nueva = s.substr(i) + s.substr(0, i);
			string tmp = nueva;
			reverse(tmp.begin(), tmp.end());
			if(nueva == tmp && nueva != s){
				one = true;
				break;
			}
		}
		if(one) cout << "1\n";
		else cout << "2\n";
	}
	return 0;
}