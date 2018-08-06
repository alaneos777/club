#include <bits/stdc++.h>
using namespace std;

struct kmp{
	vector<int> aux;
	string pattern;

	kmp(const string & pattern){
		this->pattern = pattern;
		aux.resize(pattern.size());
		int i = 1, j = 0;
		while(i < pattern.size()){
			if(pattern[i] == pattern[j])
				aux[i++] = ++j;
			else{
				if(j == 0) aux[i++] = 0;
				else j = aux[j - 1];
			}
		}
	}

	vector<int> search(string & text){
		vector<int> ans;
		int i = 0, j = 0;
		while(i < text.size() && j < pattern.size()){
			if(text[i] == pattern[j]){
				++i, ++j;
				if(j == pattern.size()){
					ans.push_back(i - j);
					j = aux[j - 1];
				}
			}else{
				if(j == 0) ++i;
				else j = aux[j - 1];
			}
		}
		return ans;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, q, l, r;
	string s, t;
	cin >> n >> m >> q >> s >> t;
	kmp k(t);
	auto positions = k.search(s);
	sort(positions.begin(), positions.end());
	while(q--){
		cin >> l >> r;
		--l, --r;
		auto pos1 = lower_bound(positions.begin(), positions.end(), l);
		int pos2 = upper_bound(pos1, positions.end(), r - m + 1) - pos1;
		cout << pos2 << "\n";
	}
	return 0;
}