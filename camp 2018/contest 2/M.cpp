#include <bits/stdc++.h>
#define endl '\n'

#define fi first
#define se second
#define eb(x,y) push_back(make_pair(x,y))

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int gcd(int a, int b) {
    return b ? gcd(b, a%b) : abs(a);
}

int a, b, c, d, g;
int sa, sb, sc, sd;

void impr (char a, char op, int k, char b) {
    cout << a << " " << op << "= " << k << " * " << b << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> a >> b >> c >> d;
	vii res, aux, cs;

	if (gcd(a, b) != gcd(c, d)) {
        cout << "No solution." << endl;
        return 0;
	}

	if (gcd(a, b) == 0) {
        cout << 0 << endl;
        return 0;
	}

	g = gcd(a, b);

	if(a) sa = a / abs(a);
    if(b) sb = b / abs(b);
    if(c) sc = c / abs(c);
    if(d) sd = d / abs(d);

    if (!a) sa = sb;
    if (!b) sb = sa;
    if (!c) sc = sd;
    if (!d) sd = sc;

    a = abs(a) / g;
    b = abs(b) / g;
    c = abs(c) / g;
    d = abs(d) / g;

    while (a != b) {
        if (a > b) {
            res.eb(0, 0);
            swap(a, b);
        }
        if (a == 0) {
            res.eb(0, 0);
            res.eb(1, 1);
            break;
        }
        int e = b / a;
        if (a == 1)
            e--;
        b %= a;
        res.eb(e, -sa * sb);
        if (!b)
            break;
    }

    while (c != d) {
        if (c > d) {
            aux.eb(0, 0);
            swap(c, d);
        }
        if (c == 0) {
            res.eb(0, 0);
            res.eb(1, 1);
            break;
        }
        int e = d / c;
        if (c == 1)
            e--;
        d %= c;
        aux.eb(e, sc*sd);
        if (!d)
            break;
    }
    reverse(aux.begin(), aux.end());

    if (sa != sc) {
        cs.eb(0, (sa * sb == 1));
    }
    sa = sc;

    if (sb != sd) {
        cs.eb(1, (sa * sb == 1));
    }
    sb = sd;

    string s = "swap(a, b)", op = "+-";

    cout << res.size() + cs.size() + aux.size() << endl;

    for (int i = 0; i < res.size(); i++) {
        ii x = res[i];
        if (x.fi == 0) {
            cout << s << endl;
        } else {
            impr('b', op[x.se == -1], x.fi, 'a');
        }
    }

    for (int i = 0; i < cs.size(); i++) {
        ii x = cs[i];
        impr("ab"[x.fi], op[x.se], 2, "ab"[1-x.fi]);
    }

    for (int i = 0; i < aux.size(); i++) {
        ii x = aux[i];
        if (x.fi == 0) {
            cout << s << endl;
        } else {
            impr('b', op[x.se == -1], x.fi, 'a');
        }
    }

	return 0;
}














