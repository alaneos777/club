// Definiciones iniciales.
typedef long long Long;
typedef vector< vector<double> > Matriz;

const double ERROR = 1e-9;

bool Igual(double a, double b) {
  return fabs(a - b) < ERROR;
}

// Realiza eliminacion Gaussiana en una matriz.
// Rellenar el otro lado de la matriz cuando se
// Quiere la inversa y checar EL SWAP!!
void EliminaGaussiana(Matriz& m) {
  for (int i = 0; i < m.size(); ++i) {
    int fila_mayor = i;
    for (int j = i + 1; j < m.size(); ++j)
      if (fabs(m[fila_mayor][i]) <
        fabs(m[j][i])) fila_mayor = j;
    swap(m[i], m[fila_mayor]);
    if (Igual(m[i][i], 0)) continue;
    for (int j = m[i].size() - 1; j >= i; --j)
      m[i][j] /= m[i][i];
    for (int j = 0; j < m.size(); ++j) {
      if (i == j || Igual(m[j][i], 0)) continue;
      double ratio = m[j][i] / m[i][i];
      for (int k = i; k < m[j].size(); ++k)
        m[j][k] -= m[i][k] * ratio;
    }
  }
}

// Multiplicacion binaria a*b mod m.
Long Multiplicar(Long a, Long b, Long m) {
  Long res = 0, p = a;
  for (; b; b >>= 1) {
    if (b & 1) res =
        (res + p) % m;
    p = (p + p) % m;
  }
  return res;
}

//N-TH NUMBER OF FIBONACCI O(LOGN)
void multiply(int F[2][2], int M[2][2]){
  int x = F[0][0]*M[0][0] + F[0][1]*M[1][0];
  int y = F[0][0]*M[0][1] + F[0][1]*M[1][1];
  int z = F[1][0]*M[0][0] + F[1][1]*M[1][0];
  int w = F[1][0]*M[0][1] + F[1][1]*M[1][1];
  F[0][0] = x;
  F[0][1] = y;
  F[1][0] = z;
  F[1][1] = w;
}

void power(int F[2][2], int n){
  if( n == 0 || n == 1) return;
  int M[2][2] = {{1,1},{1,0}};
  power(F, n/2);
  multiply(F, F);
  if (n & 1) multiply(F, M);
}

int fib(int n){
  int F[2][2] = {{1,1},{1,0}};
  if (n == 0)
  return 0;
  power(F, n-1);
  return F[0][0];
}// TO USE ONLY CALL cout << fib(n);


//N-TH NUMBER OF FIBONACCI O(LOG ^ 2 N)
#define long long long
const long M = 1000000007; // modulo
map<long, long> F;

long f(long n) {
  if (F.count(n)) return F[n];
  long k=n/2;
  if (n%2==0) { // n=2*k
    return F[n] = (f(k)*f(k) + f(k-1)*f(k-1)) % M;
  } else { // n=2*k+1
    return F[n] = (f(k)*f(k+1) + f(k-1)*f(k)) % M;
  }
}

int main(){
  long n;
  F[0]=F[1]=1;
  while (cin >> n)
  cout << (n==0 ? 0 : f(n-1)) << endl;
}

// INVERSO MODULAR
pii ExtendedEuclid(int a,int b){
  if(b==0) return pii(1,0);
  pii aux=ExtendedEuclid(b,a%b);
  return pii(aux.second,aux.first - aux.second * (a/b));
}

pii Bezout(int a,int b){
  //La identidad de Bezout esta dada por la
  //siguiente ecuacion: ax + by = d
  //Donde "a" y "b" son los numeros dados y "d" el gcd(a,b)...
  //Regresa el valor de "x" e "y" que satisfacen la ecuacion
  return ExtendedEuclid(a,b);
}
 
pii diofantica(int a,int b){
  //ax + by = c -> Donde c es un multiplo de el gcd(a,b)
  return ExtendedEuclid(a,b);
}
 
int modinv(int a,int mod){
  //El inverso modular solo funciona si "a" y "mod" son coprimos
  return (ExtendedEuclid(a,mod).first +  mod) % mod;
}

//Four Squares Theorem, works until numbers less or equals to 10^6 and at most 10^6 queries of this type.
//Lagrange's four-square theorem, also known as Bachet's conjecture, states that every natural number 
//can be represented as the sum of four integer squares.
vector<pii> Fact(lli n) {
  int cont = 0;
  vector<pii> f;

  if(n < 2) return f;
  while(n % 2ll == 0ll) {
    n /= 2ll;
    cont++;
  }

  if(cont) f.push_back(pii(2ll, cont));

  for(lli i=3;i*i<=n;i+=2) {
    cont = 0;
    while(n % i == 0ll) {
      n /= i;
      cont++;
    }
    if(cont) f.push_back(pii(i, cont));
  }

  if(n > 1) f.push_back(pii(n, 1));
  return f;
}

