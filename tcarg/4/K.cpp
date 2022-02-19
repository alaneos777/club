#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	if(n == 1){
		cout << "1\n";
		return 0;
	}
	int r = n%9, q = n/9;
	string s = string(1, r+'0')+string(q, '9');
	s.back()--;
	lli sum = 0;
	for(char c : s){
		sum += c-'0';
	}
	int x = -1;
	for(int i = 0; i < n; ++i){
		if((sum + 9*i) % n == 0){
			x = i;
			break;
		}
	}
	if(x == -1){
		cout << "-1\n";
	}else{
		s += string(x, '9');
		cout << s << "\n";
	}
	return 0;
}