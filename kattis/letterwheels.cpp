#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> mult(string a, const string & b){
	reverse(a.begin(), a.end());
	int n = a.size();
	vector<int> c(n);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			int idx = i+j;
			if(idx >= n) idx -= n;
			c[idx] += (a[i]==b[j]);
		}
	}
	return c;
}

inline int get(int i, int n){
	int a = i, b = n-i;
	if(b >= n) b -= n;
	return min(a, b);
}

int solve(const string & a, const string & b, const string & c){
	vector<int> d = mult(b, a); //a shift against b
	vector<int> e = mult(b, c); //c shift against b
	vector<int> f = mult(a, c); //c shift against a
	int ans = 1e9;
	int n = a.size();
	for(int i = 0; i < n; ++i){
		int idx1 = i-1;
		if(idx1 < 0) idx1 += n;
		if(d[idx1] == 0){ // "b" y la rotacion de "a" no tienen caracteres en comun
			for(int j = 0; j < n; ++j){
				int idx2 = j-1, idx3 = j-i-1;
				if(idx2 < 0) idx2 += n;
				if(idx3 < 0) idx3 += n;
				if(e[idx2] == 0 && f[idx3] == 0){ // "b" y la rotacion de "c" no tienen caracteres en comun
					ans = min(ans, get(i, n) + get(j, n));
				}
			}
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string a, b, c;
	cin >> a >> b >> c;
	int ans = min({solve(a, b, c), solve(a, c, b), solve(b, a, c)});
	if(ans == 1e9) ans = -1;
	cout << ans << "\n";
	return 0;
}