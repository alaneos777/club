#include <bits/stdc++.h>
using namespace std;

const int raiz[10] = {0, 1, -1, -1, 2, 5, 4, -1, -1, 3};

int inverse(int a, int m){
	int r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

pair<int, int> linear(int a, int b){
	if(a == 0 && b == 0){
		return {0, 1};
	}
	int g = __gcd(a, b);
	int m = 10;
	a /= g, b /= g, m /= __gcd(m, g);
	if(__gcd(a, m) != 1) return {-1, 1};
	return {inverse(a, m) * b % m, m};
}

string mult(string a){
	reverse(a.begin(), a.end());
	vector<int> b(2 * a.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < a.size(); ++j){
			b[i+j] = (b[i+j] + (a[i]-'0')*(a[j]-'0')) % 10;
		}
	}
	reverse(b.begin(), b.end());
	string ans;
	for(int x : b){
		ans += (x + '0');
	}
	return ans;
}

int64_t solve(string N){
	if(N[0] == '-'){
		return -1;
	}
	reverse(N.begin(), N.end());
	if(N == "0"){
		return 0;
	}
	int cnt_z = 0;
	while(N[0] == '0'){
		N = N.substr(1);
		cnt_z++;
	}
	if(cnt_z % 2 == 1){
		return -1;
	}
	cnt_z /= 2;
	int n = N.size() - 1;
	if(n % 2 == 1){
		return -1;
	}
	n /= 2;
	vector<int> a;
	for(char c : N){
		a.push_back(c - '0');
	}
	int r = raiz[a[0]];
	if(r == -1){
		return -1;
	}
	int64_t ans = -1;
	vector<int> b(2*n+1);
	b[0] = r;
	function<void(int)> f = [&](int i){
		if(i == 2*n+1){
			auto c = b;
			reverse(c.begin(), c.end());
			for(int i = 0; i < cnt_z; ++i){
				c.push_back(0);
			}
			int64_t resp = 0;
			for(int x : c){
				resp = resp * 10 + x;
			}
			if(ans == -1 || resp < ans){
				ans = resp;
			}
		}else{
			int num = a[i];
			for(int m = 1; m < i; ++m){
				num -= b[m] * b[i-m];
			}
			num %= 10;
			if(num < 0) num += 10;
			auto res = linear(2 * b[0] % 10, num);
			int curr = res.first;
			if(curr != -1){
				if(n+1 <= i && i <= 2*n){
					if(curr == 0){
						f(i + 1);
					}
				}else{
					while(curr < 10){
						b[i] = curr;
						f(i + 1);
						b[i] = 0;
						curr += res.second;
					}
				}
			}
		}
	};
	f(1);
	b[0] = 10 - r;
	f(1);
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string N;
	cin >> N;
	int64_t ans = solve(N);
	cout << ans << "\n";
	//cout << mult(to_string(ans)) << "\n";
	/*srand(time(0));
	for(int i = 1; i <= 100000; ++i){
		string r;
		int sz = rand() % 11 + 1;
		for(int j = 1; j <= sz; ++j){
			if(j == 1){
				r += ((rand() % 9 + 1) + '0');
			}else{
				r += (rand() % 10 + '0');
			}
		}
		cout << r << "\n";
		string sq = mult(r);
		cout << sq << "\n";
		int64_t r2 = solve(sq);
		cout << r2 << "\n\n";
		assert(mult(to_string(r2)) == sq);
	}*/
	return 0;
}