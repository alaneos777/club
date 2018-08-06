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

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n,m;
	cin>>n>>m;
	int x,y;
	int g = gcd(n, m, x, y);
	if(x < 0) x += m;
	if(g == 1) cout<<x<<endl;
	else cout<<-1<<endl;
	return 0;
}
