#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int mex(const vector<int> & a){
	int n = a.size();
	vector<bool> b(n);
	for(int ai : a){
		if(ai < n) b[ai] = true;
	}
	for(int i = 0; i < n; ++i){
		if(!b[i]) return i;
	}
	return n;
}

int mem[1000][1000];
int g(int m, int n){
	if(m == 0 || n == 0) return 0;
	if(mem[m][n] != -1) return mem[m][n];
	vector<int> st;
	for(int d = m; d <= n; d += m){
		st.push_back(g(min(m, n-d), max(m, n-d)));
	}
	return mem[m][n] = mex(st);
}

const lli N = lli(1e4);
const long double phi = (1 + sqrtl(5)) / 2;

int main(){
	/*memset(mem, -1, sizeof(mem));
	int sum = 0;
	for(int m = 1; m < 200; ++m){
		int cnt = 0;
		for(int n = m+1; n <= 200; ++n){
			if(!g(m, n)){
				cnt++;
			}
		}
		cout << cnt << ",";
	}*/
	lli lim = N / phi;
	lli ans = 0;
	for(lli n = 1; n <= lim; ++n){
		lli r = (lli)floor(n*phi);
		ans += r*(2*n + r + 1)/2;
	}
	ans += (-lim - 2*lim*lim - lim*lim*lim + (1 + lim - N)*(lim + lim*lim - N - N*N))/2;
	cout << ans << "\n";
	return 0;
}