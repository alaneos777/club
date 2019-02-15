#include <bits/stdc++.h>
using namespace std;

bool ps(double x){
	return abs(x - round(x)) < 1e-8;
}

bool check(int p, int x){
	if(x == 0) return false;
	if(p == 3) return ps((sqrt(8*x + 1) - 1) / 2);
	if(p == 4) return ps(sqrt(x));
	if(p == 5) return ps((sqrt(24*x + 1) + 1) / 6);
	if(p == 6) return ps((sqrt(8*x + 1) + 1) / 4);
	if(p == 7) return ps((sqrt(40*x + 9) + 3) / 10);
	if(p == 8) return ps((sqrt(3*x + 1) + 1) / 3);
}

using vb = vector<bool>;
using vi = vector<int>;

bool tryKuhn(vector<vi> & adj, int u, vb & used, vi & left, vi & right){
	if(used[u]) return false;
	used[u] = true;
	for(int v : adj[u]){
		if(right[v] == -1 || tryKuhn(adj, right[v], used, left, right)){
			right[v] = u;
			left[u] = v;
			return true;
		}
	}
	return false;
}

int maxMatching(vector<vi> & adj, int l, int r){
	vi left(l, -1), right(r, -1);
	vb used(l);
	for(int u = 0; u < l; ++u){
		tryKuhn(adj, u, used, left, right);
		fill(used.begin(), used.end(), false);
	}
	int ans = 0;
	for(int u = 0; u < r; ++u){
		if(right[u] != -1){
			ans++;
		}
	}
	return ans;
}

int cnt(const vector<int> & n){
	vector<vector<int>> adj(6);
	for(int i = 3; i <= 8; ++i){
		for(int j = 0; j < n.size(); ++j){
			if(check(i, n[j])){
				adj[i-3].push_back(j);
			}
		}
	}
	return maxMatching(adj, 6, n.size());
}

void solve(vector<string> & conj){
	if(conj.size() == 4){
		if(cnt({stoi(conj[0] + conj[1] + conj[2] + conj[3])}) < 1) return;
	}
	if(conj.size() == 6){
		if(cnt({stoi(conj[0] + conj[1] + conj[2] + conj[3]), stoi(conj[2] + conj[3] + conj[4] + conj[5])}) < 2) return;
	}
	if(conj.size() == 8){
		if(cnt({stoi(conj[0] + conj[1] + conj[2] + conj[3]), stoi(conj[2] + conj[3] + conj[4] + conj[5]), stoi(conj[4] + conj[5] + conj[6] + conj[7])}) < 3) return;
	}
	if(conj.size() == 10){
		if(cnt({stoi(conj[0] + conj[1] + conj[2] + conj[3]), stoi(conj[2] + conj[3] + conj[4] + conj[5]), stoi(conj[4] + conj[5] + conj[6] + conj[7]), stoi(conj[6] + conj[7] + conj[8] + conj[9])}) < 4) return;
	}
	if(conj.size() == 12){
		vector<int> numbers = {stoi(conj[0] + conj[1] + conj[2] + conj[3]), stoi(conj[2] + conj[3] + conj[4] + conj[5]), stoi(conj[4] + conj[5] + conj[6] + conj[7]), stoi(conj[6] + conj[7] + conj[8] + conj[9]), stoi(conj[8] + conj[9] + conj[10] + conj[11]), stoi(conj[10] + conj[11] + conj[0] + conj[1])};
		if(cnt(numbers) == 6){
			int sum = 0;
			for(int ni : numbers){
				for(int i = 3; i <= 8; ++i){
					if(check(i, ni)){
						cout << " " << i;
					}
				}
				cout << " -> " << ni << "\n";
				sum += ni;
			}
			cout << sum << "\n";
			exit(0);
		}
	}else{
		for(int i = 0; i <= 9; ++i){
			if((conj.size() == 0 || conj.size() == 2 || conj.size() == 4 || conj.size() == 6 || conj.size() == 8 || conj.size() == 10) && i == 0) continue;
			conj.push_back(to_string(i));
			solve(conj);
			conj.resize((int)conj.size()-1);
		}
	}
}

int main(){
	vector<string> conj;
	solve(conj);
	return 0;
}