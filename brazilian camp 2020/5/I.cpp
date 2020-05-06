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
 
const int MX = 1000005, inf = 10000000;
string a, b;
int mem[MX][2][2];
 
int dp (int i, int f, int car) {
    if (i == b.size()) return !f && !car ? 0 : inf;
    if (i >= a.size()) f = f | (1 - car);
    int &res = mem[i][f][car];
    if (res != -1) return res;
    res = inf;
    
    int x = (i < a.size() ? a[i] - '0' : 0);
    int _x = x;
    x += car;
    int y = b[i] - '0';
    int nc = 0;
    
    if (x == 10) {
        x = 0;
        nc = 1;
    }
    
    res = min(res, (x != y) + dp(i + 1, f, nc));
    res = min(res, 1 + ((x + 1) % 10 != y) + dp(i + 1, 0, (x + 1) / 10 + nc));
    if (car) {
        // Seguir acarreo
        res = min(res, (i >= a.size() && !f) + (_x != 9) + (y != 0) + dp(i + 1, f, 1));
        res = min(res, (_x != 9) + (y != 0) + dp(i + 1, 1, 1));
        
        // Parar acarreo
        res = min(res, 1 + (y == 0) + dp(i + 1, f, 0));
    }
    
    return res;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> a >> b;
    reverse(all(a));
    reverse(all(b));
    
    memset(mem, -1, sizeof(mem));
    cout << dp(0, 0, 0) << endl;
    
    return 0;
}