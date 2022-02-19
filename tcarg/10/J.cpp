#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, d; lli x;
	cin >> n >> d >> x;
	int magic = 35;
	auto next = [&](){
		x = (x * 37 + 10007) % 1000000007;
		return x;
	};
	vector<int> a(n), b(n), where(n+1), indices;
	for(int i = 0; i < n; ++i){
		a[i] = i+1;
	}
	for(int i = 0; i < n; ++i){
		swap(a[i], a[next()%(i+1)]);
	}
	for(int i = 0; i < n; ++i){
		b[i] = i<d;
	}
	for(int i = 0; i < n; ++i){
		swap(b[i], b[next()%(i+1)]);
	}
	for(int i = 0; i < n; ++i){
		where[a[i]] = i;
		if(b[i]) indices.push_back(i);
	}
	for(int i = 0; i < n; ++i){
		int ci = 0;
		bool found = false;
		for(int j = n; j >= n-magic && j >= 1; --j){
			if(where[j] <= i && b[i - where[j]]){
				ci = j;
				found = true;
				break;
			}
		}
		if(!found){
			for(int j : indices){
				if(j > i) break;
				ci = max(ci, a[i-j]);
			}
		}
		cout << ci << "\n";
	}
	return 0;
}