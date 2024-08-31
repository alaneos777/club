#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const double eps = 1e-9, oo = numeric_limits<double>::infinity();

typedef vector<double> vec;
typedef vector<vec> mat;

pair<vec, double> simplexMethodPD(mat &T, const vec &b, const vec &c, bool mini = true){
	int n = c.size(), m = b.size();
	T.resize(m + 1);
	for(auto& row : T){
		row.resize(n + m + 1);
	}
	vector<int> base(n + m), row(m);

	for(int j = 0; j < m; ++j){
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

		double t = min(T[m][p], T[q][n + m]);

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
				double alpha = T[j][p];
				for(int i = 0; i < n + m + 1; ++i)
					T[j][i] -= T[q][i] * alpha;
			}
		}
	}

	return {vec(n), oo};
}

auto lpSieve(int n){
	vector<int> lp(n+1), primes;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			lp[i] = i;
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const int M = 1e6;
const auto lp = lpSieve(M);

vector<int> getPrimeFactors(int n){
	vector<int> factors;
	while(n > 1){
		int p = lp[n];
		while(n%p == 0){
			n /= p;
		}
		factors.push_back(p);
	}
	return factors;
}

int getRad(int n){
	int rad = 1;
	while(n > 1){
		int p = lp[n];
		while(n%p == 0){
			n /= p;
		}
		rad *= p;
	}
	return rad;
}

int main(){
	set<int> rads;
	vector<bool> sieve(M+1);
	for(int i = 3; i <= M; i += 10){
		int r = getRad(i);
		rads.insert(r);
		sieve[r] = true;
	}
	double ans = 0;
	for(int i : rads){
		if(sieve[i]){
			if(lp[i] == i) ans += log(i);
			for(int j = lp[i] == i ? i : 2*i; j <= M; j += i){
				sieve[j] = false;
			}
		}
	}
	map<int, int> ids;
	vector<int> nums;
	for(int i = 1; i <= M; ++i){
		if(sieve[i]){
			nums.push_back(i);
			for(int p : getPrimeFactors(i)){
				if(ids.count(p) == 0) ids[p] = ids.size();
			}
		}
	}
	vector<vector<double>> A(nums.size(), vector<double>(ids.size()));
	for(int i = 0; i < nums.size(); ++i){
		for(auto p : getPrimeFactors(nums[i])){
			A[i][ids[p]] = -1;
		}
	}
	vector<double> b(nums.size(), -1), c(ids.size());
	for(auto [p, id] : ids){
		c[id] = log(p);
	}
	A.resize(nums.size() + ids.size(), vector<double>(ids.size()));
	b.resize(nums.size() + ids.size());
	for(int i = 0; i < ids.size(); ++i){
		A[nums.size() + i][i] = 1;
		b[nums.size() + i] = 1;
	}
	auto[x, ans2] = simplexMethodPD(A, b, c, true);
	ans += ans2;
	cout << fixed << setprecision(6) << ans << "\n";
	return 0;
}