#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

vi pr;
bitset<10000000> bs;
void criba () {
    ll cn = 1;
    for (ll i = 2; i < 10000000; i++) {
        if (!bs[i]) {
            pr.push_back(i);
            for (ll j = i*i; j < 10000000; j += i) {
                bs[j] = 1;
            }
        }
        if (pr.size() == cn) {
            if (i >= 1000000)
                break;
            else
                cn *= 2;
        }
    }
}

bool obtRes (ll n) {
    ll sum = 0;
    for (int i = 0; i < pr.size() && n > 1; i++) {
        while (n % pr[i] == 0) {
            n /= pr[i];
            sum ^= i;
        }
    }

    if (n > 1)
        return 1;
    else
        return sum;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    pr.push_back(1e18);
    criba();

    ll n;
    cin >> n;

    if (obtRes(n))
        cout << "David" << endl;
    else
        cout << "Vasya" << endl;
}
