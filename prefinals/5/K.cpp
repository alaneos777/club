#include <bits/stdc++.h>
#define endl '\n'
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define pb(x) push_back(x)
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 3 * 1e5;
const int T = 250;

struct BIT{
    int ft[MX + 2];
    int N;
    void init(int n){
        n = MX;
        N = n;
        for(int i = 1; i <= n; i++){
            ft[i] = 0;
        }
    }
    int bit(int x){
        return x & (-x);
    }
    void update(int i, int v){
        while(i <= N){
            ft[i] += v;
            i += bit(i);
        }
    }
    int query(int i){
        int sum = 0;
        while(i > 0){
            sum += ft[i];
            i -= bit(i);
        }
        return sum;
    }
    void update(int ri, int rf, int v){
        update(ri, v);
        update(rf + 1, -v);
    }
}tree;

/* Cosas seg */
int cubeta[MX + 2];
int cubeta_pos[MX + 2];
int pos_nodo[MX + 2]; // pos de nodo en arr_mod
int arr_mod[MX + 2];
int ini_mod[MX + 2];
int fin_mod[MX + 2];

int arr_seq[MX + 2];
int ini_seq[MX + 2];
int fin_seq[MX + 2];
int cnt_seq;

int nivel[MX + 2];
vi hijos[MX + 2];

void init_DS(int n){
    for(int i = 1; i <= n; i++){
        hijos[i].clear();
    }
}

void update_subarb(int a, int k, int z){
    if(cubeta[k] == 0) return;
    int l = ini_mod[k];
    int r = fin_mod[k] + 1;
    int inf = lower_bound(arr_mod + l, arr_mod + r, ini_seq[a]) - arr_mod;
    int sup = upper_bound(arr_mod + l, arr_mod + r, fin_seq[a]) - arr_mod - 1;
    if(inf <= sup) tree.update(inf, sup, z);
}

void dfs_recorrido(int nodo){
    cnt_seq++;
    arr_seq[cnt_seq] = nodo;
    ini_seq[nodo] = cnt_seq;
    for(int sig : hijos[nodo]){
        nivel[sig] = nivel[nodo] + 1;
        dfs_recorrido(sig);
    }
    fin_seq[nodo] = cnt_seq;
}

void construye_arr(int n, int mod){
    for(int i = 0; i < mod; i++) cubeta[i] = 0;
    for(int i = 0; i < mod; i++) cubeta_pos[i] = 0;

    for(int i = 1; i <= n; i++){
        int nodo = arr_seq[i];
        int k = nivel[nodo] % mod;
        cubeta[k]++;
        cubeta_pos[k]++;;
    }
    ini_mod[0] = 1;
    fin_mod[0] = cubeta_pos[0];
    for(int i = 1; i < mod; i++){
        ini_mod[i] = cubeta_pos[i - 1] + 1;
        cubeta_pos[i] += cubeta_pos[i - 1];
        fin_mod[i] = cubeta_pos[i];
    }
    assert(cnt_seq == n);
    for(int i = n; i >= 1; i--){
        int nodo = arr_seq[i];
        int k = nivel[nodo] % mod;
        int pos = cubeta_pos[k];
        cubeta_pos[k]--;
        arr_mod[pos] = ini_seq[nodo]; // coloca el idx euler en esa pos
        pos_nodo[nodo] = pos;
    }
}

int tipo_query[MX + 2];
int query_a[MX + 2];
int query_x[MX + 2];
int query_y[MX + 2];
int query_z[MX + 2];

int res_query[MX + 2];

void lee_queries(int m){
    for(int i = 1; i <= m; i++){
        res_query[i] = 0;
        scanf("%d", &tipo_query[i]);//cin >> tipo_query[i];
        scanf("%d", &query_a[i]);//cin >> query_a[i];
        if(tipo_query[i] != 1) continue;
        scanf("%d", &query_x[i]); //cin >> query_x[i];
        scanf("%d", &query_y[i]); //cin >> query_y[i];
        scanf("%d", &query_z[i]); //cin >> query_z[i];
    }
}

int main () {
	//ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int casos;
    scanf("%d", &casos); //cin >> casos;

    while(casos--){

        int n, m;
        scanf("%d", &n); //cin >> n >> m;
        scanf("%d", &m); //cin >> n >> m;
        
        init_DS(n);

        for(int i = 1; i <= n - 1; i++){
            int p;
            scanf("%d", &p); //cin >> p;
            hijos[p].pb(i + 1);
        }

        cnt_seq = 0;
        nivel[1] = 0;
        dfs_recorrido(1);

        lee_queries(m);

        for(int x = 1; x <= T; x++){
            construye_arr(n, x);
            tree.init(n);
            for(int i = 1; i <= m; i++){
                if(tipo_query[i] == 1){
                    // update
                    if(query_x[i] != x) continue;
                    int a = query_a[i];
                    int y = query_y[i];
                    int z = query_z[i];
                    int k = (nivel[a] + y) % x;
                    update_subarb(a, k, z);
                }else{
                    // query
                    int nodo = query_a[i];
                    int pos = pos_nodo[nodo];
                    res_query[i] += tree.query(pos);
                }
            }
        }
        // queries con x > T
        construye_arr(n, n);
        tree.init(n);
        for(int i = 1; i <= m; i++){
            if(tipo_query[i] == 1){
                // update
                if(query_x[i] <= T) continue;
                int a = query_a[i];
                int y = query_y[i];
                int z = query_z[i];
                for(int k = nivel[a] + y; k < n; k += query_x[i]){
                    update_subarb(a, k, z);
                }
            }else{
                // query
                int nodo = query_a[i];
                int pos = pos_nodo[nodo];
                res_query[i] += tree.query(pos);
            }
        }

        for(int i = 1; i <= m; i++){
            if(tipo_query[i] == 1) continue;
            printf("%d\n", res_query[i]);//cout << res_query[i] << endl;
        }
    }

	return 0;
}
