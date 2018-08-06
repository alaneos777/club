#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)

using namespace std;

typedef long long ll;
typedef vector<int> vi;

const int MX = 200000;

struct ST {
    ll st[4*MX], lz[4*MX];
    int a[MX];

    void lazy (int i, int j, int pos) {
        if (i == j) {
            a[i] = lz[pos];
        } else {
            lz[pos*2] = lz[pos];
            lz[pos*2+1] = lz[pos];
        }
        lz[pos] = 0;
    }

    void update (int i, int j, int pos, int a, int b, int x) {
        if (lz[pos])
            lazy(i, j, pos);

        if (j < a || i > b)
            return;

        if (a <= i && j <= b) {
            lz[pos] = x;
            return;
        }

        int m = (i+j)/2;
        update(i, m, pos*2, a, b, x);
        update(m+1, j, pos*2+1, a, b ,x);
    }

    void dfs (int i, int j, int pos) {
        if (lz[pos])
            lazy(i, j, pos);

        if (i == j) {
            return;
        }

        int m = (i+j)/2;
        dfs(i, m, pos*2);
        dfs(m+1, j, pos*2+1);
    }
};

ST st;

int n, k, q;
int c[MX], l[MX], r[MX], tam[MX];
int res[MX] = {0};

void mapear () {
    vi st;
    for (int i = 0; i < q; i++) {
        st.push_back(l[i]);
        st.push_back(r[i]);
        st.push_back(r[i]+1);
    }
    st.push_back(2e9);

    sort(st.begin(), st.end());
    st.erase(unique(st.begin(), st.end()), st.end());

    for (int i = 0; i < st.size()-1; i++)
        tam[i+1] = st[i+1] - st[i];

    for (int i = 0; i < q; i++) {
        int a = lower_bound(st.begin(), st.end(), l[i]) - st.begin();
        int b = lower_bound(st.begin(), st.end(), r[i]) - st.begin();

        l[i] = a+1, r[i] = b+1;
    }

    n = st.size();
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> k >> q;
    for (int i = 0; i < q; i++)
        cin >> c[i] >> l[i] >> r[i];
    mapear();

    for (int i = 0; i < q; i++) {
        st.update(1, n, 1, l[i], r[i], c[i]);
    }

    st.dfs(1, n, 1);
    for (int i = 1; i <= n; i++) {
        res[st.a[i]] += tam[i];
    }

    for (int i = 1; i <= k; i++)
        cout << res[i] << " ";
    cout << endl;

	return 0;
}
