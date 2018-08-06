#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

const int inf = 1e9;
const int MAXN = 1000001;

int gcd(int a,int b,int &x,int &y) {
	int xx = y = 0;
	int yy = x = 1;
	while(b) {
		int q = a / b;
		int t = b; b = a % b; a = t;
		t = xx; xx = x - q * xx; x = t;
		t = yy; yy = y - q * yy; y = t;
	}
	return a;
}

int mod(int a,int b) {
	return ( (a % b) + b ) % b;
}

pii crt(int m1,int r1,int m2, int r2) {
	int s,t;
	int g = gcd(m1, m2, s, t);
	return pii(mod(s * r2*m1 + t*r1*m2, m1*m2) / g, m1*m2 / g);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int a,b,n,m;
	cin>>a>>b>>n>>m;
	cout<<crt(n, a, m, b).fi<<endl;
	return 0;
}
