#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli Pow(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a);
		b >>= 1;
		a = (a * a);
	}
	return ans;
}

lli mod(lli a, lli b){
	return (a - 1) % b + 1;
}

vector<lli> primes;

void sieve(lli n){
	vector<bool> isPrime(n + 1, true);
	primes.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(isPrime[i]){
			primes.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2 * i){
					isPrime[j] = false;
				}
			}
		}
	}
}

map<lli, int> factorize(lli n){
	map<lli, int> f;
	for(lli & p : primes){
		if(p * p > n) break;
		int pot = 0;
		while(n % p == 0){
			n /= p;
			pot++;
		}
		if(pot) f[p] = pot;
	}
	if(n > 1) f[n] = 1;
	return f;
}

map<lli, int> f_n;

lli wedge(lli m){
	lli ans = 1;
	map<lli, int> f_m = factorize(m);
	for(auto & f : f_m){
		ans *= Pow(f.first, f_n[f.first]);
	}
	return ans;
}

//apply the permutation A to permutation B
vector<int> product(const vector<int> & A, const vector<int> & B){
	int n = A.size() - 1;
	vector<int> ans(n + 1);
	for(int i = 1; i <= n; i++){
		ans[i] = B[A[i]];
	}
	return ans;
}

vector<int> inverse(const vector<int> & A){
	int n = A.size() - 1;
	vector<int> ans(n + 1);
	for(int i = 1; i <= n; i++){
		ans[A[i]] = i;
	}
	return ans;
}

vector<int> root(const vector<int> & sigma, lli power){
	int n = sigma.size() - 1;
	vector<bool> visited(n + 1, false);
	unordered_map<int, vector<vector<int>>> cycles;
	for(int i = 1; i <= n; i++){
		if(!visited[i]){
			vector<int> cycle(1);
			visited[i] = true;
			int current = i;
			cycle.push_back(current);
			do{
				current = sigma[current];
				visited[current] = true;
				if(current != i) cycle.push_back(current);
			}while(current != i);
			cycles[cycle.size() - 1].push_back(cycle);
		}
	}
	vector<int> ans(n + 1);
	for(auto & it : cycles){
		int m = it.first;
		int vm = it.second.size();
		int g = wedge(m); //also, we can use any g such that g<=vm and g = gcd(g*m, power)
		if((vm % g) != 0){
			cout << "-1";
			exit(0);
		}
		int bundles = vm / g;
		int current = 0;
		for(int b = 1; b <= bundles; b++){
			int size_resultant = m * g;
			vector<int> resultant(size_resultant + 1);
			for(int i = 1; i <= g; i++){
				vector<int> & cycle = it.second[current++];
				lli pos = i;
				for(int j = 1; j <= m; j++){
					resultant[pos] = cycle[j];
					pos = mod(pos + power, size_resultant);
				}
			}
			for(int i = 1; i <= size_resultant; i++){
				int source = resultant[i];
				int dest = resultant[mod(i + 1, size_resultant)];
				ans[source] = dest;
			}
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	sieve(50000);
	int n;
	lli t, power;
	cin >> n >> t;
	vector<int> P(n + 1), B(n + 1);
	for(int i = 1; i <= n; i++){
		cin >> P[i];
	}
	for(int i = 1; i <= n; i++){
		cin >> B[i];
	}
	if(t & 1ll){
		B = product(P, B);
		power = (t + 1ll) >> 1;
	}else{
		power = t >> 1;
	}
	f_n = factorize(power);
	vector<int> ans = product(inverse(P), root(B, power));
	for(int i = 1; i <= n; i++){
		cout << ans[i] << " ";
	}
	return 0;
}