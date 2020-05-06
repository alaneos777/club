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

const int MX = 1005;
const ld eps = 1e-9;

int n, a[MX];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n;
    a[0] = 1;
    a[1] = 1;
    for (int i = 2; i <= n; i++) {
        bitset<MX> bs;
        for (int k = 1; i - 2 * k >= 0; k++) {
            int no = 2 * a[i - k] - a[i - 2 * k];
            if (no > 0)
                bs[no] = 1;
        }
        for (int j = 1; j < MX; j++)
            if (!bs[j]) {
                a[i] = j;
                break;
            }
    }
    cout << a[n] << endl;
    
    return 0;
}

