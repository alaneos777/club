#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ull = unsigned long long int;

vector<pair<lli, int>> factorize(lli n){
	vector<pair<lli, int>> f;
	for(lli i = 2; i <= sqrt(n); ++i){
		int pot = 0;
		while(n % i == 0){
			n /= i;
			pot++;
		}
		if(pot){
			f.emplace_back(i, pot);
		}
	}
	if(n > 1){
		f.emplace_back(n, 1);
	}
	return f;
}

lli techo(lli a, lli b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		if(a % b == 0) return a / b;
		else return a / b + 1;
	}else{
		return a / b;
	}
}

ull mult(ull a, ull b, ull m){
	ull ans = 0;
	while(b){
		if(b & 1) ans = (ans + a) % m;
		b >>= 1;
		a = (a + a) % m;
	}
	return ans;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

ull inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 == -1) s0 *= -1;
	if(s0 < 0) s0 += m;
	return s0;
}

pair<lli, lli> crt(const vector<lli> & a, const vector<lli> & m){
	map<lli, pair<int, lli>> congruences; //prime, <pot, ai>
	int n = a.size();
	for(int i = 0; i < n; ++i){
		auto f = factorize(m[i]);
		for(auto & par : f){
			lli p;
			int pot;
			tie(p, pot) = par;
			if(congruences.find(p) == congruences.end()){
				congruences[p] = {pot, a[i]};
			}else{
				lli oldAi;
				int oldPot;
				tie(oldPot, oldAi) = congruences[p];
				if((oldAi - a[i]) % power(p, min(oldPot, pot)) == 0){
					if(pot > oldPot){
						congruences[p] = {pot, a[i]};
					}
				}else{
					return {0, 0}; //error
				}
			}
		}
	}
	ull allProd = 1;
	for(auto & c : congruences){
		allProd *= (ull)power(c.first, c.second.first);
	}
	ull ans = 0;
	for(auto & c : congruences){
		lli pi = c.first;
		int pot;
		ull ai;
		tie(pot, ai) = c.second;
		ull mi = power(pi, pot);
		ull prod = allProd / mi;
		ans = (ans + mult(mult(ai % mi, inv(prod, mi), allProd), prod, allProd)) % allProd;
	}
	return {ans, allProd};
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int b, z;
	cin >> b >> z;
	vector<vector<pair<int, int>>> times(z); // equation mt+b, <m, b>
	for(int i = 0; i < b; ++i){
		int start;
		cin >> start;
		--start;
		vector<int> sigma(z);
		for(auto & s : sigma){
			cin >> s;
			--s;
		}
		vector<bool> visited(z);
		int curr = start, startCycle = -1;
		visited[curr] = true;
		while(true){
			curr = sigma[curr];
			if(visited[curr]){
				startCycle = curr;
				break;
			}
			visited[curr] = true;
		}

		curr = start;
		int time = 0;
		while(curr != startCycle){
			times[curr].emplace_back(0, time++);
			curr = sigma[curr];
		}

		int cycleLength = 0;
		curr = startCycle;
		do{
			cycleLength++;
			curr = sigma[curr];
		}while(curr != startCycle);

		curr = startCycle;
		do{
			times[curr].emplace_back(cycleLength, time++);
			curr = sigma[curr];
		}while(curr != startCycle);
	}

	lli ans = -1;
	int node = -1;
	for(int i = 0; i < z; ++i){
		auto & info = times[i];
		lli reachTime = -1;
		vector<lli> a, m;
		if(info.size() != b) continue;
		//cout << "Equations for node " << i++ << ":\n";
		for(auto & equation : info){
			lli ai, mi;
			tie(mi, ai) = equation;
			if(mi != 0){
				a.emplace_back(ai);
				m.emplace_back(mi);
			}
			//cout << " t = " << ai << " mod " << mi << "\n";
		}
		lli time = 0, modulo = 1;
		if(a.size() > 0){
			tie(time, modulo) = crt(a, m);
		}
		if(modulo == 0){
			continue;
		}
		bool equal = true;
		lli commonValue = -1;
		lli k = 0;
		for(auto & equation : info){
			lli ai, mi;
			tie(mi, ai) = equation;
			//t = ai mod mi
			//t = time mod modulo
			if(mi == 0){
				if(commonValue == -1){
					commonValue = ai;
				}else if(commonValue != ai){
					equal = false;
				}
			}else{
				k = max(k, techo(ai - time, modulo));
			}
		}
		time += modulo * k;
		//cout << time << " + " << modulo << "k " << commonValue << "\n";
		if(equal){
			if(commonValue != -1){
				//t = commonValue
				//t = time + k*modulo, k >= 0
				if(commonValue >= time && (commonValue - time) % modulo == 0){
					reachTime = commonValue;
				}
			}else{
				reachTime = time;
			}
		}
		if(reachTime != -1){
			if(ans == -1 || reachTime < ans){
				ans = reachTime;
				node = i;
			}
		}
	}

	if(ans == -1){
		cout << "*\n";
	}else{
		cout << node+1 << " " << ans << "\n";
	}
	return 0;
}