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

int A[MAXN];
int B[MAXN];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n,m;
	cin>>n>>m;

	forn(i, n) cin>>A[i];
	sort(A, A + n);
	forn(i, m) cin>>B[i];
	sort(B, B + m);
	
	lli ans = 1ll, sz = 0;
	int tmp = n;

	for(int i=m-1;i>=0;i--) {
		int id = lower_bound(A, A + tmp, B[i]) - A;
		sz += (tmp - id);
		if(!sz) {
			ans = 0;
			break;
		}
		ans = (ans * sz) % mod;
		tmp = id;
		sz--;
	}

	cout<<ans<<endl;
	return 0;
}
