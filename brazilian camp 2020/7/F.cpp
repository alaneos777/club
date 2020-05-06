#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

const int MX = 1e5;
int n, m, dp[2][(1 << 16) + 5];
string s[155];

#define count(n) __builtin_popcount(n)

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> s[i];
    
    int x = 0, y = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++, x = 1 - x, y = 1 - y) {
            fill(dp[y], dp[y] + (1 << m) + 5, -1e9);
            
            for (int k = 0; k < (1 << m); k++) {
                int pre = (1 << j) - 1;
                int suf = ((1 << m) - 1) & (~pre);
                
                pre = k & pre;
                suf = k & suf;
                
                int a = count(pre);
                int b = i ? int(s[i - 1].size()) - count(suf): 0;
                
                if (a > s[i].size() || b < 0) continue;
                
                // Poner
                if (a < s[i].size()) {
                    int p = dp[x][k];
                    
                    if (i && (k & (1 << j)))
                        p += s[i][a] == s[i-1][b];
                    
                    if (a && (k & (1 << j - 1)))
                        p += s[i][a] == s[i][a-1];
                    
                    dp[y][k | (1 << j)] = max(dp[y][k | (1 << j)], p);
                }
                
                // No poner
                int p = dp[x][k];
                dp[y][k & ~(1 << j)] = max(dp[y][k & ~(1 << j)], p);
            }
        }
        
        for (int k = 0; k < (1 << m); k++)
            if (count(k) != s[i].size())
                dp[x][k] = -1e9;
    }
    
    int res = 0;
    for (int i = 0; i < (1 << m); i++)
        res = max(res, dp[x][i]);
    cout << 2 * res << endl;
    
    return 0;
}