lli divisor(lli a,lli b) {
  lli r = 1;
  while(a % b == 0) {
    a /= b;
    r *= b;
  }
  return r;
}

void FourSquares(lli n) {
  if(res.find(n) != res.end()) {
    cout<<res[n].first.first<<" "<<res[n].first.second<<" ";
    cout<<res[n].second.first<<" "<<res[n].second.second<<endl;
    return;
  }
  vector<pii> factors = Fact(n);
  lli n1, n2, n3, n4, sq, sq1, sq2, sq3, sq4, res1, res2, res3, res4;
  vector<pii> factors3;
  res1 = n ? 1ll : 0ll;
  res2 = res3 = res4 = 0ll;

  for(int i=0;i<factors.size();i++) {
    n1 = factors[i].first;

    // First square solution
    for(sq1 = floor(sqrt(n1));sq1 > 0;sq1--) {
      n2 = n1 - sq1 * sq1;
      if ( (n2 / divisor(n2, 4)) % 8 != 7 ) break;
    }

    // Second square solution
    for(sq2 = floor(sqrt(n2));sq2 > 0;sq2--) {
      n3 = n2 - sq2 * sq2;

      bool ok = true;
      factors3  = Fact(n3);
      for(int j=0;j<factors3.size() && ok;j++)
        ok = (factors3[j].first % 4ll != 3ll) || (factors3[j].second % 2 == 0);
      if(ok) break;
    }

    // To save time: extract the largest square divisor from the previous factorisation:
    sq = 1;
    for(int j=0;j<factors3.size();j++) {
      sq *= pow(factors3[j].first, (factors3[j].second - factors3[j].second % 2) / 2); 
      factors3[j].second = factors3[j].second % 2;
    }
    n3 /= sq * sq;

    // 3. Find a suitable third square
    sq4 = 0;

    // b. Find square for the remaining value:
    for (sq3 = floor(sqrt(n3)); sq3 > 0; sq3--) {
      n4 = n3 - sq3 * sq3;
      // See if this yields a sum of two squares:
      sq4 = floor(sqrt(n4));
      if (n4 == sq4 * sq4) break; // YES!
    }
    // Incorporate the square divisor back into the step-3 result:
    sq3 *= sq;
    sq4 *= sq;

    // 4. Merge this quadruple of squares with any previous 
    // quadruple we had, using the Euler square identity:
    while (factors[i].second--) {
      lli r1 = abs(res1*sq1 + res2*sq2 + res3*sq3 + res4*sq4);
      lli r2 = abs(res1*sq2 - res2*sq1 + res3*sq4 - res4*sq3);
      lli r3 = abs(res1*sq3 - res2*sq4 - res3*sq1 + res4*sq2);
      lli r4 = abs(res1*sq4 + res2*sq3 - res3*sq2 - res4*sq1);
      res1 = r1, res2 = r2;
      res3 = r3, res4 = r4;
    }
  }

  res[n] = psi(ii(res1, res2), ii(res3, res4));
  cout<<res1<<" "<<res2<<" "<<res3<<" "<<res4<<endl;
}

// FAST FOURIER TRANSFORM O(n log n)
typedef complex<double> base;
const double PI = acos(-1.0);
const double ERROR = 0.5;
 
void fft (vector<base> & a, bool invert) {
  lli n = (lli) a.size();
   
  for (int i=1, j=0; i<n; ++i) {
    lli bit = n >> 1;
    for (; j>=bit; bit>>=1) j -= bit;
    j += bit;
    if (i < j) swap (a[i], a[j]);
  }
   
  for (int len=2; len<=n; len<<=1) {
    double ang = 2*PI/len * (invert ? -1 : 1);
    base wlen (cos(ang), sin(ang));
    for (int i=0; i<n; i+=len) {
      base w (1);
      for (int j=0; j<len/2; ++j) {
      base u = a[i+j],  v = a[i+j+len/2] * w;
        a[i+j] = u + v;
        a[i+j+len/2] = u - v;
        w *= wlen;
      }
    }
  }
  if (invert)
    for (int i=0; i<n; ++i)
      a[i] /= n;
}
 
