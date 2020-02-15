#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int aleatorio(int a, int b){
	uniform_int_distribution<int> dist(a, b);
	return dist(rng);
}

const int GO = 0;
const int JAIL = 10;
const int G2J = 30;
const int CC1 = 2;
const int CC2 = 17;
const int CC3 = 33;
const int CH1 = 7;
const int CH2 = 22;
const int CH3 = 36;

int main(){
	vector<int> cnt(40);
	int pos = GO;
	int dobles = 0;
	int M;
	cin >> M;
	for(int i = 0; i < M; ++i){
		int a = aleatorio(1, 4);
		int b = aleatorio(1, 4);
		if(a == b){
			dobles++;
			if(dobles == 3){
				dobles = 0;
				pos = JAIL;
				cnt[pos]++;
				continue;
			}
		}else{
			dobles = 0;
		}
		pos = (pos + a+b) % 40;
		if(pos == G2J){
			pos = JAIL;
			cnt[pos]++;
			continue;
		}
		if(pos == CC1 || pos == CC2 || pos == CC3){
			int c = aleatorio(1, 16);
			if(c == 1){
				pos = GO;
				cnt[pos]++;
				continue;
			}
			if(c == 2){
				pos = JAIL;
				cnt[pos]++;
				continue;
			}
			cnt[pos]++;
			continue;
		}
		if(pos == CH1 || pos == CH2 || pos == CH3){
			int c = aleatorio(1, 16);
			if(c == 1){
				pos = GO;
				cnt[pos]++;
				continue;
			}
			if(c == 2){
				pos = JAIL;
				cnt[pos]++;
				continue;
			}
			if(c == 3){
				pos = 11;
				cnt[pos]++;
				continue;
			}
			if(c == 4){
				pos = 24;
				cnt[pos]++;
				continue;
			}
			if(c == 5){
				pos = 39;
				cnt[pos]++;
				continue;
			}
			if(c == 6){
				pos = 5;
				cnt[pos]++;
				continue;
			}
			if(c == 7 || c == 8){
				if(pos == CH1) pos = 15;
				if(pos == CH2) pos = 25;
				if(pos == CH3) pos = 5;
				cnt[pos]++;
				continue;
			}
			if(c == 9){
				if(pos == CH1) pos = 12;
				if(pos == CH2) pos = 28;
				if(pos == CH3) pos = 12;
				cnt[pos]++;
				continue;
			}
			if(c == 10){
				pos = (pos + 37) % 40;
			}
		}
		cnt[pos]++;
	}
	vector<pair<double, int>> freq;
	for(int i = 0; i < 40; ++i){
		freq.emplace_back((double)cnt[i] / M * 100, i);
	}
	sort(freq.begin(), freq.end(), greater<pair<double, int>>());
	for(int i = 0; i < 40; ++i){
		cout << freq[i].second << " " << freq[i].first << "\n";
	}
	return 0;
}