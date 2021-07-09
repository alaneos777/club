#include <bits/stdc++.h>
using namespace std;

vector<int> manacher_odd(const string& s){
	int n = s.size();
	vector<int> odd(n);
	for(int i = 0, l = 0, r = -1; i < n; ++i){
		int k = (i > r ? 1 : min(odd[l+r-i], r-i+1));
		while(0 <= i-k && i+k < n && s[i-k] == s[i+k]) k++;
		odd[i] = k--;
		if(i+k > r){
			l = i-k;
			r = i+k;
		}
	}
	return odd;
}

vector<int> manacher_even(const string& s){
	int n = s.size();
	vector<int> even(n);
	for(int i = 0, l = 0, r = -1; i < n; ++i){
		int k = (i > r ? 0 : min(even[l+r-i+1], r-i+1));
		while(0 <= i-k-1 && i+k < n && s[i-k-1] == s[i+k]) k++;
		even[i] = k--;
		if(i+k > r){
			l = i-k-1;
			r = i+k;
		}
	}
	return even;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s;
	cin >> s;
	auto odd = manacher_odd(s), even = manacher_even(s);
	for(int i = 0; i < s.size(); ++i){
		cout << 2*odd[i]-1 << " ";
		if(i+1 < s.size()) cout << 2*even[i+1] << " ";
	}
	cout << "\n";
	return 0;
}