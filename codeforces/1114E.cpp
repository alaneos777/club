#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> test = {14, 24, 9, 19};
vector<int> sorted = {9, 14, 19, 24};

int ask(char c, int x){
	int r;
	cout << c << " " << x << endl;
	cin >> r;
	return r;
	/*if(c == '>'){
		auto pos = upper_bound(sorted.begin(), sorted.end(), x);
		return pos != sorted.end();
	}else{
		return test[x-1];
	}*/
}

void answer(int x1, int d){
	cout << "! " << x1 << " " << d << endl;
	exit(0);
}

int main(){
	srand(time(0));
	int n;
	cin >> n;
	int l = 0, r = 1e9, xn;
	int q = 0;
	while(true){
		if(l == r){
			xn = l;
			break;
		}
		int m = (l + r) / 2;
		q++;
		if(ask('>', m)){
			l = m + 1;
		}else{
			r = m;
		}
	}
	vector<int> positions(n);
	for(int i = 1; i <= n; ++i){
		positions[i-1] = i;
	}
	vector<int> values;
	random_shuffle(positions.begin(), positions.end(), [](int i){return ((rand() << 15) + rand()) % i;});
	for(int i = 0; i < n && i < 60-q; ++i){
		values.push_back(ask('?', positions[i]));
	}
	int d = 0;
	sort(values.begin(), values.end());
	for(int i = 0; i < (int)values.size()-1; ++i){
		d = __gcd(d, abs(values[i] - values[i+1]));
	}
	answer(xn - (n-1)*d, d);
	return 0;
}