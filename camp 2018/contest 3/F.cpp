#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >
#define mod 1000000007

using namespace std;

const int MAXN = 1000005;

lli num[MAXN];
lli pot[MAXN];
lli freq[MAXN];
lli subset[MAXN];

// чтение и перевод это будет пустой тратой времени
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	pot[0] = 1ll;
	forn(i, MAXN)
		if(i) pot[i] = (pot[i - 1] * 2ll) % mod;

	int n;
	cin>>n;

	lli maxi = 0;
	forn(i, n) {
		cin>>num[i];
		freq[ num[i] ]++;
		maxi = max(maxi, num[i]);
	}

	lli ans = 0ll;
	for(lli i=maxi;i>=1;i--) {
		lli sub = 0;
		lli add = freq[i];
		for(lli j=i+i;j<=maxi;j+=i) {
			add = (add + freq[j]) % mod;
			sub = (subset[j] + sub) % mod;
		}
		subset[i] = (pot[add] - 1ll - sub + mod + mod) % mod;
		ans = (ans + (subset[i] * i) % mod) % mod;
	}

	cout<<ans<<endl;
	return 0;
}
