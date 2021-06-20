#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli techo(lli a, lli b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		if(a % b == 0) return a / b;
		else return a / b + 1;
	}else{
		return a / b;
	}
}

tuple<lli, lli, lli> extgcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extgcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

pair<lli, lli> crt(const vector<lli>& a, const vector<lli>& m){
	lli x = a[0], mod = m[0];
	for(int i = 1; i < a.size(); ++i){
		auto[d, s, t] = extgcd(mod, -m[i]);
		if((a[i] - x) % d != 0) return {-1, -1};
		lli step = m[i] / d;
		lli k = s * (((a[i] - x) / d) % step) % step;
		if(k < 0) k += step;
		x += mod*k;
		mod *= step;
	}
	return {x, mod};
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
				a.emplace_back(ai % mi);
				m.emplace_back(mi);
			}
			//cout << " t = " << ai << " mod " << mi << "\n";
		}
		lli time = 0, modulo = 1;
		if(a.size() > 0){
			tie(time, modulo) = crt(a, m);
		}
		if(modulo == -1){
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