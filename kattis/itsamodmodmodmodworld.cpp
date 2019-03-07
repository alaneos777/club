#include <iostream>
using namespace std;
using lli = long long int;

lli gcd(lli a, lli b){
    lli r;
    while(b) r = a%b, a=b, b=r;
    return a;
}

lli f(lli p, lli q, lli n){
    lli t = gcd(p, q);
    p /= t, q /= t;
    lli s = 0, z = 1;
    while(q && n){
        t = p/q;
        s += z*t*n*(n+1)/2;
        p -= q*t;
        t = n/q;
        s += z*p*t*(n+1) - z*t*(p*q*t + p + q - 1)/2;
        n -= q*t;
        t = n*p/q;
        s += z*t*n;
        n = t;
        swap(p, q);
        z = - z;
    }
    return s;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    lli n, p, q;
    cin >> t;
    while(t--){
        cin >> p >> q >> n;
        cout << p*n*(n+1)/2 - q*f(p, q, n) << "\n";
    }
    return 0;
}