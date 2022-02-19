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
void file_io(string taskname){
   string fin = taskname + ".in";
   string fout = taskname + ".out";
   const char* FIN = fin.c_str();
   const char* FOUT = fout.c_str();
   freopen(FIN, "r", stdin);
   freopen(FOUT, "w", stdout);
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	file_io("control");

	int n, m;
	cin >> n >> m;
	vector<vector<int>> v(n, vector<int>(m));
	set<int> s; map<int, vector<int>> adj;
	forn(i, n){
		forn(j, m){
			cin >> v[i][j];
			s.insert(v[i][j]);
		}
	}

	for(int i=1; i<n; i++){
		forn(j, m){
			if(v[0][j] != v[i][j]){
				adj[v[0][j]].pb(v[i][j]);
				adj[v[i][j]].pb(v[0][j]);
				break;
			}
		}
	}
	map<int, int> ans;
	for(int x: s){
		vector<bool> used(50);
		for(int y: adj[x]){
			if(y < x) used[ans[y]] = true;
		}
		int i = 0;
		while(used[i]) i++;
		ans[x] = i;
	}

	cout << "Yes" << "\n";
	for(pii p: ans){
		cout << p.f << " -> " << p.s << "\n";
	}

}