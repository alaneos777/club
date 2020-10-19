#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct SumPrimePi{
	int v;
	lli n;
	int k;
	vector<T> lo, hi;
	vector<int> primes;

	SumPrimePi(lli n, int k = 0): n(n), v(sqrt(n)), k(k){
		lo.resize(v+2), hi.resize(v+2);
	}

	T power(T a, lli b){
		T ans = 1;
		while(b){
			if(b & 1) ans *= a;
			b >>= 1;
			a *= a;
		}
		return ans;
	}

	T powerSum(T n, int k){
		if(k == 0) return n;
		if(k == 1) return n * (n + 1) / 2;
		if(k == 3) return powerSum(n, 1) * powerSum(n, 1);
		return 0;
	}

	void build(){
		lli p, q, j, end, i, d;
		T temp;
		for(p = 1; p <= v; p++){
			lo[p] = powerSum(p, k) - 1;
			hi[p] = powerSum(n/p, k) - 1;
		}
		for(p = 2; p <= v; p++){
			T pk = power(p, k);
			if(lo[p] == lo[p-1]) continue;
			primes.push_back(p);
			temp = lo[p-1];
			q = p * p;
			end = (v <= n/q) ? v : n/q;
			for(i = 1; i <= end; ++i){
				d = i * p;
				if(d <= v)
					hi[i] -= (hi[d] - temp) * pk;
				else
					hi[i] -= (lo[n/d] - temp) * pk;
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp) * pk;
			}
		}
	}

	T get(lli i) const{
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

template<typename T>
struct SumPrimePiModulo4{
	int v;
	lli n;
	vector<T> lo, hi;
	vector<T> lo1, hi1;

	SumPrimePiModulo4(lli n): n(n), v(sqrt(n)){
		lo.resize(v+2), hi.resize(v+2);
		lo1.resize(v+2), hi1.resize(v+2);
	}

	void build(){
		lli p, q, j, end, i, d;
		T temp, temp1;
		for(p = 1; p <= v; p++){
			lo[p] = p - 1;
			hi[p] = n/p - 1;
			lo1[p] = (p + 3) / 4 - 1;
			hi1[p] = (n/p + 3) / 4 - 1;
		}
		for(p = 2; p <= v; p++){
			if(lo[p] == lo[p-1]) continue;
			temp = lo[p-1];
			temp1 = lo1[p-1];
			q = p * p;
			end = (v <= n/q) ? v : n/q;
			for(i = 1; i <= end; ++i){
				d = i * p;
				if(d <= v){
					hi[i] -= (hi[d] - temp);
					if(p % 4 == 1)
						hi1[i] -= (hi1[d] - temp1);
					else if(p % 4 == 3)
						hi1[i] -= (hi[d] - hi1[d]) - (temp - temp1);
				}else{
					hi[i] -= (lo[n/d] - temp);
					if(p % 4 == 1)
						hi1[i] -= (lo1[n/d] - temp1);
					else if(p % 4 == 3)
						hi1[i] -= (lo[n/d] - lo1[n/d]) - (temp - temp1);
				}
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp);
				if(p % 4 == 1)
					lo1[i] -= (lo1[i/p] - temp1);
				else if(p % 4 == 3)
					lo1[i] -= (lo[i/p] - lo1[i/p]) - (temp - temp1);
			}
		}
	}

	T get(lli i) const{
		T ans = 0;
		if(i <= v) ans = lo[i] - 2*lo1[i];
		else ans = hi[n/i] - 2*hi1[n/i];
		if(i >= 2) ans--;
		return ans;
	}
};

template<typename T>
struct MultiplicativeSum{
	int v;
	lli n;
	vector<T> lo, hi, smallFP;
	vector<int> primes;

	MultiplicativeSum(lli n, const vector<int> & primes): n(n), v(sqrt(n)), primes(primes){
		lo.resize(v+2), hi.resize(v+2), smallFP.resize(v+2);
	}

	void add(T coef, const auto & pi){
		assert(pi.n == n);
		for(int i = 1; i <= v; ++i){
			smallFP[i] += coef * pi.get(i);
			hi[i] += coef * (pi.get(n/i) - pi.get(v));
		}
	}

	T getAdded(lli i, lli p){
		if(i <= v){
			return lo[i] + smallFP[max(i, p)] - smallFP[p];
		}else{
			return hi[n/i] + smallFP[v] - smallFP[p];
		}
	}

	void build(function<T(lli, int)> g){
		for(int i = 1; i <= v; ++i){
			lo[i] += 1;
			hi[i] += 1;
		}
		for(int r = (int)primes.size()-1; r >= 0; --r){
			lli p = primes[r];
			vector<lli> p_power(1, 1);
			vector<T> gs(1, T(1));
			lli p_pow = p;
			for(int e = 1; ; ++e){
				p_power.push_back(p_pow);
				gs.push_back(g(p, e));
				if(p_pow > n/p) break;
				p_pow *= p;
			}
			for(int i = 1; i <= v; ++i){
				lli next = n / i;
				if(next < p*p) break;
				for(int e = 1; e < p_power.size() && p_power[e] <= next; ++e){
					hi[i] += gs[e] * getAdded(next / p_power[e], p);
				}
				hi[i] -= gs[1];
			}
			for(int i = v; i >= 1; --i){
				if(i < p*p) break;
				for(int e = 1; e <= p_power.size() && p_power[e] <= i; ++e){
					lo[i] += gs[e] * getAdded(i / p_power[e], p);
				}
				lo[i] -= gs[1];
			}
		}
		for(int i = 1; i <= v; ++i){
			lo[i] += smallFP[i];
			hi[i] += smallFP[v];
		}
	}

	T get(lli i) const{
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}
 
template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;
 
  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }
 
  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }
 
  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }
 
  Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }
 
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm(
      "divl %4; \n\t"
      : "=a" (d), "=d" (m)
      : "d" (xh), "a" (xl), "r" (mod())
    );
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type& operator*=(const Modular& rhs) {
    int64_t q = static_cast<int64_t>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }
 
  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }
 
  template <typename U>
  friend const Modular<U>& abs(const Modular<U>& v) { return v; }
 
  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);
 
  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);
 
  template <typename U>
  friend std::istream& operator>>(std::istream& stream, Modular<U>& number);
 
 private:
  Type value;
};
 
template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }
 
template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
 
template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }
 
template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
 
template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
 
template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
 
template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

 
template <typename T>
bool IsZero(const Modular<T>& number) {
  return number() == 0;
}
 
template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}
 
template <typename T>
std::ostream& operator<<(std::ostream& stream, const Modular<T>& number) {
  return stream << number();
}
 
template <typename T>
std::istream& operator>>(std::istream& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, int64_t>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}
 
constexpr int md = 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

Mint power(Mint a, lli b) {
  Mint ans = 1;
  while(b){
  	if(b & 1) ans *= a;
  	b >>= 1;
  	a *= a;
  }
  return ans;
}

const lli N = 1e12;

int main(){
	SumPrimePi<Mint> sum_3(N, 3);
	sum_3.build();

	SumPrimePiModulo4<Mint> sum_4(N);
	sum_4.build();

	MultiplicativeSum<Mint> ms(N, sum_3.primes);
	ms.add(1, sum_3);
	ms.add(1, sum_4);

	ms.build([](lli p, int a){
		Mint ans = power(p, 3*a);
		if(p >= 3){
			if((p & 3) == 3){
				ans += power(p, 3*a - 3);
			}else{
				ans -= power(p, 3*a - 3);
			}
		}
		return ans;
	});

	cout << ms.get(N) << "\n";
	return 0;
}