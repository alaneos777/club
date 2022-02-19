#include <bits/stdc++.h>
using namespace std;

int ask(int l, int r){
	cout << r-l+1;
	for(int i = l; i <= r; ++i){
		cout << " " << i;
 	}
 	cout << endl;
 	string resp;
 	cin >> resp;
	return resp == "Yes";
}

const int M = 144;
int mem[M+1][M+1], steps[M+1][M+1];
int f(int l, int r){
	if(l >= r) return 0;
	int& ans = mem[l][r];
	if(ans) return ans;
	int& i_min = steps[l][r];
	ans = 1e9;
	for(int i = l; i <= r; ++i){
		int nxt = max(f(l, i) + 2, f(i+1, r) + 1);
		if(nxt < ans){
			ans = nxt;
			i_min = i;
		}
	}
	return ans;
}

int main(){
	for(int l = 1; l <= M; ++l){
		for(int r = 1; r <= M; ++r){
			f(l, r);
		}
	}
	int n;
	cin >> n;
	if(n < f(1, M)){
		cout << "Not enough money" << endl;
	}else{
		cout << "Let's play!" << endl;
		int cost = 0;
		int l = 1, r = M;
		while(l <= r){
			if(l == r){
				cout << "0 " << l << endl;
				break;
			}
			int mid = steps[l][r];
			if(ask(l, mid)){
				r = mid;
				cost += 2;
			}else{
				l = mid+1;
				cost += 1;
			}
		}
		assert(cost <= n);
	}
	return 0;
}