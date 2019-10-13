#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 87;

vector<int> sieve(int n){
	vector<int> isPrime(n + 1, true);
	vector<int> primes;
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const int limit = 1e7;
const int cnt = 10;

const vector<int> primes = sieve(limit);

lli pot_fact(lli n, lli p){
	lli ans = 0;
	while(n /= p) ans += n;
	return ans;
}

lli s(lli n){
	lli ans = 1;
	for(lli p : primes){
		if(p > n) break;
		ans = ans * (2 * pot_fact(n, p) + 1) % mod;
	}
	return ans;
}

atomic<lli> sum(0);
atomic<lli> progress(0);

void f(lli a, lli b){
	lli ans = 0;
	for(lli i = a; i <= b; ++i){
		ans += s(i);
		progress++;
		if(ans >= mod) ans -= mod;
	}
	sum += ans;
	if(sum >= mod) sum -= mod;
}

int main(){
	lli work = limit / cnt;
	vector<thread*> threads(cnt);
	for(int i = 0; i < cnt; ++i){
		threads[i] = new thread(f, work * i + 1, i == cnt-1 ? limit : work * (i + 1));
	}
	auto f = []{
		while(1){
			cout << "Progress: " << progress << " / " << limit << " (" << (double)progress / limit * 100 << "%)" << endl;
			if(progress == limit) break;
			this_thread::sleep_for(chrono::seconds(3));
		}
	};
	thread watch(f);
	for(int i = 0; i < cnt; ++i){
		threads[i]->join();
	}
	watch.join();
	cout << sum-1 << endl;
	return 0;
}