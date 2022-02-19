#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

/*struct point{
	int x, y;
	point(): x(0), y(0){}
	point(int x, int y): x(x), y(y){}
	point north() const{return {x, y-1};}
	point south() const{return {x, y+1};}
	point northeast() const{
		if(x&1) return {x+1, y-1};
		else return {x+1, y};
	}
	point southeast() const{
		if(x&1) return {x+1, y};
		else return {x+1, y+1};
	}
	point northwest() const{
		if(x&1) return {x-1, y-1};
		else return {x-1, y};
	}
	point southwest() const{
		if(x&1) return {x-1, y};
		else return {x-1, y+1};
	}
	point move(int dir) const{
		if(dir == 0) return southwest();
		if(dir == 1) return south();
		if(dir == 2) return southeast();
		if(dir == 3) return northeast();
		if(dir == 4) return north();
		if(dir == 5) return northwest();
		return *this;
	}
	bool operator<(const point& p) const{
		return x < p.x || (x == p.x && y < p.y);
	}
};*/

/*int f(int l, int d, int i){
	if(l == 0) return 1;
	if(i == -1){
		i = l-1;
		d = (d+5)%6;
	}else if(i == l){
		i = 0;
		d = (d+1)%6;
	}
	return 3*l*l - 3*l + 2 + l*d + i;
}

auto move(int l, int d, int i){
	vector<int> dest(6);
	dest[0] = f(l, d, i-1);
	dest[1] = f(l, d, i+1);
	if(i == 0){
		dest[2] = f(l+1, (d+5)%6, l);
	}else{
		dest[2] = f(l-1, d, i-1);
	}
	dest[3] = f(l-1, d, i);
	dest[4] = f(l+1, d, i);
	dest[5] = f(l+1, d, i+1);
	return dest;
}*/

auto isSieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return is;
}

const int M = 1e6;
const auto isPrime = isSieve(M);

int main(){
	int target = 2000;
	int cnt = 2;
	for(lli l = 2; 12*l+5 <= M; ++l){
		if(isPrime[6*l-1] && isPrime[12*l+5] && isPrime[6*l+1]){
			cnt++;
			if(cnt == target){
				cout << 3*l*l - 3*l + 2 << "\n";
				break;
			}
		}
		if(isPrime[6*l-1] && isPrime[12*l-7] && isPrime[6*l+5]){
			cnt++;
			if(cnt == target){
				cout << 3*l*l + 3*l + 1 << "\n";
				break;
			}
		}
	}
	/*int cnt = 1;
	for(int l = 1; f(l+1, 0, 0) <= M; ++l){
		for(int d : {0, 5}){
			int i = (d == 0 ? 0 : l-1);
			int m = f(l, d, i);
			int pd = 0;
			for(int n : move(l, d, i)){
				pd += isPrime[abs(n - m)];
			}
			if(pd == 3){
				cnt++;
				cout << cnt << ": " << m << " " << l << " " << d << " " << i << "\n";
			}
		}
	}
	cout << cnt << "\n";*/
	/*map<point, int> mp;
	vector<point> mp_inv(M+1);
	int n = 1;
	point curr(0, 0);
	mp[curr] = n;
	mp_inv[n] = curr;
	n++;
	for(int layer = 1; n <= M; ++layer){
		curr = curr.north();
		for(int dir = 0; dir < 6 && n <= M; ++dir){
			for(int i = 1; i <= layer && n <= M; ++i){
				mp[curr] = n;
				mp_inv[n] = curr;
				n++;
				curr = curr.move(dir);
			}
		}
	}
	auto pd = [&](int n){
		int cnt = 0;
		for(int dir = 0; dir < 6; ++dir){
			cnt += isPrime[abs(n - mp[mp_inv[n].move(dir)])];
		}
		return cnt;
	};
	int cnt = 0;
	for(int n = 1; n <= M; ++n){
		if(pd(n) == 3){
			cnt++;
			if(cnt == 2000){
				cout << n << "\n";
				break;
			}
		}
	}
	cout << "!" << cnt << "\n";*/
	return 0;
}