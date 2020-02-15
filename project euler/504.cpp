#include <bits/stdc++.h>
using namespace std;

const int M = 100;

int main(){
	int ans = 0;
	set<int> sqs;
	for(int i = 1; i*i <= 2*M*M + 1; ++i){
		sqs.insert(2*i*i);
	}
	for(int a = 1; a <= M; ++a){
		for(int b = 1; b <= M; ++b){
			for(int c = 1; c <= M; ++c){
				for(int d = 1; d <= M; ++d){
					int sq = (a+c)*(b+d) + 2 - __gcd(a,b) - __gcd(b,c) - __gcd(c,d) - __gcd(d,a);
					if(sqs.count(sq)) ans++;
				}
			}
		}
	}
	cout << ans << "\n";
	return 0;
}