#include <bits/stdc++.h>
using namespace std;
using ld = long double;

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<ld> p(n);
    for(int i = 0; i < n; ++i){
        cin >> p[i];
        p[i] /= 100;
    }
    sort(p.begin(), p.end(), greater<ld>());
    vector<ld> poly = {1};
    ld ans = 0;
    for(int s = 0; s < n; ++s){
        poly.resize(poly.size() + 1);
        for(int j = poly.size()-2; j >= -1; --j){
            poly[j+1] = poly[j+1] * (1 - p[s]) + (j >= 0 ? poly[j] * p[s] : 0);
        }
        ld tmp = 0;
        for(int a = 1; a <= s+1; ++a){
            tmp += powl(ld(a), ld(a)/ld(s+1)) * poly[a];
        }
        ans = max(tmp, ans);
    }
    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}