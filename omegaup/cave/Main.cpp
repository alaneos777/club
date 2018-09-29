#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
int down[5000];
int door[5000];
int tries = 0;
int exitcode = 1;
const int maxTries = 70000;

int tryCombination(int _, int S[]) {
	if (_ != N) {
		cout << "WA - Size of array does not match N" << endl;
		exit(0);
	}
	if (tries++ == maxTries) {
		cout << "WA - Max tries exceeded" << endl;
		exit(0);
	}

	for (int i = 0; i < N; i++) {
		if (down[door[i]] != S[door[i]]) {
			return i;
		}
	}

	return -1;
}

void answer(int _, int S[], int D[]) {
	if (_ != N) {
		cout << "WA - Size of array does not match N" << endl;
		exit(0);
	}
	for (int i = 0; i < N; i++) {
		if (S[i] != down[i]) {
			cout << "WA - Wrong switch configuration. Switch " << (i + 1) << " was " << S[i] << " expecting " << down[i] << endl;
			exit(0);
		}
	}
	for (int i = 0; i < N; i++) {
		if (door[D[i]] != i) {
			cout << "WA - Wrong door configuration, Door " << (i + 1) << " was " << D[i] << " expecting " << door[i] << endl;
			exit(0);
		}
	}

	cout << "AC" << endl;

	exit(0);
}

//#include "cave.h"
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int S[6000], D[6000];
ordered_set pending;

void flip(int n, int start, int end){
	auto s = pending.find_by_order(start);
	for(int i = start; i <= end && s != pending.end(); ++i, ++s){
		if(0 <= *s && *s < n){
			S[*s] ^= 1;
		}
	}
}

int intenta(int n, int arr[]){
	int idx = tryCombination(n, arr);
	if(idx == -1) idx = n;
	return idx;
}

void exploreCave(int n) {
	int cnt = 0;
	fill(S, S + n, 0);
	fill(D, D + n, 0);
	pending.clear();
	for(int i = 0; i < n; ++i) pending.insert(i);

	while(cnt < n){
		int l = 0, r = (int)pending.size()-1, m;
		flip(n, l, r);
		int prev = intenta(n, S);
		do{
			if(l == r){
				auto s = pending.find_by_order(l);
				if(s != pending.end() && 0 <= *s && *s < n){
					int idx = *s;
					if(intenta(n, S) == cnt) S[idx] ^= 1;
					D[idx] = cnt;
					pending.erase(idx);
				}
				break;
			}
			m = (l + r) / 2;
			flip(n, m + 1, r);
			int curr = intenta(n, S);
			if((cnt < prev) ^ (cnt < curr)){
				l = m + 1;
				prev = curr;
			}else{
				r = m;
			}
		}while(true);
		++cnt;
	}
	
	answer(n, S, D);
}

int main(int argc, char* argv[]) {
	/*ios_base::sync_with_stdio(0);
	cin.tie(0);*/

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> down[i];
	}
	for (int i = 0; i < N; i++) {
		int idx;
		cin >> idx;
		door[idx] = i;
	}

	exploreCave(N);

	cout << "WA - Did not call answer()" << endl;
	return 0;
}
