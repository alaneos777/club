#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

const ld eps = 1e-15;

int main(){
    int N = 80;
    ld t = 0.5l;
    vector<int> p = {2, 3, 5, 7, 13};
    vector<ld> dens;
    function<void(int, int)> go = [&](int pos, int acum){
        if(pos == p.size()){
            if(acum > 1) dens.push_back(1.0l / (acum*acum));
        }else{
            int p_pow = 1;
            for(int i = 0; ; ++i){
                if(acum * p_pow <= N){
                    go(pos + 1, acum * p_pow);
                }else{
                    break;
                }
                p_pow *= p[pos];
            }
        }
    };
    go(0, 1);
    sort(dens.begin(), dens.end());
    int sz = dens.size();
    auto gen = [&](int l, int r){
        vector<ld> ans;
        int sz = r-l+1;
        for(int mask = 0; mask < (1<<sz); ++mask){
            ld sum = 0;
            for(int i = 0; i < sz; ++i){
                if(mask & (1<<i)){
                    sum += dens[l+i];
                }
            }
            if(sum <= t + eps) ans.push_back(sum);
        }
        sort(ans.begin(), ans.end());
        return ans;
    };
    vector<ld> left = gen(0, sz/2-1);
    vector<ld> right = gen(sz/2, sz-1);
    lli ans = 0;
    for(ld x : left){
        ld target = t - x;
        // |y - target| < eps --> -eps + target < y < eps + target
        ans += upper_bound(right.begin(), right.end(), eps + target) - lower_bound(right.begin(), right.end(), -eps + target);
    }
    cout << ans << "\n";
    return 0;
}