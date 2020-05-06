#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

int n, k;
int adj[1005][1005];
set<pii> st;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> k;
    while (n * (n - 1) / 2 <= k)
        n++;
    n--;
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                adj[i][j] = 1;
    
    k -= n * (n - 1) / 2;
    for (int i = 2; k && i <= n; i++)
        for (int j = 2; k && j <= n; j++)
            if (adj[i][j]) {
                k--;
                adj[i][j] = adj[j][i] = 0;
            }
    
    if (k) {
        cout << -1 << endl;
        return 0;
    }
    
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            if (adj[i][j])
                st.emplace(i, j);
    
    cout << n << endl << st.size() << endl;
    for (auto r : st)
        cout << r.fi << " " << r.se << endl;
        
    return 0;
}

