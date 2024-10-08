#include <bits/stdc++.h>
using namespace std;

struct T {
  uint64_t a, b;

  T() : a(0), b(0) { }
  T(uint64_t x) : a(x), b(0) { }
  T(uint64_t a, uint64_t b) : a(a), b(b) { }

  //The conjugate of a + b*omega is given by mapping omega -> omega^2
  T conj() {
    return T{a - b, -b};
  }

  T operator-() {
    return T{-a, -b};
  }
};

/*
 * A couple of useful constants: `OMEGA` is a third root of unity, `OMEGA2` is
 * its square and `INV3` is the multiplicative inverse of 3.
 */

const T OMEGA = {0, 1};
const T OMEGA2 = {-1ull, -1ull};
const T INV3 = {12297829382473034411ull, 0};

/*
 * Standard operators.
 */

T operator+(const T &u, const T &v) {
  return {u.a + v.a, u.b + v.b};
}

T operator-(const T &u, const T &v) {
  return {u.a - v.a, u.b - v.b};
}

T operator*(const T &u, const T &v) {
  return {u.a*v.a - u.b*v.b, u.b*v.a + u.a*v.b - u.b*v.b};
}

void operator+=(T &u, const T &v) {
  u.a += v.a;
  u.b += v.b;
}

void operator-=(T &u, const T &v) {
  u.a -= v.a;
  u.b -= v.b;
}

void operator*=(T &u, const T &v) {
  uint64_t tmp=u.a;
  u.a=u.a*v.a - u.b*v.b;
  u.b=u.b*v.a + tmp*v.b - u.b*v.b;
}

// We pack the main algorithm in a class of its own, mainly because we will have
// to allocate some temporary working memory.
class Conv64 {
  public:

  // Returns the product of two polynomials from the ring R[x].
  vector<int64_t> multiply(const vector<int64_t> &p,
                           const vector<int64_t> &q) {
    vector<uint64_t> pp(p.size()), qq(q.size());
    for (uint64_t i = 0; i < p.size(); ++i) {
      pp[i] = p[i];
    }
    for (uint64_t i = 0; i < q.size(); ++i) {
      qq[i] = q[i];
    }
    uint64_t s = 1;
    while (s < p.size() + q.size() - 1) {
      s *= 3;
    }
    pp.resize(s);
    qq.resize(s);
    vector<int64_t> res(s);
    multiply_cyclic_raw(pp.data(), qq.data(), pp.size(), (uint64_t*)res.data());
    res.resize(p.size() + q.size() - 1);
    return res;
  }

  private:

  // Temporary space.
  T *tmp;

  // Returns the product of a polynomial and the monomial x^t in the ring
  // T[x]/(x^m - omega). The result is placed in `to`.
  // NOTE: t must be in the range [0,3m]
  void twiddle(T *p, uint64_t m, uint64_t t, T *to) {
    if (t == 0 || t == 3*m) {
      for (uint64_t j = 0; j < m; ++j) {
        to[j] = p[j];
      }
      return;
    }
    uint64_t tt;
    T mult = 1;
    if (t < m) {
      tt = t;
    } else if (t < 2*m) {
      tt = t - m;
      mult = OMEGA;
    } else {
      tt = t - 2*m;
      mult = OMEGA2;
    }
    for (uint64_t j=0;j<tt;j++) {
      to[j] = p[m - tt + j]*OMEGA*mult;
    }
    for (uint64_t j=tt;j<m;j++) {
      to[j] = p[j-tt]*mult;
    }
  }

  // A "Decimation In Frequency" In-Place Radix-3 FFT Routine.
  // Input: A polynomial from (T[x]/(x^m - omega))[y]/(y^r - 1).
  // Output: Its Fourier transform (w.r.t. y) in 3-reversed order.
  void fftdif(T *p, uint64_t m, uint64_t r) {
    if (r == 1) return;
    uint64_t rr = r/3;
    uint64_t pos1 = m*rr, pos2 = 2*m*rr;
    for (uint64_t i = 0; i < rr; ++i) {
      for (uint64_t j = 0; j < m; ++j) {
        tmp[j] = p[i*m + j] + p[pos1 + i*m + j] + p[pos2 + i*m + j];
        tmp[m + j] = p[i*m + j] + OMEGA*p[pos1 + i*m + j] + OMEGA2*p[pos2 + i*m + j];
        tmp[2*m + j] = p[i*m + j] + OMEGA2*p[pos1 + i*m + j] + OMEGA*p[pos2 + i*m + j];
        p[i*m + j] = tmp[j];
      }
      twiddle(tmp + m, m, 3*i*m/r, p + pos1 + i*m);
      twiddle(tmp + 2*m, m, 6*i*m/r, p + pos2 + i*m);
    }
    fftdif(p, m, rr);
    fftdif(p + pos1, m, rr);
    fftdif(p + pos2, m, rr);
  }

