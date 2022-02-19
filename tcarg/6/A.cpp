#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
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

typedef tree<
pair<int,int>,
null_type,
less<pair<int,int>>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

int x[maxn],r[maxn],q[maxn];

int main(){__
	int n,k;
	cin >> n >> k;
	vector<pii> a;

	set<int> vals;
	map<int,vector<pii>> ev;
	for(int i=1; i <=n; i++){
		cin >> x[i] >> r[i] >> q[i];
		vals.insert(x[i]);
		ev[x[i]].push_back({0,i});
		vals.insert(x[i] - r[i]);
		vals.insert(x[i] + r[i]);
		ev[x[i]+r[i]].push_back({1,i});
	}

	map<int,ordered_set> bits;

	lli ans = 0ll;
	for(auto f : ev){
		vector<pii> e = f.se;
		sort(all(e));

		for(auto aux : e){
			int tipo,id;
			tie(tipo,id) = aux;
			int iq = q[id];

			if(tipo == 0){
				//checar y anadir
				int start = x[id] - r[id];
				for(int otro = max(0,iq-k); otro <= iq+k; otro++){
					if(bits.find(otro) == bits.end()) continue;

					int primero = bits[otro].order_of_key({start,-1});
					int segundo = bits[otro].order_of_key({x[id],inf});
					ans+= segundo - primero;
				}

				bits[iq].insert({x[id],id});
			}
			else{
				//borrar
				bits[iq].erase(bits[iq].lower_bound({x[id],id}));
			}
		}
	}

	cout << ans << endl;
	return 0;
}