vector<lli> multiply(const vector<lli> & a, const vector<lli> & b) {
  vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
  size_t n = 1;
  while (n < max (a.size(), b.size()))  n <<= 1;
  n <<= 1;
  fa.resize (n),  fb.resize (n);
   
  fft (fa, false),  fft (fb, false);
  for (size_t i=0; i<n; ++i)
    fa[i] *= fb[i];
  fft (fa, true);
   
  vector<lli> convolucion(n, 0);
  for (size_t i=0; i<n; ++i)
    convolucion[i] = (lli) (fa[i].real() + ERROR);
  return convolucion;
}

//Pollard-Rho algorithm
typedef long long tint;

inline tint prodlog(tint a,tint b, tint M)
{
  return (__int128(a) * b) % M;
}

tint potlog(tint a,tint b, const tint M)
{
  tint res = 1;
  while (b)
  {
    if (b%2) res = prodlog(res,a, M);
    a = prodlog(a,a,M);
    b /= 2;
  }
  return res;
}

bool primo(tint n)
{
  if (n < 2) return false;
  if (n == 2) return true;
  tint D = n-1, S = 0;
  while (D%2 == 0)
  {
    D /= 2;
    S++;
  }
  // n-1 = 2^S * D
  static const int STEPS = 16;
  forn(pasos,STEPS)
  {
    const tint A = 1 + rand() % (n-1);
    tint M = potlog(A,D,n);
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
tint mcd(tint a,tint b) { return (a==0)?b:mcd(b%a,a);}

tint factor(tint n)
{
  static tint A ,B;
  A = 1 + rand() % (n-1);
  B = 1 + rand() % (n-1);
  #define f(x) (prodlog(x,x + B,n) + A)
  tint x = 2, y = 2, d = 1;
  while (d == 1 || d == -1)
  {
    x = f(x);
    y = f(f(y));
    d = mcd(x-y,n);
  }
  return abs(d);
}

map<tint,tint> fact;

void factorize(tint n)
{
  assert(n > 0);
  while (n > 1 && !primo(n))
  {
    tint f;
    do { f = factor(n); } while (f == n);
    n /= f;
    factorize(f);
    for (auto &it : fact)
    while (n % it.first == 0)
    {
      n /= it.first;
      it.second++;
    }
  }
  if (n > 1)
    fact[n]++;
}

//Sufficient condition to fit a rectangle with sides (p,q) in another w/ sides (a,b)
bool can(double p,double q,double a,double b) {
  if(p <= a && q <= b) return true;
  double sr = (2 * p * q * a) + ( p * p - q * q) * sqrt( p * p + q * q - a * a );
  sr /= (p * p + q * q);
  if(p > a && b >= sr) return true;
  return false;
}

//Cambio de Base
char to_char(int c){
  if(c >= 10) return c - 10 + 'A';
  return c + 48;
}

string ChangeBase(int num, int base){
  string ret;
  int div = base;
  while(div < num) div *= base;
  for(div /= base;;) {
    ret += to_char(num / div);
    num = num % div;
    if(div < 2) break;
    div /= base;
  }
  return ret;
}

// Logaritmo discreto, Baby Step-Gian Step
#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >

using namespace std;

const int MAXN = 1000001;

int power(int a,int b,int mod) {
	int ans = 1;
	while(b) {
		if(b & 1) ans = (ans * a) % mod;
		b >>= 1;
		a = (a * a) % mod;
	}
	return ans;
}

// Given n a prime number and p, q two integers between 0 and n-1,
// Find k such that p ^ k == q (mod n)

// Probar hasta phi(n), pero como n es primo, entonces hasta n - 1
// Si queremos que funcione para cuando (n, p) = 1, entonces probar hasta raiz( phi(n) ).
int naiveSolution(int n,int p,int q) { // O(n) 
	for(int k=0;k<=n-1;k++)
		if(power(p, k, n) == q)
			return k;
	return -1;
}

// Como n es primo, entonces retornar n - 1
int phi(int n) {
	return n - 1;
}

// Reescribiendo k = i * sqrt(n) - j
// => 1 <= i <= techo( n / suelo_sqrt(n) ) 0 <= j <= sqrt(n)

// Find k such that p ^ (i * sqrt(n) - j) == q (mod n)
// p ^ (i * sqrt(n) ) == q * p ^ j (mod n)
int babyStepGiantStep(int p, int q, int n) { // O( sqrt(n) * log(n) )
	int root = sqrt( phi(n) ); 
	int limite = phi(n) / root;
	if(phi(n) % root != 0) limite++;

	map<int, vi> all;
	for(int i=1;i<=limite;i++) {
		int p_i = power(p, i * root, n);
		all[p_i].pb(i);
	}

	set<int> ans;
	for(int j=0;j<=root;j++) {
		int p_j = power(p, j, n);
		int comp = (p_j * q) % n;

		if(all.find(comp) == all.end()) continue;

		for(int h=0;h<all[comp].size();h++) {
			int k = (all[ comp ][h] * root - j) % phi(n);
			if(k < 0) k += phi(n);
			ans.insert(k);
		}
	}

	for(set<int> :: iterator it=ans.begin();it!=ans.end();it++)
		cout<<*it<<" ";
	cout<<endl;

	return ans.size();
}

// чтение и перевод это будет пустой тратой времени
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout<<babyStepGiantStep(10, 1, 13)<<endl<<endl; // 0, 6
	cout<<babyStepGiantStep(14, 12, 17)<<endl<<endl; // 5
	cout<<babyStepGiantStep(15, 4, 221)<<endl<<endl; // 10 resultados
	return 0;
}

// Test de raices primitivas
// ADVERTENCIA: Esto solo funciona si x es prima relativa con mod. (x, mod) = 1.
// O(log^2 (n))
#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >

using namespace std;

const int MAXN = 1000001;

int power(int a,int b,int mod = -1) {
	int ans = 1;
	while(b) {
		if(b & 1) {
			ans = (ans * a);
			if(mod != -1) ans %= mod;
		}
		b >>= 1;
		a = (a * a);
		if(mod != -1) a %= mod;
	}
	return ans;
}

// Regresamos n - 1 si n es primo, cambiar si n no es primo.
int Phi(int n) {
	return n - 1;
}

// Necesitamos implementar factorizar un numero.
vector<pii> Factorize(int n) {
	vector<pii> primes;
	int cont = 0;
	while(n % 2 == 0) {
		cont++;
		n /= 2;
	}
	if(cont) primes.pb(pii(2, cont));
	for(int i=3;i*i<=n;i+=2) {
		cont = 0;
		while(n % i == 0) {
			cont++;
			n /= i;
		}
		if(cont) primes.pb(pii(i, cont));
	}

	if(n > 1) primes.pb(pii(n, 1));
	return primes;
}

// Tienen que ser coprimos x y mod.
int isPrimitiveRoot(int x, int mod) {
	int phi = Phi(mod);
	vector<pii> fact_phi = Factorize(phi);

	forn(i, fact_phi.size()) {
		int p = fact_phi[i].fi;
		int a = fact_phi[i].se;

		int temp = phi / power(p, a);
		if(power(x, temp, mod) == 1) return false;
	}
	return true;
}

// чтение и перевод это будет пустой тратой времени
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for(int i=1;i<=6;i++)
		if(isPrimitiveRoot(i, 7))
			cout<<i<<" ";
	cout<<endl;
	return 0;
}

