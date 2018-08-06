#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

ull phi(ull n){
    ull ans = n;
    if(n==1) return 1;
    set<ull> primos;
    ull d=2;
    while(d<=sqrt(n)){
        if(n%d==0){
            primos.insert(d);
            n /= d;
        }else{
            d++;
        }
    }
    primos.insert(n);
    for(ull i:primos) ans = (ans / i) * (i-1);
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ull n;
    while(cin >> n)
    cout << n-phi(n) << endl;
    return 0;
}
