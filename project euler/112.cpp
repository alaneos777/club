#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool bouncy(int n){
	deque<int> digits;
	do{
		int d = n % 10;
		digits.push_front(d);
		n /= 10;
	}while(n);
	bool inc = true, dec = true;
	for(int i = 0; i < (int)digits.size()-1; ++i){
		inc = inc & (digits[i] <= digits[i+1]);
		dec = dec & (digits[i] >= digits[i+1]);
	}
	return !inc && !dec;
}

int main(){
	lli cnt = 0, total = 0;
	int n = 1;
	do{
		cnt += bouncy(n);
		total++;
		n++;
	}while(100*cnt != 99*total);
	cout << n-1 << "\n";
	return 0;
}