// Orden multiplicativo de (x modulo mod).
// ADVERTENCIA: Esto solo funciona si x es prima relativa con mod. (x, mod) = 1.
// Si no se cumple, se va a ciclar este programa.
// O(log^2 (n))
#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >

using namespace std;

const int MAXN = 1000001;

int power(int a,int b,int mod = -1) {
	int ans = 1;
	while(b) {
		if(b & 1) {
			ans = (ans * a);
			if(mod != -1) ans %= mod;
		}
		b >>= 1;
		a = (a * a);
		if(mod != -1) a %= mod;
	}
	return ans;
}

// Regresamos n - 1 si n es primo, cambiar si n no es primo.
int Phi(int n) {
	return n - 1;
}

// Necesitamos implementar factorizar un numero.
vector<pii> Factorize(int n) {
	vector<pii> primes;
	int cont = 0;
	while(n % 2 == 0) {
		cont++;
		n /= 2;
	}
	if(cont) primes.pb(pii(2, cont));
	for(int i=3;i*i<=n;i+=2) {
		cont = 0;
		while(n % i == 0) {
			cont++;
			n /= i;
		}
		if(cont) primes.pb(pii(i, cont));
	}

	if(n > 1) primes.pb(pii(n, 1));
	return primes;
}

// Tienen que ser coprimos x y mod.
int multiplicativeOrder(int x, int mod) {
	int phi = Phi(mod);
	int order = phi;
	vector<pii> fact_phi = Factorize(phi);

	forn(i, fact_phi.size()) {
		int p = fact_phi[i].fi;
		int a = fact_phi[i].se;

		order = order / power(p, a);
		int temp = power(x, order, mod);
		while(temp != 1) {
			temp = power(temp, p, mod);
			order *= p;
		}
	}

	return order;
}

// чтение и перевод это будет пустой тратой времени
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int mod = 1009;
	for(int i=1;i<mod;i++) {
		//cout<<multiplicativeOrder(i, mod)<<" ";
		if(multiplicativeOrder(i, mod) == Phi(mod)) cout<<i<<" ";
	}
	cout<<endl;
	return 0;
}
