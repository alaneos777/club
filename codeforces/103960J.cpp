#include <bits/stdc++.h>
using namespace std;

int val(int n){
	return min(10, n);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	multiset<int> cards;
	for(int i = 1; i <= 13; ++i){
		for(int j = 1; j <= 4; ++j){
			cards.insert(i);
		}
	}
	int n;
	cin >> n;
	int j1, j2, m1, m2;
	cin >> j1 >> j2 >> m1 >> m2;
	int j = val(j1) + val(j2);
	int m = val(m1) + val(m2);
	cards.erase(cards.find(j1));
	cards.erase(cards.find(j2));
	cards.erase(cards.find(m1));
	cards.erase(cards.find(m2));
	for(int i = 1; i <= n; ++i){
		int c;
		cin >> c;
		j += val(c);
		m += val(c);
		cards.erase(cards.find(c));
	}
	int ans = -1;
	for(int x : cards){
		if((j+val(x) > 23 && m+val(x) <= 23) || m+val(x) == 23){
			ans = x;
			break;
		}
	}
	cout << ans << "\n";
	return 0;
}