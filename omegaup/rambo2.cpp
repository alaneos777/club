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
	int n, d, k, m, pos;
	cin >> n >> d >> k >> m;
	int step = gcd(n, d);
	int saltos = n / step;
	int maximo = 0, start = 0;
	map<int, int> info;
	while(k--){
		cin >> pos;
		info[pos % step]++;
	}
	for(pair<const int, int> & p : info){
		if(p.second > maximo && saltos <= m){
			maximo = p.second;
			start = p.first;
		}
	}
	cout << maximo << " " << start << "\n";
	return 0;
}