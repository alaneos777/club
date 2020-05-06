#include <bits/stdc++.h>
using namespace std;

void print(int n, const vector<int> & difs, const vector<int> & lengths){
	cout << "1\n";
	int acum = 0;
	for(int i = 0; i < lengths.size(); ++i){
		acum += lengths[i];
		cout << acum << " " << (difs[i] - (i+1 < n ? difs[i+1] : 0)) << "\n";
	}
}

bool decreasing(const vector<int> & a){
	for(int i = 0; i < (int)a.size() - 1; ++i){
		if(a[i] <= a[i+1]) return false;
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n, k;
		cin >> n >> k;
		vector<int> a(k+1);
		for(int & ai : a){
			cin >> ai;
		}
		while(a.size() >= 2 && a[a.size()-2] == 0 && a[a.size()-1] == 0){
			a.pop_back();
			--k;
		}
		if(k == 0 || !decreasing(a)){
			cout << "0\n";
			continue;
		}
		int prev = -1, len = 0;
		vector<int> difs, lengths;
		for(int i = 1; i <= k; ++i){
			int dif = a[i-1] - a[i];
			if(dif != prev && prev != -1){
				difs.push_back(prev);
				if(len != 0) lengths.push_back(len);
				len = 0;
			}
			len++;
			prev = dif;
		}
		difs.push_back(prev);
		lengths.push_back(len);
		if(!decreasing(difs)){
			cout << "0\n";
			continue;
		}
		if(lengths.size() > n){
			cout << "0\n";
		}else if(lengths.size() == n){
			if(a.back() % difs.back() > 0){
				cout << "0\n";
			}else{
				lengths.back() += a.back() / difs.back();
				print(n, difs, lengths);
			}
		}else if(n - (int)lengths.size() == 1){
			int cnt_sols = 0;
			vector<int> difs_sol, lengths_sol;
			int B = difs.back();
			while(a.back() > 0){
				if(cnt_sols >= 2) break;
				int A = a.back();
				for(int d = 1; d < B; ++d){
					if(A % d == 0){
						difs_sol = difs, lengths_sol = lengths;
						cnt_sols++;
						difs_sol.push_back(d);
						lengths_sol.push_back(A/d);
					}
				}
				a.push_back(a.back() - B);
				lengths.back()++;
			}
			if(cnt_sols == 0){
				cout << "0\n";
			}else if(cnt_sols == 1){
				print(n, difs_sol, lengths_sol);
			}else{
				cout << "2\n";
			}
		}else{
			int cnt_sols = 0;
			vector<int> difs_sol, lengths_sol;
			int B = difs.back();
			int x = n - (int)lengths.size();
			while(a.back() >= 0){
				if(cnt_sols >= 2) break;
				int A = a.back();
				int sum = x * (x + 1) / 2;
				if(B >= x+1 && A >= sum){
					if(A == sum){
						difs_sol = difs, lengths_sol = lengths;
						cnt_sols++;
						for(int i = x; i >= 1; --i){
							difs_sol.push_back(i);
							lengths_sol.push_back(1);
						}
					}else if(x+1 == B && A == sum+1){
						difs_sol = difs, lengths_sol = lengths;
						cnt_sols++;
						for(int i = x; i >= 1; --i){
							difs_sol.push_back(i);
							lengths_sol.push_back(i == 1 ? 2 : 1);
						}
					}else{
						cnt_sols += 2;
					}
				}
				a.push_back(a.back() - B);
				lengths.back()++;
			}
			if(cnt_sols == 0){
				cout << "0\n";
			}else if(cnt_sols == 1){
				print(n, difs_sol, lengths_sol);
			}else{
				cout << "2\n";
			}
		}
	}
	return 0;
}