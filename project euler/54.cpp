#include <bits/stdc++.h>
using namespace std;

struct card{
	int number;
	char type;

	bool operator<(const card & c) const{
		if(number == c.number) return type < c.type;
		return number < c.number;
	}
};

struct condition{
	int id;
	bool value;
	int rank;
};

condition check(const vector<card> & hand){
	vector<condition> conditions(10);
	vector<int> freq(15);
	for(auto & c : hand){
		freq[c.number]++;
	}

	conditions[0] = {0, true, hand.back().number}; //high card

	bool test = false;
	int M = 0;
	for(int i = 0; i < 15; ++i){
		if(freq[i] == 2){
			test = true;
			M = max(M, i);
		}
	}
	conditions[1] = {1, test, M}; //one pair

	test = false;
	int cnt = 0;
	M = 0;
	for(int i = 0; i < 15; ++i){
		if(freq[i] == 2){
			cnt++;
			M = max(M, i);
		}
	}
	conditions[2] = {2, cnt == 2, cnt == 2 ? M : 0}; //two pairs

	test = false;
	M = 0;
	for(int i = 0; i < 15; ++i){
		if(freq[i] == 3){
			test = true;
			M = max(M, i);
		}
	}
	conditions[3] = {3, test, M}; //three of a kind

	test = true;
	for(int i = 1; i < hand.size(); ++i){
		test = test & (hand[i].number - hand[i-1].number == 1);
	}
	conditions[4] = {4, test, test ? hand.back().number : 0}; //straight?

	test = true;
	for(int i = 1; i < hand.size(); ++i){
		test = test & (hand[i-1].type == hand[i].type);
	}
	conditions[5] = {5, test, test ? hand.back().number : 0}; //flush?

	int cnt2 = 0, cnt3 = 0;
	M = 0;
	for(int i = 0; i < 15; ++i){
		if(freq[i] == 3){
			cnt3++;
			M = max(M, i);
		}
		if(freq[i] == 2){
			cnt2++;
		}
	}
	conditions[6] = {6, cnt2 == 1 && cnt3 == 1, (cnt2 == 1 && cnt3 == 1) ? M : 0}; //full house

	test = false;
	M = 0;
	for(int i = 0; i < 15; ++i){
		if(freq[i] == 4){
			test = true;
			M = max(M, i);
		}
	}
	conditions[7] = {7, test, test ? M : 0}; //four of a kind

	test = true;
	for(int i = 1; i < hand.size(); ++i){
		test = test & (hand[i].number - hand[i-1].number == 1) & (hand[i-1].type == hand[i].type);
	}
	conditions[8] = {8, test, test ? hand.back().number : 0}; //straight flush?

	test = (freq[10] == 1 && freq[11] == 1 && freq[12] == 1 && freq[13] == 1 && freq[14] == 1);
	conditions[9] = {9, test, test ? 14 : 0};

	for(int i = 9; i >= 0; --i){
		if(conditions[i].value){
			return conditions[i];
		}
	}
}

int main(){
	int ans = 0;
	ifstream in("p054_poker.txt");
	string game;
	while(getline(in, game)){
		stringstream ss(game);
		vector<card> hand[2];
		for(int h = 0; h < 2; ++h){
			hand[h].resize(5);
			for(int i = 0; i < 5; ++i){
				char n, c;
				ss >> n >> c;
				int number;
				if('2' <= n && n <= '9'){
					hand[h][i].number = n-'0';
				}else if(n == 'T'){
					hand[h][i].number = 10;
				}else if(n == 'J'){
					hand[h][i].number = 11;
				}else if(n == 'Q'){
					hand[h][i].number = 12;
				}else if(n == 'K'){
					hand[h][i].number = 13;
				}else if(n == 'A'){
					hand[h][i].number = 14;
				}
				hand[h][i].type = c;
			}
			sort(hand[h].begin(), hand[h].end());
		}
		int winner = -1;
		condition c1 = check(hand[0]);
		condition c2 = check(hand[1]);
		if(c1.id > c2.id){
			winner = 1;
		}else if(c2.id > c1.id){
			winner = 2;
		}else{
			if(c1.rank > c2.rank){
				winner = 1;
			}else if(c2.rank > c1.rank){
				winner = 2;
			}else{
				int M1 = 0, M2 = 0;
				for(card card1 : hand[0]){
					if(card1.number != c1.rank){
						M1 = max(M1, card1.number);
					}
				}
				for(card card2 : hand[1]){
					if(card2.number != c2.rank){
						M2 = max(M2, card2.number);
					}
				}
				if(M1 > M2){
					winner = 1;
				}else if(M2 > M1){
					winner = 2;
				}
			}
		}
		assert(winner != -1);
		ans += (winner == 1);
	}
	cout << ans << "\n";
	return 0;
}