  // A "Decimation In Time" In-Place Radix-3 Inverse FFT Routine.
  // Input: A polynomial in (T[x]/(x^m - omega))[y]/(y^r - 1) with coefficients
  //        in 3-reversed order.
  // Output: Its inverse Fourier transform in normal order.
  void fftdit(T *p, uint64_t m, uint64_t r) {
    if (r == 1) return;
    uint64_t rr = r/3;
    uint64_t pos1 = m*rr, pos2 = 2*m*rr;
    fftdit(p, m, rr);
    fftdit(p + pos1, m, rr);
    fftdit(p + pos2, m, rr);
    for (uint64_t i = 0; i < rr; ++i) {
      twiddle(p + pos1 + i*m, m, 3*m - 3*i*m/r, tmp + m);
      twiddle(p + pos2 + i*m, m, 3*m - 6*i*m/r, tmp + 2*m);
      for(uint64_t j = 0; j < m; ++j) {
        tmp[j] = p[i*m + j];
        p[i*m + j] = tmp[j] + tmp[m + j] + tmp[2*m + j];
        p[i*m + pos1 + j] = tmp[j] + OMEGA2*tmp[m + j] + OMEGA*tmp[2*m + j];
        p[i*m + pos2 + j] = tmp[j] + OMEGA*tmp[m + j] + OMEGA2*tmp[2*m + j];
      }
    }
  }

  // Computes the product of two polynomials in T[x]/(x^n - omega), where n is
  // a power of 3. The result is placed in `to`.
  void mul(T *p, T *q, uint64_t n, T *to) {
    if (n <= 27) {
      // O(n^2) grade-school multiplication
      for (uint64_t i = 0; i < n; ++i) {
        to[i]=0;
      }
      for (uint64_t i = 0; i < n; ++i) {
        for (uint64_t j = 0; j < n - i; ++j) {
          to[i + j] += p[i]*q[j];
        }
        for (uint64_t j = n - i; j < n; ++j) {
          to[i + j - n] += p[i]*q[j]*OMEGA;
        }
      }
      return;
    }

    uint64_t m = 1;
    while (m*m < n) {
      m *= 3;
    }
    uint64_t r = n/m;

    T inv = 1;
    for (uint64_t i = 1; i < r; i *= 3) {
      inv *= INV3;
    }

    /**********************************************************
     * THE PRODUCT IN (T[x]/(x^m - omega))[y] / (y^r - omega) *
     **********************************************************/

    // Move to the ring (T[x]/(x^m - omega))[y]/(y^r - 1) via the map y -> x^(m/r) y
    for (uint64_t i = 0; i < r; ++i) {
      twiddle(p + m*i, m, m/r*i, to + m*i);
      twiddle(q + m*i, m, m/r*i, to + n + m*i);
    }

    // Multiply using FFT
    fftdif(to, m, r);
    fftdif(to + n, m, r);
    for (uint64_t i = 0; i < r; ++i) {
      mul(to + m*i, to + n + m*i, m, to +2*n + m*i);
    }
    fftdit(to + 2*n, m, r);
    for (uint64_t i = 0; i < n; ++i) {
      to[2*n + i] *= inv;
    }

    // Return to the ring (T[x]/(x^m - omega))[y]/(y^r - omega)
    for (uint64_t i = 0; i < r; ++i) {
      twiddle(to + 2*n + m*i, m, 3*m - m/r*i, to + n + m*i);
    }

    /************************************************************
     * THE PRODUCT IN (T[x]/(x^m - omega^2))[y] / (y^r - omega) *
     ************************************************************/

    // Use conjugation to move to the ring (T[x]/(x^m - omega))[y]/(y^r - omega^2).
    // Then move to (T[x]/(x^m - omega))[y]/(y^r - 1) via the map y -> x^(2m/r) y
    for (uint64_t i = 0; i < r; ++i) {
      for (uint64_t j = 0; j < m; ++j) {
        p[m*i + j] = p[m*i + j].conj();
        q[m*i + j] = q[m*i + j].conj();
      }
      twiddle(p + m*i, m, 2*m/r*i, to + m*i);
      twiddle(q + m*i, m, 2*m/r*i, p + m*i);
    }

    fftdif(to, m, r);
    fftdif(p, m, r);
    for (uint64_t i = 0; i < r; ++i) {
      mul(to + m*i, p + m*i, m, to + 2*n + m*i);
    }
    fftdit(to + 2*n, m, r);
    for (uint64_t i = 0; i < n; ++i) {
      to[2*n + i] *= inv;
    }

    for (uint64_t i = 0; i < r; ++i) {
      twiddle(to + 2*n + m*i, m, 3*m - 2*m/r*i, q + m*i);
    }

    /**************************************************************************
     * The product in (T[x]/(x^(2m) + x^m + 1))[y]/(y^r - omega) via CRT, and *
     * unravelling the substitution y = x^m at the same time.                 *
     **************************************************************************/

    for (uint64_t i = 0; i < n; ++i) {
      to[i] = 0;
    }
    for (uint64_t i = 0; i < r; ++i) {
      for (uint64_t j = 0; j < m; ++j) {
        to[i*m + j] += (1 - OMEGA)*to[n + i*m + j] + (1 - OMEGA2)*q[i*m + j].conj();
        if (i*m + m + j < n) {
          to[i*m + m + j] += (OMEGA2 - OMEGA)*(to[n + i*m + j] - q[i*m + j].conj());
        } else {
          to[i*m + m + j - n] += (1 - OMEGA2)*(to[n + i*m + j] - q[i*m + j].conj());
        }
      }
    }
    for (uint64_t i = 0; i < n; ++i) {
      to[i] *= INV3;
    }
  }

