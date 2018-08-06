#include <bits/stdc++.h>
using namespace std;
typedef __int128 lli;

void gcd(lli a, lli b, lli & r, lli & s, lli & t){
	lli q, r0 = a, r1 = b, ri, s0 = 1, s1 = 0, si, t0 = 0, t1 = 1, ti;
	while(r1 != 0){
		q = r0 / r1;
		ri = r0 % r1, r0 = r1, r1 = ri;
		si = s0 - s1 * q, s0 = s1, s1 = si;
		ti = t0 - t1 * q, t0 = t1, t1 = ti;
	}
	r = r0, s = s0, t = t0;
}

ostream& operator<<( ostream& dest, __int128_t value ){
    ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( ios_base::badbit );
        }
    }
    return dest;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, caso = 1;
	long long int r_, ki_;
	lli r, ki, d;
	while(cin >> n >> r_ && !(n == 0 && r_ == 0)){
		r = r_;
		vector<lli> ans(n);
		d = 0;
		for(int i = 0; i < n; i++){
			cin >> ki_;
			ki = ki_;
			lli s, t;
			gcd(d, ki, d, s, t);
			for(int j = 0; j < i; j++){
				ans[j] *= s;
			}
			ans[i] = t;
		}
		cout << "Case #" << caso << ": ";
		if(r % d == 0){
			lli q = r / d;
			for(int i = 0; i < n; i++){
				if(i > 0) cout << " ";
				cout << (q * ans[i]);
			}
			cout << "\n";
		}else{
			cout << "Stupid keypad!\n";
		}
		++caso;
	}
	return 0;
}