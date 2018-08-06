#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second
#define mod 1000000007

using namespace std;

const int inf = 1e9;
const int MAXN = 1000001;

lli suma(lli a) {
	return (a * a) % mod;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	lli a,b;
	cin>>a>>b;
	if(a == 0 && b > 0) {
		cout<<-1<<endl;
		return 0;
	}
	if(a == b) {
		cout<<1<<endl;
		return 0;
	}

	cout<<(suma(b - 1) - suma(a - 1) + (b - a + 1) + mod) % mod<<endl;
	return 0;
}
