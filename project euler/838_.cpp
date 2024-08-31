#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

template<typename T>
struct flowEdge{
	int dest;
	T flow, capacity;
	flowEdge *res;

	flowEdge(): dest(0), flow(0), capacity(0), res(NULL){}
	flowEdge(int dest, T flow, T capacity): dest(dest), flow(flow), capacity(capacity), res(NULL){}

	void addFlow(T flow){
		this->flow += flow;
		this->res->flow -= flow;
	}
};

template<typename T>
struct flowGraph{
	T inf = numeric_limits<T>::max();
	vector<vector<flowEdge<T>*>> adjList;
	vector<int> dist, pos;
	int V;
	flowGraph(int V): V(V), adjList(V), dist(V), pos(V){}
	~flowGraph(){
		for(int i = 0; i < V; ++i)
			for(int j = 0; j < adjList[i].size(); ++j)
				delete adjList[i][j];
	}
	void addEdge(int u, int v, T capacity){
		flowEdge<T> *uv = new flowEdge<T>(v, 0, capacity);
		flowEdge<T> *vu = new flowEdge<T>(u, capacity, capacity);
		uv->res = vu;
		vu->res = uv;
		adjList[u].push_back(uv);
		adjList[v].push_back(vu);
	}

	T blockingFlow(int u, int t, T flow){
		if(u == t) return flow;
		for(int &i = pos[u]; i < adjList[u].size(); ++i){
			flowEdge<T> *v = adjList[u][i];
			if(v->capacity > v->flow && dist[u] + 1 == dist[v->dest]){
				T fv = blockingFlow(v->dest, t, min(flow, v->capacity - v->flow));
				if(fv > 0){
					v->addFlow(fv);
					return fv;
				}
			}
		}
		return 0;
	}
	T dinic(int s, int t){
		T maxFlow = 0;
		dist[t] = 0;
		while(dist[t] != -1){
			fill(dist.begin(), dist.end(), -1);
			queue<int> Q;
			Q.push(s);
			dist[s] = 0;
			while(!Q.empty()){
				int u = Q.front(); Q.pop();
				for(flowEdge<T> *v : adjList[u]){
					if(dist[v->dest] == -1 && v->flow != v->capacity){
						dist[v->dest] = dist[u] + 1;
						Q.push(v->dest);
					}
				}
			}
			if(dist[t] != -1){
				T f;
				fill(pos.begin(), pos.end(), 0);
				while(f = blockingFlow(s, t, inf))
					maxFlow += f;
			}
		}
		return maxFlow;
	}
};

auto lpSieve(int n){
	vector<int> lp(n+1), primes;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			lp[i] = i;
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const int M = 1e6;
const auto lp = lpSieve(M);

vector<int> getPrimeFactors(int n){
	vector<int> factors;
	while(n > 1){
		int p = lp[n];
		while(n%p == 0){
			n /= p;
		}
		factors.push_back(p);
	}
	return factors;
}

int getRad(int n){
	int rad = 1;
	while(n > 1){
		int p = lp[n];
		while(n%p == 0){
			n /= p;
		}
		rad *= p;
	}
	return rad;
}

int main(){
	set<int> rads;
	vector<bool> sieve(M+1);
	for(int i = 3; i <= M; i += 10){
		int r = getRad(i);
		rads.insert(r);
		sieve[r] = true;
	}
	ld ans = 0;
	for(int i : rads){
		if(sieve[i]){
			if(lp[i] == i) ans += logl(i);
			for(int j = lp[i] == i ? i : 2*i; j <= M; j += i){
				sieve[j] = false;
			}
		}
	}
	map<int, int> ids;
	vector<int> nums;
	for(int i = 1; i <= M; ++i){
		if(sieve[i]){
			nums.push_back(i);
			for(int p : getPrimeFactors(i)){
				if(ids.count(p) == 0) ids[p] = ids.size();
			}
		}
	}
	flowGraph<lli> g(ids.size()+2);
	int S = ids.size(), T = S+1;
	set<int> lhs, rhs;
	for(int i = 0; i < nums.size(); ++i){
		auto primeFactors = getPrimeFactors(nums[i]);
		assert(primeFactors.size() == 2);
		int u = primeFactors[0], v = primeFactors[1];
		if(u%10 == 9) swap(u, v);
		lhs.insert(u);
		rhs.insert(v);
		g.addEdge(ids[u], ids[v], g.inf);
	}
	for(int p : lhs){
		g.addEdge(S, ids[p], lli(logl(p) * 1e15));
	}
	for(int q : rhs){
		g.addEdge(ids[q], T, lli(logl(q) * 1e15));
	}
	ans += g.dinic(S, T)/1e15;
	cout << fixed << setprecision(6) << ans << "\n";
	return 0;
}