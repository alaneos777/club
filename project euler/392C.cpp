#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

lli power(lli a, lli b){
    lli ans = 1;
    while(b){
        if(b&1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

// numbers of the form a + b*sqrt(5)
struct num{
    int a, b;
    num(): a(0), b(0){}
    num(int a){
        if(a < 0) a += mod;
        this->a = a;
        this->b = 0;
    }
    num(int a, int b){
        if(a < 0) a += mod;
        if(b < 0) b += mod;
        this->a = a;
        this->b = b;
    }
    num operator+(const num& rhs) const{
        int A = a + rhs.a, B = b + rhs.b;
        if(A >= mod) A -= mod;
        if(B >= mod) B -= mod;
        return num(A, B);
    }
    num operator+=(const num& rhs){
        *this = *this + rhs;
        return *this;
    }
    num operator-(const num& rhs) const{
        int A = a - rhs.a, B = b - rhs.b;
        if(A < 0) A += mod;
        if(B < 0) B += mod;
        return num(A, B);
    }
    num operator-=(const num& rhs){
        *this = *this - rhs;
        return *this;
    }
    num operator-() const{
        return num(-a, -b);
    }
    num operator*(const num& rhs) const{
        int A = 1ll*a*rhs.a % mod + 5ll*b*rhs.b % mod;
        int B = 1ll*a*rhs.b % mod + 1ll*b*rhs.a % mod;
        if(A >= mod) A -= mod;
        if(B >= mod) B -= mod;
        return num(A, B);
    }
    num operator*=(const num& rhs){
        *this = *this * rhs;
        return *this;
    }
    num operator/(const num& rhs) const{
        int den = 1ll*rhs.a*rhs.a % mod - 5ll*rhs.b*rhs.b % mod;
        if(den < 0) den += mod;
        den = power(den, mod-2);
        int A = (1ll*a*rhs.a % mod - 5ll*b*rhs.b % mod) * den % mod;
        int B = (-1ll*a*rhs.b % mod + 1ll*b*rhs.a % mod) * den % mod;
        if(A < 0) A += mod;
        if(B < 0) B += mod;
        return num(A, B);
    }
    num operator/=(const num& rhs){
        *this = *this / rhs;
        return *this;
    }
    num operator^(lli b) const{
        num ans = 1, A = *this;
        while(b){
            if(b & 1) ans *= A;
            b >>= 1;
            A *= A;
        }
        return ans;
    }
};

const int M = 100;
vector<num> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

using poly = vector<num>;

poly operator*(poly a, num b){
    for(num& x : a){
        x *= b;
    }
    return a;
}

poly operator/(const poly& a, const poly& b){
    assert(a.size() == b.size());
    int n = a.size();
    poly c(n);
    c[0] = a[0] / b[0];
    for(int i = 1; i < n; ++i){
        c[i] = a[i];
        for(int j = 1; j <= i; ++j){
            c[i] -= b[j] * c[i-j];
        }
        c[i] /= b[0];
    }
    return c;
}

poly Exp(num n, int sz){
    poly a(sz);
    for(int i = 0; i < sz; ++i){
        a[i] = (n^i) * invfact[i];
    }
    return a;
}

const vector<num> roots = {num(1, 1) / 2, num(1, -1) / 2};

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for(int i = 2; i <= M; ++i){
        fact[i] = fact[i-1] * i;
        inv[i] = -inv[mod % i] * (mod / i);
        invfact[i] = invfact[i-1] * inv[i];
    }
    lli n; int k;
    cin >> n >> k;
    num ans = 0;
    for(int i = 0; i < 2; ++i){
        num r = roots[i];
        poly numerator = Exp(num((n+1)%mod), k+1) * (r^(n+1));
        numerator[0] -= 1;
        poly denominator = Exp(1, k+1) * r;
        denominator[0] -= 1;
        if(i == 0) ans += (numerator / denominator)[k] * r;
        else ans -= (numerator / denominator)[k] * r;
    }
    ans /= (roots[0] - roots[1]);
    ans *= fact[k];
    cout << ans.a << "\n";
    return 0;
}