#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool isSq(lli n){
	lli r = sqrtl(n);
	return r*r == n;
}

lli check(const vector<string> & words){
	map<char, int> digit;
	for(const string & s : words){
		for(const char & c : s){
			digit[c] = 0;
		}
	}
	int n = 10, r = digit.size();
	lli ans = 0;
	vector<int> data(r);
	function<void(int, int)> comb = [&](int index, int i){
		if(index == r){
			do{
				int j = 0;
				for(auto & par : digit){
					par.second = data[j++];
				}
				bool test = true;
				vector<lli> tmp;
				for(const string & s : words){
					lli sq = 0;
					bool first = true;
					for(const char & c : s){
						if(first){
							if(digit[c] == 0){
								test = false;
							}
							first = false;
						}
						sq = sq * 10 + digit[c];
					}
					test = test & isSq(sq);
					tmp.push_back(sq);
				}
				if(test){
					for(lli m : tmp){
						ans = max(ans, m);
						cout << m << " ";
					}
					cout << "\n";
				}
			}while(next_permutation(data.begin(), data.end()));
			return;
		}
		if(i >= n) return;
		data[index] = i;
		comb(index + 1, i + 1);
		comb(index, i + 1);
	};
	comb(0, 0);
	return ans;
}

int main(){
	ifstream input("p098_words.txt");
	map<string, vector<string>> info;
	string str;
	int cnt = 0;
	while(input >> str){
		string tmp = str;
		sort(tmp.begin(), tmp.end());
		info[tmp].push_back(str);
		cnt++;
	}
	lli ans = 0;
	for(auto & par : info){
		if(par.first.size() > 10) continue;
		vector<string> & words = par.second;
		if(words.size() < 2) continue;
		ans = max(ans, check(words));
	}
	cout << ans << "\n";
	return 0;
}