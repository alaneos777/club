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
 
const int MX = 200005;
int n, a[MX], res[MX];
stack<int> st;
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n;
    for (int i = 1; i < n; i++)
        cin >> a[i];
    
    for (int i = 1; i < n; i++)
        if (abs(a[i] - a[i-1]) > 2 || abs(a[i] - a[i+1]) > 2 || a[i] % 2) {
            cout << "No" << endl;
            return 0;
        }
    
    iota(res, res+MX, 0);
    for (int i = 1; i <= n; i++) {
        if (a[i] > a[i-1]) {
            st.push(i);
        } else if (a[i] < a[i-1]) {
            swap(res[i], res[st.top()]);
            st.pop();
        }
    }
    
    cout << "Yes" << endl;
    for (int i = 1; i <= n; i++)
        cout << res[i] << " ";
    cout << endl;
        
    return 0;
}
