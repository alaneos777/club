#include <iostream>
#include <map>
using namespace std;

int gcd(int a, int b){
	int r;
	while(b != 0){
		r = a % b, a = b, b = r;
	}
	return a;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, d, k, pos;
	cin >> n >> d >> k;
	int step = gcd(n, d);
	int maximo = 0, start = 0;
	map<int, int> info;
	while(k--){
		cin >> pos;
		info[pos % step]++;
	}
	for(pair<const int, int> & p : info){
		if(p.second > maximo){
			maximo = p.second;
			start = p.first;
		}
	}
	cout << maximo << " " << start << "\n";
	return 0;
}