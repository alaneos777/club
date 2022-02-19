#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define __ ios_base::sync_with_stdio(0);cin.tie(0);
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
typedef long long int lli;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int mod = (int)1e9+7;
const int inf = (int) 1e9+10;
const int maxn = (int)2e5+5;

int x[maxn],v[maxn];
int n;

bool can(ld t){
	vector<pair<ld,ld>> r;
	for(int i=1; i <=n; i++){
		ld uno = (ld) x[i] - t * v[i];
		ld dos = (ld) x[i] + t * v[i];
		r.push_back({uno,dos});
	}

	sort(all(r));
	pair<ld,ld> actual = r[0];
	for(int i=1; i < n; i++){
		ld uno = max(actual.fi,r[i].fi);
		ld dos = min(actual.se,r[i].se);
		if(dos < uno) return false;
		actual = pair<ld,ld>(uno,dos);
	}

	return true;
}

int main(){__
	cin >> n;
	for(int i=1; i <=n; i++) cin >> x[i];
	for(int i=1; i <=n; i++) cin >> v[i];
	
	ld l = 0.0, r = 1e9;
	for(int rep=0; rep <= 100; rep++){
		ld m = (l + r) /2.0;
		if(can(m)){
			r = m;
		}
		else{
			l = m;
		}
	}
	
	cout << fixed << setprecision(10) << r << endl;
	return 0;
}
