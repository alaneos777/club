#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9+7;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> x(n);
	for(int& xi : x){
		cin >> xi;
	}
	vector<int> s(n);
	for(int i = 0; i < n; ++i){
		s[i] = (i-1>=0 ? s[i-1] : 0) + x[i];
		if(s[i] >= mod) s[i] -= mod;
		if(s[i] < 0) s[i] += mod;
	}
	vector<int> t(n);
	for(int i = 0; i < n; ++i){
		t[i] = (i-1>=0 ? t[i-1] : 0) + s[i];
		if(t[i] >= mod) t[i] -= mod;
	}

	vector<int> left(n), right(n);
	stack<int> aux;
	aux.push(n-1);
	right[n-1] = n-1;
	for(int i = n-2; i >= 0; --i){
		while(!aux.empty() && x[i] >= x[aux.top()]){
			aux.pop();
		}
		if(aux.empty()){
			right[i] = n-1;
		}else{
			right[i] = aux.top()-1;
		}
		aux.push(i);
	}

	aux = stack<int>();
	aux.push(0);
	left[0] = 0;
	for(int i = 1; i < n; ++i){
		while(!aux.empty() && x[i] >= x[aux.top()]){
			aux.pop();
		}
		if(aux.empty()){
			left[i] = 0;
		}else{
			left[i] = aux.top()+1;
		}
		aux.push(i);
	}

	lli ans = 0;
	for(int i = 0; i < n; ++i){
		int a = left[i], b = right[i];
		ans += (lli(i-a+1) * (t[b] - (i-1 >= 0 ? t[i-1] : 0)) % mod - lli(b-i+1) * ((i-1 >= 0 ? t[i-1] : 0) - (a-2 >= 0 ? t[a-2] : 0)) % mod) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	cout << ans << "\n";

	return 0;
}