#include <bits/stdc++.h>
using namespace std;
using ld = long double;

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    while(n--){
        int w_, g_, h_, r_;
        cin >> w_ >> g_ >> h_ >> r_;
        if(g_ + h_ == 2*r_){
            cout << w_ << " " << w_ << "\n";
            continue;
        }
        ld w = w_, g = g_, h = h_, r = r_;
        ld lambda = w / sqrtl(w*w + (g+h-2*r)*(g+h-2*r));
        ld a = (g-r) / sqrtl(1 - lambda * lambda);
        ld b = (h-r) / sqrtl(1 - lambda * lambda);
        cout << fixed << setprecision(9) << sqrtl(w*w + (g-h)*(g-h)) << " " << a+b << "\n";
    }
    return 0;
}