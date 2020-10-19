#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int curr = 0;
int color[55][2][40][40][2];
int mem[55][2][40][40][2];

int dp(int pos, bool can, int ab, int bc, bool appears, const string & n){
	if(3*ab > (int)n.size() || -(int)n.size() > 3*bc || 3*bc > (int)n.size()) return 0;
	if(pos == n.size()) return ab == 0 && bc == 0 && appears;
	int & ans = mem[pos][can][ab+20][bc+20][appears];
	int & st = color[pos][can][ab+20][bc+20][appears];
	if(st == curr) return ans;
	st = curr;
	ans = 0;
	int limit = can ? 9 : n[pos]-'0';
	for(int d = 0; d <= limit; ++d){
		int AB = ab, BC = bc;
		if(d == 3) AB++;
		else if(d == 6) AB--, BC++;
		else if(d == 9) BC--;
		ans += dp(pos+1, can | d < limit, AB, BC, appears | (d == 3) | (d == 6) | (d == 9), n);
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int f(const string & n){
	curr++;
	return dp(0, false, 0, 0, false, n);
}

int valid(const string & n){
	int a = 0, b = 0, c = 0;
	for(char d : n){
		a += (d == '3');
		b += (d == '6');
		c += (d == '9');
	}
	return a == b && b == c && a >= 1;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		string a, b;
		cin >> a >> b;
		int ans = f(b) - f(a);
		if(ans < 0) ans += mod;
		if(valid(a)) ans = (ans + 1) % mod;
		cout << ans << "\n";
	}
	return 0;
}