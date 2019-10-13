#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ull = unsigned long long int;
using uint = unsigned int;

struct u128{
	ull hi;
	ull lo;
	u128(ull h, ull l): hi(h), lo(l) {}
	u128(ull l): hi(0), lo(l) {}
	u128(lli l): hi(0), lo(l){
		if(l < 0) hi = -1;
	}
	u128(int l): hi(0), lo(l){
		if(l < 0) hi = -1;
	}
	u128(): hi(0), lo(0) {}

	u128 operator<<(size_t cnt) const{
		if(cnt >= 128) return u128(0, 0);
		u128 ans(hi, lo);
		if(cnt >= 64){
			ans.hi = ans.lo;
			ans.lo = 0;
			cnt -= 64;
		}
		ans.hi = (ans.hi << cnt) | (ans.lo >> (64 - cnt));
		ans.lo = (ans.lo << cnt);
		return ans;
	}

	u128 operator>>(size_t cnt) const{
		if(cnt >= 128) return u128(0, 0);
		u128 ans(hi, lo);
		if(cnt >= 64){
			ans.lo = ans.hi;
			ans.hi = 0;
		}
		ans.lo = (ans.hi << (64 - cnt)) | (ans.lo >> cnt);
		ans.hi = (ans.hi >> cnt);
		return ans;
	}

	u128 operator+(const u128 & rhs) const{
		return u128(hi + rhs.hi + ((lo + rhs.lo) < lo), lo + rhs.lo);
	}

	u128 operator-(const u128 & rhs) const{
		return u128(hi - rhs.hi - ((lo - rhs.lo) > lo), lo - rhs.lo);
	}

	u128 operator*(const u128 & rhs) const{
		ull m = 0xFFFFFFFF;
		ull top[4] = {hi >> 32, hi & m, lo >> 32, lo & m};
		ull bottom[4] = {rhs.hi >> 32, rhs.hi & m, rhs.lo >> 32, rhs.lo & m};
		ull prods[4][4];
		ull res[4];

		for(int i = 3; i >= 0; --i)
			for(int j = 3; j >= 0; --j)
				prods[3 - i][j] = top[i] * bottom[j];

		res[3] = (prods[0][3] & m);
		res[2] = (prods[0][2] & m) + (prods[0][3] >> 32);
		res[1] = (prods[0][1] & m) + (prods[0][2] >> 32);
		res[0] = (prods[0][0] & m) + (prods[0][1] >> 32);

		res[2] += (prods[1][3] & m);
		res[1] += (prods[1][2] & m) + (prods[1][3] >> 32);
		res[0] += (prods[1][1] & m) + (prods[1][2] >> 32);

		res[1] += (prods[2][3] & m);
		res[0] += (prods[2][2] & m) + (prods[2][3] >> 32);

		res[0] += (prods[3][3] & m);

		res[2] += (res[3] >> 32);
		res[1] += (res[2] >> 32);
		res[0] += (res[1] >> 32);

		res[3] &= m;
		res[2] &= m;
		res[1] &= m;
		res[0] &= m;

		return u128((res[0] << 32) | res[1], (res[2] << 32) | res[3]);
	}

	u128 operator+=(const u128 & rhs){
		*this = *this + rhs;
		return *this;
	}

	u128 operator-=(const u128 & rhs){
		*this = *this - rhs;
		return *this;
	}

	u128 operator-() const{
		return u128(0) - *this;
	}

	u128 operator*=(const u128 & rhs){
		*this = *this * rhs;
		return *this;
	}

	u128 operator<<=(size_t rhs){
		*this = *this << rhs;
		return *this;
	}

	u128 operator>>=(size_t rhs){
		*this = *this >> rhs;
		return *this;
	}

	bool operator==(const u128 & rhs) const{
		return lo == rhs.lo && hi == rhs.hi;
	}

	bool operator!=(const u128 & rhs) const{
		return lo != rhs.lo || hi != rhs.hi;
	}
};

ostream & operator<<(ostream & os, u128 val){
	unsigned char digits[64] = {0};
	bool neg = false;
	if(val.hi >> 63){
		val = -val;
		neg = true;
	}
	for(int i = 0; i < 128; ++i){
		for(int j = 0; j < 64; ++j){
			if(digits[j] >= 5) digits[j] += 3;
		}
		for(int j = 63; j >= 0; --j){
			digits[j] = (digits[j] << 1) & 15;
			if(j) digits[j] |= (digits[j-1] >> 3);
			else digits[j] |= (val.hi >> 63);
		}
		val = (val << 1);
	}
	char buf[64];
	char* pos = begin(buf);
	int start = 63;
	while(start >= 0){
		if(digits[start] != 0) break;
		start--;
	}
	if(start == -1){
		*pos = '0';
		++pos;
	}else{
		if(neg){
			*pos = '-';
			++pos;
		}
		for(int i = start; i >= 0; --i){
			*pos = digits[i] + '0';
			++pos;
		}
	}
	*pos = '\0';
	return os << buf;
}

istream & operator>>(istream & is, u128 & value){
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

template<typename T>
struct SegmentTreeDin{
	SegmentTreeDin *left, *right;
	int l, r;
	T sum, lazy;
 
	SegmentTreeDin(int start, int end): left(NULL), right(NULL), l(start), r(end), sum(0), lazy(0){
		if(l != r){
			int half = l + ((r - l) >> 1);
			left = new SegmentTreeDin(l, half);
			right = new SegmentTreeDin(half+1, r);
		}
	}
 
	void propagate(T dif){
		sum += dif * (r - l + 1);
		if(l != r){
			left->lazy += dif;
			right->lazy += dif;
		}
	}
 
	T sum_query(int start, int end){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum;
		else return left->sum_query(start, end) + right->sum_query(start, end);
	}
 
	void add_range(int start, int end, T dif){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(dif);
		else{
			left->add_range(start, end, dif);
			right->add_range(start, end, dif);
			sum = left->sum + right->sum;
		}
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q; lli x;
	cin >> n >> x >> q;
	SegmentTreeDin<u128> st(0, n-1);
	while(q--){
		int t, l, r; lli k;
		cin >> t >> l >> r;
		--l, --r;
		if(t == 1){
			cin >> k;
			st.add_range(l, r, k);
		}else if(t == 2){
			cout << st.sum_query(l, r)*x << "\n";
		}
	}
	return 0;
}