#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

//cout for __int128
ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

//cin for __int128
istream &operator>>(istream &is, __int128 & value){
	char buffer[64];
	is >> buffer;
	char *pos = begin(buffer);
	int sgn = 1;
	value = 0;
	if(*pos == '-'){
		sgn = -1;
		++pos;
	}else if(*pos == '+'){
		++pos;
	}
	while(*pos != '\0'){
		value = (value << 3) + (value << 1) + (*pos - '0');
		++pos;
	}
	value *= sgn;
	return is;
}

inline lli gauss(lli n){
	return (n * (n + 1)) >> 1;
}

lli floorSqrt(lli n){
	lli l = 0, r = 1ll << 35, ans = -1;
	while(l <= r){
		lli x = (l + r) >> 1;
		if(x*x <= n){
			ans = x;
			l = x+1;
		}else{
			r = x-1;
		}
	}
	return ans;
}

lli ceilSqrt(lli n){
	lli x = floorSqrt(n);
	if(x*x == n) return x;
	else return x+1;
}

lli floorCbrt(lli n){
	lli l = 0, r = 1e9, ans = -1;
	while(l <= r){
		lli x = (l + r) >> 1;
		if(x*x*x <= n){
			ans = x;
			l = x+1;
		}else{
			r = x-1;
		}
	}
	return ans;
}

lli ceilCbrt(lli n){
	lli x = floorCbrt(n);
	if(x*x*x == n) return x;
	else return x+1;
}

lli SR(lli w, lli h, lli a1, lli b1, lli c1, lli a2, lli b2, lli c2, lli n, lli C1, lli C2){
	lli a3 = a1 + a2, b3 = b1 + b2, u4, v4, u5, v5, u6, v6, u7;
	auto H = [&](lli u, lli v){
		return (b2 * (u + c1) - b1 * (v + c2)) * (a1 * (v + c2) - a2 * (u + c1));
	};
	auto Utan = [&](){
		lli num = a1*b2 + b1*a2 + 2*a1*b1;
		return floorSqrt(num * num * n / (a3 * b3)) - c1;
	};
	auto Vfloor = [&](lli u){
		return ((a1*b2 + b1*a2) * (u + c1) - ceilSqrt((u + c1) * (u + c1) - 4*a1*b1*n)) / (2*a1*b1) - c2;
	};
	auto Ufloor = [&](lli v){
		return ((a1*b2 + b1*a2) * (v + c2) - ceilSqrt((v + c2) * (v + c2) - 4*a2*b2*n)) / (2*a2*b2) - c1;
	};
	auto SW = [&](){
		lli sum = 0;
		for(lli u = 1; u <= w; ++u){
			sum += Vfloor(u);
		}
		return sum;
	};
	auto SH = [&](){
		lli sum = 0;
		for(lli v = 1; v <= h; ++v){
			sum += Ufloor(v);
		}
		return sum;
	};
	auto SN = [&](){
		return gauss(v6 - 1) - gauss(v6 - u5) + gauss(u7 - u5);
	};
	lli s = 0;
	if(h > 0 && H(w, 1) <= n){
		s += w;
		c2++;
		h--;
	}
	if(w > 0 && H(1, h) <= n){
		s += h;
		c1++;
		w--;
	}
	if(w <= C2){
		return s + SW();
	}
	if(h <= C2){
		return s + SH();
	}
	u4 = Utan(), v4 = Vfloor(u4), u5 = u4 + 1, v5 = Vfloor(u5);
	v6 = u4 + v4, u7 = u6 + v6;
	s += SN();
	s += SR(u4, h - v6, a1, b1, c1, a3, b3, c1 + c2 + v6, n, C1, C2);
	s += SR(w - u7, v5, a3, b3, c1 + c2 + u7, a2, b2, c2, n, C1, C2);
	return s;
}

lli F(lli n){
	lli C1 = 10, C2 = 10;
	lli xmax = floorSqrt(n), ymin = n / xmax, xmin = min(xmax, C1 * ceilCbrt(n * 2));
	lli s = 0, a1, a2 = 1, x2 = xmax, y2 = ymin, c2 = a2*x2 + y2, c4, c5, x4, y4, x5, y5;
	auto S1 = [&](){
		lli sum = 0;
		for(lli x = 1; x < xmin; ++x){
			sum += n / x;
		}
		return sum;
	};
	auto S2 = [&](){
		return (xmax - xmin + 1) * ymin + gauss(xmax - xmin);
	};
	auto S3 = [&](){
		lli sum = 0;
		for(lli x = xmin; x < x2; ++x){
			sum += n / x - (a2 * (x2 - x) + y2);
		}
		return sum;
	};
	auto SM = [&](){
		return gauss(c4 - c2 - xmin) - gauss(c4 - c2 - x5) + gauss(c5 - c2 - x5);
	};
	while(true){
		a1 = a2 + 1;
		x4 = floorSqrt(n / a1);
		if(x4 < xmin) break;
		y4 = n / x4, c4 = a1*x4 + y4;
		x5 = x4 + 1, y5 = n / x5, c5 = a1*x5 + y5;
		s += SM() + SR(a1*x2 + y2 - c5, a2*x5 + y5 - c2, a1, 1, c5, a2, 1, c2, n, C1, C2);
		a2 = a1, x2 = x4, y2 = y4, c2 = c4;
	}
	s += S1() + S2() + S3();
	return 2*s - xmax*xmax;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		cout << F(n) << "\n";
	}
	return 0;
}