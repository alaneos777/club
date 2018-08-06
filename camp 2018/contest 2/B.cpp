#define forn(i, n) for(int i=0;i<n;i++)
#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli inv(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1 != 0){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	return s0;
}

lli modPow(lli a, lli b, lli m){
	lli ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = (ans * a) % m;
		b >>= 1;
		a = (a * a) % m;
	}
	return ans;
}

inline lli prodlog(lli a,lli b, lli M)
{
  return (__int128(a) * b) % M;
}

lli potlog(lli a,lli b, const lli M)
{
  lli res = 1;
  while (b)
  {
    if (b%2) res = prodlog(res,a, M);
    a = prodlog(a,a,M);
    b /= 2;
  }
  return res;
}

bool primo(lli n)
{
  if (n < 2) return false;
  if (n == 2) return true;
  lli D = n-1, S = 0;
  while (D%2 == 0)
  {
    D /= 2;
    S++;
  }
  // n-1 = 2^S * D
  static const int STEPS = 16;
  forn(pasos,STEPS)
  {
    const lli A = 1 + rand() % (n-1);
    lli M = potlog(A,D,n);
    if (M == 1 || M == (n-1)) goto next;
    forn(k,S-1)
    {
      M = prodlog(M,M,n);
      if (M == (n-1)) goto next;
    }
    return false;
next:;
  }
  return true;
}

// Pollard's rho - Fast Factorization
lli mcd(lli a,lli b) { return (a==0)?b:mcd(b%a,a);}

lli factor(lli n)
{
  static lli A ,B;
  A = 1 + rand() % (n-1);
  B = 1 + rand() % (n-1);
  #define f(x) (prodlog(x,x + B,n) + A)
  lli x = 2, y = 2, d = 1;
  while (d == 1 || d == -1)
  {
    x = f(x);
    y = f(f(y));
    d = mcd(x-y,n);
  }
  return abs(d);
}

map<lli,lli> fact;
vector<lli> factors;

void factorize(lli n)
{
  assert(n > 0);
  while (n > 1 && !primo(n))
  {
    lli f;
    do { f = factor(n); } while (f == n);
    n /= f;
    factorize(f);
    for (auto &it : fact)
    while (n % it.first == 0)
    {
      n /= it.first;
      it.second++;
      factors.push_back(it.first);
    }
  }
  if (n > 1){
    fact[n]++;
	factors.push_back(n);
  }
}

lli firstPrimitiveRoot(lli p){
	lli order = p - 1;
	fact.clear();
	factors.clear();
	factorize(order);
	lli test = 1;
	while(true){
		bool found = true;
		for(lli & factor : factors){
			if(modPow(test, order / factor, p) == 1){
				found = false;
				break;
			}
		}
		if(found) return test;
		test++;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	lli p, a, b;
	while(t--){
		cin >> p >> a >> b;
		a %= (p - 1);
		if(b == 0){
			lli upper = min(p, 10ll);
			cout << upper << "\n";
			for(lli i = 0; i < upper; i++){
				cout << i << " ";
			}
		}else{
			lli d = __gcd(a, p - 1);
			lli g = firstPrimitiveRoot(p);
			lli w = modPow(g, (p - 1) / d, p);
			lli current = w;
			cout << min(d - 1, 10ll) << "\n";
			for(lli k = 1; k < d && k <= 10; k++){
				lli ans = (b * inv(current - 1, p)) % p;
				if(ans < 0) ans += p;
				cout << ans << " ";
				current = (current * w) % p;
			}
		}
		cout << "\n";
	}
	return 0;
}