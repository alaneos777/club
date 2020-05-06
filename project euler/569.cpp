#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const int M = 2.5e6;
const auto primes = sieve(4 * M * log(M));

struct point{
	lli x, y;
	int id;
	point(): x(0), y(0) {}
	point(lli x, lli y): x(x), y(y) {}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}

	lli cross(const point & p) const{return x * p.y - y * p.x;}
};

int main(){
	assert(primes.size() >= M);
	point P;
	vector<point> peaks(M);
	for(int i = 0, k = 0; i < M; ++i, ++k){
		P = P + point(primes[k], primes[k]);
		++k;
		peaks[i] = P;
		peaks[i].id = i;
		P = P + point(primes[k], -primes[k]);
	}

	int64_t ans = 0;
	vector<point> slopes(M);
	slopes[0] = point(0, -1);
	for(int i = 1; i < M; ++i){
		point current_slope = peaks[i-1] - peaks[i];
		for(int j = i-1; j >= 0; --j){
			point slope = peaks[j] - peaks[i];
			if(current_slope.cross(slope) <= 0){
				ans++;
				current_slope = slope;
			}
			if(current_slope.cross(slopes[j]) > 0) break;
		}
		slopes[i] = current_slope;
	}
	cout << ans << "\n";
	return 0;
}