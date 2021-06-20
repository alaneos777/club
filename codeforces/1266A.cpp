#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<string> four;
	for(int i = 0; i < 100; i += 20){
		four.push_back(to_string(i));
		if(i < 10) four.back() = string("0") + four.back();
	}
	int t;
	cin >> t;
	while(t--){
		string s;
		cin >> s;
		int sum = 0;
		vector<int> freq(10);
		for(char c : s){
			int d = c-'0';
			sum += d;
			freq[d]++;
		}
		bool div20 = false;
		for(const string& f : four){
			div20 |= (freq[f[0]-'0']>0 && freq[f[1]-'0']>0 && (f[0] != f[1] || freq[f[0]-'0']>1));
		}
		bool div3 = (sum % 3 == 0);
		if(div3 && div20){
			cout << "red\n";
		}else{
			cout << "cyan\n";
		}
	}
	return 0;
}