  // Computes the product of two polynomials from the ring R[x]/(x^n - 1), where
  // n must be a power of three. The result is placed in target which must have
  // space for n elements.
  void multiply_cyclic_raw(uint64_t *p, uint64_t *q, uint64_t n,
                                       uint64_t *target) {
    // If n = 3^k, let m = 3^(floor(k/2)) and r = 3^(ceil(k/2))
    uint64_t m = 1;
    while (m*m <= n) {
      m *= 3;
    }
    m /= 3;
    uint64_t r = n/m;

    // Compute 3^(-r)
    T inv = 1;
    for (uint64_t i = 1; i < r; i *= 3) {
      inv *= INV3;
    }

    // Allocate some working memory, the layout is as follows:
    // pp: length n
    // qq: length n
    // to: length n + 3*m
    // tmp: length 3*m
    T *buf = new T[3*n + 6*m];
    T *pp = buf;
    T *qq = buf + n;
    T *to = buf + 2*n;
    tmp = buf + 3*n + 3*m;

    for (uint64_t i = 0; i < n; ++i) {
      pp[i] = p[i];
      qq[i] = q[i];
    }

    // By setting y = x^m, we may write our polynomials in the form
    //   (p_0 + p_1 x + ... + p_{m-1} x^{m-1})
    // + (p_m + ... + p_{2m-1} x^{m-1}) y
    // + ...
    // + (p_{(r-1)m} + ... + p_{rm - 1} x^{m-1}) y^r
    //
    // In this way we can view p and q as elements of the ring S[y]/(y^r - 1),
    // where S = R[x]/(x^m - omega), and since r <= 3m, we know that x^{3m/r} is
    // an rth root of unity. We can therefore use FFT to calculate the product
    // in S[y]/(y^r - 1).
    fftdif(pp, m, r);
    fftdif(qq, m, r);
    for (uint64_t i = 0; i < r; ++i) {
      mul(pp + i*m, qq + i*m, m, to + i*m);
    }
    fftdit(to, m, r);
    for (uint64_t i = 0; i<n; ++i) {
      pp[i] = to[i]*inv;
    }
    
    // Now, the product in (T[x]/(x^m - omega^2))[y](y^r - 1) is simply the
    // conjugate of the product in (T[x]/(x^m - omega))[y]/(y^r - 1), because
    // there is no omega-component in the data.
    //
    // By the Chinese Remainder Theorem we can obtain the product in the
    // ring (T[x]/(x^(2m) + x^m + x))[y]/(y^r - 1), and then set y=x^m to get
    // the result.
    for (uint64_t i = 0; i < n; ++i) to[i] = 0;
    for (uint64_t i = 0; i < r; ++i) {
      for (uint64_t j = 0; j < m; ++j) {
        to[i*m + j] += (1 - OMEGA)*pp[i*m + j] + (1 - OMEGA2)*pp[i*m + j].conj();
        if (i*m + m + j < n) {
          to[i*m + m + j] += (OMEGA2 - OMEGA)*(pp[i*m + j] - pp[i*m + j].conj());
        } else {
          to[i*m + m + j - n] += (OMEGA2 - OMEGA) * (pp[i*m + j] - pp[i*m + j].conj());
        }
      }
    }
    for (uint64_t i = 0; i < n; ++i) {
      target[i] = (to[i]*INV3).a;
    }

    delete[] buf;
  }
};

