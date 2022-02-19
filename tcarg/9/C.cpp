#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9;

using int64 = long long int;

void exgcd(int64 a, int64 b, int64 &g, int64 &x, int64 &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

int64 inverse(int64 a, int64 m) {
  int64 d, x, y;
  exgcd(a, m, d, x, y);
  return d == 1 ? (x % m + m) % m : -1;
}

int64 crt(const std::vector<int64> &c, const std::vector<int64> &m) {
  int n = c.size();
  int64 M = 1, ans = 0;
  for (int i = 0; i < n; ++i) M *= m[i];
  for (int i = 0; i < n; ++i) {
    int64 x, y, g, tm = M / m[i];
    exgcd(tm, m[i], g, x, y);
    ans = (ans + tm * x * c[i] % M) % M;
  }
  return (ans + M) % M;
}

inline int deg(const std::vector<int64> &a) {
  if (a.empty()) return -100;
  if (a.size() == 1 && a[0] == 0) return -100;
  return a.size() - 1;
}

inline int L(const std::vector<int64> &a, const std::vector<int64> &b) {
  return std::max(deg(a), 1 + deg(b));
}

std::pair<std::vector<int64>, std::vector<int64>> lfsr_pe (const std::vector<int64> &s, int64 mod, int64 p, int64 e) {
  // linear feedback shift register mod p^e, p is prime
  std::vector<std::vector<int64>> a(e), b(e);
  std::vector<std::vector<int64>> an(e), bn(e);
  std::vector<std::vector<int64>> ao(e), bo(e);
  std::vector<int64> t(e), u(e), r(e);
  std::vector<int64> to(e, 1), uo(e);
  std::vector<int64> pw(e + 1);
  pw[0] = 1;
  for (int i = pw[0] = 1; i <= e; ++i) {
    pw[i] = pw[i - 1] * p;
  }
  for (int64 i = 0; i < e; ++i) {
    a[i] = {pw[i]}, an[i] = {pw[i]};
    b[i] = {0}, bn[i] = {s[0] * pw[i] % mod};
    t[i] = s[0] * pw[i] % mod;
    if (t[i] == 0) {
      t[i] = 1, u[i] = e;
    } else {
      for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i]);
    }
  }
  auto extand = [](std::vector<int64> &a, int m, int64 value = 0) {
    if (m > a.size()) a.resize(m, value);
  };
  for (size_t k = 1; k < s.size(); ++k) {
    for (int g = 0; g < e; ++g) {
      if (L(an[g], bn[g]) > L(a[g], b[g])) {
        ao[g] = a[e - 1 - u[g]];
        bo[g] = b[e - 1 - u[g]];
        to[g] = t[e - 1 - u[g]];
        uo[g] = u[e - 1 - u[g]];
        r[g] = k - 1;
      }
    }
    a = an, b = bn;
    for (int o = 0; o < e; ++o) {
      int64 d = 0;
      for (int i = 0; i < a[o].size() && i <= k; ++i) {
        d = (d + a[o][i] * s[k - i]) % mod;
      }
      if (d == 0) {
        t[o] = 1, u[o] = e;
      } else {
        for (u[o] = 0, t[o] = d; t[o] % p == 0; t[o] /= p, ++u[o]);
        int g = e - 1 - u[o];
        if (L(a[g], b[g]) == 0) {
          extand(bn[o], k + 1);
          bn[o][k] = (bn[o][k] + d) % mod;
        } else {
          int64 coef = t[o] * inverse(to[g], mod) % mod * pw[u[o] - uo[g]] % mod;
          int m = k - r[g];
          extand(an[o], ao[g].size() + m);
          extand(bn[o], bo[g].size() + m);
          for (size_t i = 0; i < ao[g].size(); ++i) {
            an[o][i + m] -= coef * ao[g][i] % mod;
            if (an[o][i + m] < 0) an[o][i + m] += mod;
          }
          while (an[o].size() && an[o].back() == 0) an[o].pop_back();
          for (size_t i = 0; i < bo[g].size(); ++i) {
            bn[o][i + m] -= coef * bo[g][i] % mod;
            if (bn[o][i + m] < 0) bn[o][i + m] -= mod;
          }
          while (bn[o].size() && bn[o].back() == 0) bn[o].pop_back();
        }
      }
    }
  }
  return std::make_pair(an[0], bn[0]);
}

std::vector<int64> ReedsSloane(const std::vector<int64> &s, int64 mod) {
  int64 modulo = mod;
  std::vector<std::tuple<int64, int64, int>> fac;
  for (int64 i = 2; i * i <= mod; ++i) if (mod % i == 0) {
    int64 cnt = 0, pw = 1;
    while (mod % i == 0) mod /= i, ++cnt, pw *= i;
    fac.emplace_back(pw, i, cnt);
  }
  if (mod > 1) fac.emplace_back(mod, mod, 1);
  std::vector<std::vector<int64>> as;
  int l = 0;
  for (auto &&x: fac) {
    int64 mod, p, e;
    std::tie(mod, p, e) = x;
    auto ss = s;
    for (auto &&x: ss) x %= mod;
    std::vector<int64> a, b;
    std::tie(a, b) = lfsr_pe(ss, mod, p, e);
    as.emplace_back(a);
    l = std::max<int>(l, a.size());
  }
  std::vector<int64> a(l);
  for (int i = 0; i < l; ++i) {
    std::vector<int64> c(as.size()), m(as.size());
    for (size_t j = 0; j < as.size(); ++j) {
      m[j] = std::get<0>(fac[j]);
      c[j] = i < as[j].size() ? as[j][i] : 0;
    }
    a[i] = crt(c, m);
  }
  reverse(a.begin(), a.end());
  a.pop_back();
  for(int64& ai : a){
  	ai = (modulo - ai) % modulo;
  }
  return a;
}

lli rec(const vector<lli> & P, const vector<lli> & init, lli n){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += ans[i] * init[i]) %= mod;
	return nValue;
}

lli n, m;
vector < vector<long long> > dp;

void calc (int x = 0, int y = 0, int mask = 0, int next_mask = 0)
{
	if (x == n)
		return;
	if (y >= m)
		(dp[x+1][next_mask] += dp[x][mask]) %= mod;
	else
	{
		int my_mask = 1 << y;
		if (mask & my_mask)
			calc (x, y+1, mask, next_mask);
		else
		{
			calc (x, y+1, mask, next_mask); // 1x1
			calc (x, y+1, mask, next_mask | my_mask); // abajo 2x1
			if (y+1 < m && ! (mask & (my_mask << 1)))
				calc (x, y+2, mask, next_mask); // derecha 1x2
		}
	}
}


int main()
{
	cin >> m >> n;
	lli N = n;
	n = 300;

	dp.resize (n+1, vector<long long> (1<<m));
	dp[0][0] = 1;
	for (int x=0; x<n; ++x)
		for (int mask=0; mask<(1<<m); ++mask)
			calc (x, 0, mask, 0);

	vector<lli> init;
	for(int i = 0; i < n; ++i){
		init.push_back(dp[i][0]);
	}

	cout << rec(ReedsSloane(init, mod), init, N) << "\n";

}