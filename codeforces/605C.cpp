#include <bits/stdc++.h>
using namespace std;
const long double eps = 1e-9, oo = numeric_limits<long double>::infinity();

typedef vector<long double> vec;
typedef vector<vec> mat;

pair<vec, long double> simplexMethodPD(mat &A, vec &b, vec &c, bool mini = true){
	int n = c.size(), m = b.size();
	mat T(m + 1, vec(n + m + 1));
	vector<int> base(n + m), row(m);

	for(int j = 0; j < m; ++j){
		for(int i = 0; i < n; ++i)
			T[j][i] = A[j][i];
		row[j] = n + j;
		T[j][n + j] = 1;
		base[n + j] = 1;
		T[j][n + m] = b[j];
	}

	for(int i = 0; i < n; ++i)
		T[m][i] = c[i] * (mini ? 1 : -1);

	while(true){
		int p = 0, q = 0;
		for(int i = 0; i < n + m; ++i)
			if(T[m][i] <= T[m][p])
				p = i;

		for(int j = 0; j < m; ++j)
			if(T[j][n + m] <= T[q][n + m])
				q = j;

		long double t = min(T[m][p], T[q][n + m]);

		if(t >= -eps){
			vec x(n);
			for(int i = 0; i < m; ++i)
				if(row[i] < n) x[row[i]] = T[i][n + m];
			return {x, T[m][n + m] * (mini ? -1 : 1)}; // optimal
		}

		if(t < T[q][n + m]){
			// tight on c -> primal update
			for(int j = 0; j < m; ++j)
				if(T[j][p] >= eps)
					if(T[j][p] * (T[q][n + m] - t) >= T[q][p] * (T[j][n + m] - t))
						q = j;

			if(T[q][p] <= eps)
				return {vec(n), oo * (mini ? 1 : -1)}; // primal infeasible
		}else{
			// tight on b -> dual update
			for(int i = 0; i < n + m + 1; ++i)
				T[q][i] = -T[q][i];

			for(int i = 0; i < n + m; ++i)
				if(T[q][i] >= eps)
					if(T[q][i] * (T[m][p] - t) >= T[q][p] * (T[m][i] - t))
						p = i;

			if(T[q][p] <= eps)
				return {vec(n), oo * (mini ? -1 : 1)}; // dual infeasible
		}

		for(int i = 0; i < m + n + 1; ++i)
			if(i != p) T[q][i] /= T[q][p];

		T[q][p] = 1; // pivot(q, p)
		base[p] = 1;
		base[row[q]] = 0;
		row[q] = p;

		for(int j = 0; j < m + 1; ++j){
			if(j != q){
				long double alpha = T[j][p];
				for(int i = 0; i < n + m + 1; ++i)
					T[j][i] -= T[q][i] * alpha;
			}
		}
	}

	return {vec(n), oo};
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, p, q;
	cin >> n >> p >> q;
	mat A(2, vec(n));
	for(int i = 0; i < n; ++i){
		cin >> A[0][i] >> A[1][i];
		A[0][i] *= -1;
		A[1][i] *= -1;
	}
	vec b = {-p, -q};
	vec c(n, 1);
	cout << fixed << setprecision(10) << simplexMethodPD(A, b, c).second << "\n";
	return 0;
}