using lli = int64_t;
const lli mod = 1ll << 48;

vector<lli> conv(const vector<lli> & a, const vector<lli> & b){
	Conv64 c;
	auto res = c.multiply(a, b);
	for(lli & x : res){
		x &= mod - 1;
	}
	return res;
}

vector<lli> inversePolynomial(const vector<lli> & A){
	assert(A[0] == 1);
	vector<lli> R(1, 1);
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		vector<lli> R2 = R;
		vector<lli> a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		R2 = conv(R2, R2);
		R2.resize(c);
		R2 = conv(R2, a);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - R2[i];
			if(R[i] < 0) R[i] += mod;
			if(R[i] >= mod) R[i] -= mod;
		}
	}
	R.resize(A.size());
	return R;
}

vector<lli> quotient(vector<lli> A, vector<lli> B){
	int n = A.size(), m = B.size();
	if(n < m) return vector<lli>{0};
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	A.resize(n-m+1), B.resize(n-m+1);
	A = conv(A, inversePolynomial(B));
	A.resize(n-m+1);
	reverse(A.begin(), A.end());
	return A;
}

vector<lli> remainder(vector<lli> A, const vector<lli> & B){
	int n = A.size(), m = B.size();
	if(n >= m){
		vector<lli> C = conv(quotient(A, B), B);
		A.resize(m-1);
		for(int i = 0; i < m-1; ++i){
			A[i] -= C[i];
			if(A[i] < 0) A[i] += mod;
		}
	}
	return A;
}

vector<lli> multiEvaluate(const vector<lli> &f, const vector<lli> &x) {
	int n = x.size();
	if (!n) {
		return vector<lli>();
	}
	vector<vector<lli>> up(n * 2);
	for (int i = 0; i < n; ++i) {
		up[i + n] = vector<lli>{(mod - x[i]) % mod, 1};
	}
	for (int i = n - 1; i; --i) {
		up[i] = conv(up[i << 1], up[i << 1 | 1]);
	}
	cerr << "two\n";
	vector<vector<lli>> down(n * 2);
	down[1] = remainder(f, up[1]);
	for (int i = 2; i < n * 2; ++i) {
		down[i] = remainder(down[i >> 1], up[i]);
	}
	cerr << "three\n";
	vector<lli> y(n);
	for (int i = 0; i < n; ++i) {
		y[i] = down[i + n][0];
	}
	return y;
}

vector<lli> calc(lli l, lli r){
	if(l == r) return {2*l + 1, 1};
	lli m = (l + r) / 2;
	return conv(calc(l, m), calc(m+1, r));
}

lli factorial(lli n){
	int sz = max(1, (int)sqrt(n / 2.0));
	vector<lli> poly = calc(0, sz - 1);
	cerr << "one\n";
	lli l = 1, r = 2*sz - 1, curr = 0;
	vector<lli> points;
	while(r <= n){
		points.push_back(curr);
		l += 2*sz, r += 2*sz, curr += 2*sz;
	}
	vector<lli> res = multiEvaluate(poly, points);
	lli ans = 1;
	for(lli x : res){
		ans = (ans * x) & (mod - 1);
	}
	for(lli i = l; i <= n; i += 2){
		ans = (ans * i) & (mod - 1);
	}
	return ans;
}




lli potInFactorial(lli n, lli p){
	lli ans = 0, div = n;
	while(div /= p) ans += div;
	return ans;
}

lli factmod2(lli n, int s){
	lli ans = 1;
	lli ps = 1ll << s;
	while(n > 1){
		lli q = n >> s, r = n & (ps - 1);
		cerr << (int64_t)r << "\n";
		ans = ans * (q % 2 == 1 && !(s >= 3) ? ps-1 : 1) & (ps - 1);
		if(!(r & 1)) r--;
		ans = (ans * factorial(r)) & (ps - 1);
		n >>= 1;
	}
	return ans;
}

int main(){
	lli N = 1;
	for(int i = 1; i <= 20; ++i){
		N *= i;
	}
	//N = 20;

	lli pot = potInFactorial(N, 2);
	lli ans = (factmod2(N, 48) << (pot % 4)) & ((1ll << 48) - 1);
	cout << hex << uppercase << int64_t(ans) << "\n";
	return 0;
}