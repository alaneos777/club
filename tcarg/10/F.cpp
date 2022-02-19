#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for (int i = 0; i < (n); i++)
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define f first
#define s second
#define rand(i, j) uniform_int_distribution<ll>((ll)(i), (ll)(j))(rng)
mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef double ld;
typedef long double lld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "(" << p.f << ", " << p.s << ")"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
	cout << "["; for (int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i]; } return cout << "]";
}
template<typename T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<typename T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }


//2 147 483 647 int max
//9 223 372 036 854 775 807 ll max


int main(){
	cin.tie(0)->sync_with_stdio(0);

	int n, t;
	cin >> n >> t;

	vector<ll> d(n), p(n);
	forn(i, n){
		cin >> d[i] >> p[i];
	}

	vector<int> ord(n);
	forn(i, n) ord[i] = i;
	sort(ord.begin(), ord.end(), [&](int i, int j){return p[i]*d[j] > p[j]*d[i];});
	vector<vector<pll>> dp(n+1, vector<pll>(t+1));
	vector<vector<bool>> bt(n+1, vector<bool>(t+1));

	// cout << ord << "\n";
	// cout << "HERE" << endl;
	for(int i=1; i<=n; i++){
		forn(j, t+1){
			dp[i][j] = dp[i-1][j];
			if(d[ord[i-1]] > j) continue;
			pll x = dp[i-1][j-d[ord[i-1]]];
			// cout << "a" << endl;
			if(ckmax(dp[i][j], mp(p[ord[i-1]] + x.f, x.s - p[ord[i-1]]*j))) bt[i][j] = true;
			// cout << "b" << endl;
		}
	}
	// cout << "HERE" << endl;
	// cout << dp << "\n";
	// cout << bt << endl;

	vector<int> ans;
	pair<pll, int> best = mp(dp[n][t], t);
	forn(i, t){
		ckmax(best, mp(dp[n][i], i));
	}
	int curr = best.s;
	for(int i=n; i>0; i--){
		if(bt[i][curr]){
			ans.pb(ord[i-1]+1);
			curr -= d[ord[i-1]];
		}
	}
	// assert(curr == 0);
	cout << ans.size() << "\n";
	for(int i=(int)(ans.size())-1; i>=0; i--) cout << ans[i] << " ";
	cout << "\n";
}