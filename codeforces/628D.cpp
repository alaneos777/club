#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 1e9 + 7;

int mem[2010][2010][2];
int ten[2010];

int f(int pos, int rem, bool canUseAll, const vector<int> & num, int m, int D){
	if(pos == num.size()) return rem == 0;
	int & ans = mem[pos][rem][canUseAll];
	if(ans != -1) return ans;
	ans = 0;
	int limit = canUseAll ? 9 : num[pos];
	for(int d = 0; d <= limit; ++d){
		if((pos % 2 == 1 && d == D) || (pos % 2 == 0 && d != D)){
			ans += f(pos+1, (rem + ten[num.size()-1-pos]*d) % m, canUseAll | (d < limit), num, m, D);
			if(ans >= mod) ans -= mod;
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m, d;
	cin >> m >> d;
	ten[0] = 1 % m;
	for(int i = 1; i < 2010; ++i){
		ten[i] = ten[i-1] * 10 % m;
	}
	string l, r;
	cin >> l >> r;
	vector<int> a, b;
	for(char c : l){
		a.push_back(c - '0');
	}
	for(char c : r){
		b.push_back(c - '0');
	}
	a.back()--;
	for(int i = a.size()-1; i >= 0; --i){
		if(a[i] < 0){
			a[i] = 9;
			a[i-1]--;
		}else{
			break;
		}
	}
	memset(mem, -1, sizeof(mem));
	int ans = f(0, 0, false, b, m, d);
	memset(mem, -1, sizeof(mem));
	ans -= f(0, 0, false, a, m, d);
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}