#include <bits/stdc++.h>

#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)

using namespace std;

typedef long long ll;

struct ST {
    int st[800005];
    int a[200005];
    bool res;

    void build (int i, int j, int pos) {
        if (i == j) {
            st[pos] = a[i];
            return;
        }

        int m = (i+j)/2;
        build(i, m, pos*2);
        build(m+1, j, pos*2+1);

        st[pos] = max(st[pos*2], st[pos*2+1]);
    }

    void update (int i, int j, int pos, int a, int x) {
        if (j < a || i > a)
            return;

        if (i == j) {
            st[pos] = x;
            return;
        }

        int m = (i+j)/2;
        update(i, m, pos*2, a, x);
        update(m+1, j, pos*2+1, a,x);

        st[pos] = max(st[pos*2], st[pos*2+1]);
    }

    int query (int i, int j, int pos, int a, int x) {
        if (j < a)
            return -1;

        if (st[pos] < x)
            return -1;

        if (i == j)
            return i;

        int m = (i+j)/2;
        int d = query(i, m, pos*2, a, x);
        return d == -1 ? query (m+1, j, pos*2+1, a, x) : d;
    }
};

ST st;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q, a, b, x;
    char op;

    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> st.a[i];
    st.build(1, n, 1);

    while (q--) {
        cin >> op >> a >> b;

        if (op == '1') {
            cout << st.query(1, n, 1, a, b) << endl;
        } else {
            st.update(1, n, 1, a, b);
        }
    }

	return 0;
}
