#include <bits/stdc++.h>
using namespace std;

int mex(const vector<int> & a){
	int n = a.size();
	vector<bool> b(n);
	for(int ai : a){
		if(ai < n) b[ai] = true;
	}
	for(int i = 0; i < n; ++i){
		if(!b[i]) return i;
	}
	return n;
}

const int M = 1e6; 
int mem[M+10];

int f(int n){
	if(n <= 1) return 0;
	if(n == 2) return 1;
	if(mem[n] != -1) return mem[n];
	vector<int> conj;
	for(int i = 0; i <= n-2; ++i){
		conj.push_back(f(i) ^ f(n-2-i));
	}
	return mem[n] = mex(conj);
}

int main(){
	memset(mem, -1, sizeof(mem));
	/*for(int i = 1; i <= 50; ++i){
		cout << "g(" << i << ") = " << f(i) << "\n";
	}*/
	vector<int> lose = {1, 5, 9, 15, 21, 25, 29, 35, 39, 43, 55, 59, 63, 73};
	while(lose.back() <= 1e6){
		lose.push_back(lose[lose.size() - 5] + 34);
	}
	lose.pop_back();
	cout << M-lose.size() << "\n";
	return 0;
}