#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

typedef long double ld;
typedef vector<ld> vld;

vld mem((1 << 20) + 5, -1);

int n, a[25];
ld sum = 0;

ld dp (int mask) {
    if (mask == (1 << n) - 1)
        return 0;

    ld &res = mem[mask];

    if (res != -1)
        return res;

    ld act = 0;

    res = 0;
    for (int i = 0, j = 1; i < n; i++, j *= 2) {
        if (mask & j) {
            act += a[i];
            res += a[i];
        } else {
            res += a[i] * (dp(mask | j) + 1);
        }
    }

    res /= 1 - act / sum;
    res /= sum;

    return res;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
	}

	cout << fixed << setprecision(8) << dp(0) << endl;

	return 0;
}
