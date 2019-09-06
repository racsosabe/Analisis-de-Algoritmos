#include<bits/stdc++.h>
using namespace::std;

class BigInteger{
	int len;
	vector<int> v;
	public:
	BigInteger(string s){
		len = s.size();
		for(int i=s.size()-1; i >= 0; i--){
			v.emplace_back(s[i] - '0');
		}
	}

	BigInteger(int L){
		len = L;
		v.resize(len);
		v.assign(len,0);
	}

	BigInteger(vector<int> a){
		v = a;
		len = v.size();
		fixLeadingZeroes();
	}

	~BigInteger(){
		v.clear();
		len = 0;
	}

	BigInteger operator + (BigInteger b){
		int new_len = max(len,b.len);
		vector<int> new_v(new_len,0);
		for(int i=0; i<new_len; i++){
			if(i < b.len) new_v[i] += b.v[i];
			if(i < len) new_v[i] += v[i];
		}
		for(int i=0; i<new_v.size(); i++){
			if(new_v[i] >= 10){
				if(i + 1 < new_v.size()){
					new_v[i+1] += new_v[i] / 10;
				}
				else new_v.emplace_back(new_v[i] / 10);
				new_v[i] %= 10;
			}
		}
		return BigInteger(new_v);
	}

	BigInteger operator = (BigInteger b){
		v = b.v;
		len = v.size();
	}

	friend ostream& operator << (ostream& o, BigInteger a){
		for(int i=a.len-1; i>=0; i--){
			o << a.v[i];
		}
		return o;
	}

	void makeEqual(int new_len){
		while(len < new_len){
			v.emplace_back(0);
			len += 1;
		}
	}

	int getValue(){
		int ans = 0;
		for(int i = 0; i < len; i++){
			ans |= v[i]<<i;
		}
		return ans;
	}

	int getLen(){ return len;}

	BigInteger operator - (BigInteger b){
		int alen = max(len,b.len);
		vector<int> a(alen,0);
		for(int i=0; i<alen; i++){
			if(i < len) a[i] += v[i];
			if(i < b.len) a[i] -= b.v[i];
		}
		for(int i=0; i<a.size(); i++){
			if(a[i] <= -10){
				int val = -a[i];
				int c = (val + 9) / 10;
				if(i + 1 < a.size()) a[i+1] -= c;
				else a.emplace_back(-c);
				a[i] -= (-c) * 10;
			}
			else if(a[i] >= 10){
				if(i + 1 < a.size()) a[i+1] += a[i] / 10;
				else a.emplace_back(a[i] / 10);
				a[i] %= 10;
			}
		}
		BigInteger ans(a);
		ans.fixLeadingZeroes();
		return ans;

	}

	BigInteger operator * (BigInteger b){
		if(b.isZero() or isZero()) return BigInteger("0");
		int alen = len + b.len;
		vector<int> a(alen,0);
		for(int i=0; i<len; i++){
			for(int j=0; j<b.len; j++){
				a[i+j] += v[i] * b.v[j];
			}
		}
		for(int i=0; i<a.size(); i++){
			if(a[i] >= 10){
				if(i + 1 < a.size()) a[i+1] += a[i] / 10;
				else a.emplace_back(a[i] / 10);
				a[i] %= 10;
			}
		}
		BigInteger ans(a);
		ans.fixLeadingZeroes();
		return ans;
	}

	BigInteger operator * (int val){
		assert(val > 0);
		vector<int> a;
		while(val > 0){
			a.emplace_back(val % 10);
			val /= 10;
		}
		BigInteger b(a);
		BigInteger c(v);
		BigInteger ans = b * c;
		ans.fix();
		return ans;
	}

	void set(int id, int val){
		assert(0 <= id and id < len);
		v[id] = val;
	}

	void add(int id, int val){
		assert(0 <= id and id < len);
		v[id] += val;
	}

	void divide(int val){ // I'm sure val < 10 :'v
		int rem = 0;
		for(int i=len-1; i >= 0; i--){
			rem = (10 * rem + v[i]) % val;
		}
		assert(rem == 0);
		vector<int> a(len,0);
		int pos = 0;
		int carry = 0;
		for(int i=len-1; i>=0; i--){
			int x = v[i] + carry;
			a[pos++] = x / val;
			carry = (x % val) * 10;
		}
		reverse(a.begin(),a.end());
		while(a.size() > 1 and a.back() == 0) a.pop_back();
		v = a;
		len = a.size();
		fix();
	}

	int get(int id){
		assert(0 <= id and id < len);
		return v[id];
	}

	void fix(){
		int carry = 0;
		for(int i=0; i<len; i++){
			v[i] += carry;
			if(v[i] < 0){
				int c = i + 1 < len? -(-v[i] + 9) / 10 : 0;
				carry = c;
			}
			else if(v[i] >= 10){
				carry = v[i] / 10;
			}
			v[i] -= carry * 10;
		}
		if(carry < 0) v.emplace_back(carry);
		while(carry > 0){
			v.emplace_back(carry % 10);
			carry /= 10;
		}

		for(int i=0; i<v.size(); i++){
			if(v[i] >= 10){
				if(i + 1 < v.size()) v[i+1] += v[i] / 10;
				else v.emplace_back(v[i] / 10);
				v[i] %= 10;
			}
		}
		len = v.size();
		fixLeadingZeroes();
	}

	void fixLeadingZeroes(){
		while(len > 1 and v.back() == 0){
			v.pop_back();
			len -= 1;
		}
	}

	bool isZero(){
		for(int i=0; i<len; i++){
			if(v[i] != 0) return false;
		}
		return true;
	}

	void shift(int pos){
		vector<int> a;
		for(int i=0; i<pos; i++) a.emplace_back(0);
		for(int i=0; i<len; i++) a.emplace_back(v[i]);
		v = a;
		len = v.size();
	}

	BigInteger getOrder(int L, int R){
		vector<int> a(v.begin() + L, v.begin() + R);
		return BigInteger(a);
	}
};

BigInteger multiplyToomCook3(BigInteger &A, BigInteger &B){
	int len = max(A.getLen(),B.getLen());
	int L = len / 3 + 1;
	if(len <= 9){
		return A * B;
	}
	BigInteger A0 = A.getOrder(0,L);
	BigInteger A1 = A.getOrder(L,L+L);
	BigInteger A2 = A.getOrder(L+L,len);
	BigInteger B0 = B.getOrder(0,L);
	BigInteger B1 = B.getOrder(L,L+L);
	BigInteger B2 = B.getOrder(L+L, len);
	cout << "A(x) = " << A2 << "x^2 + " << A1 << "x + " << A0 << endl;
	cout << "B(x) = " << B2 << "x^2 + " << B1 << "x + " << B0 << endl;

	BigInteger ap = A0 + A2;

	BigInteger a0 = A0;
	BigInteger a1 = ap + A1;
	BigInteger am1 = ap - A1;
	BigInteger am2 = (am1 + A2) * 2 - A0;
	BigInteger ai = A2;

	BigInteger bp = B0 + B2;

	BigInteger b0 = B0;
	BigInteger b1 = bp + B1;
	BigInteger bm1 = bp - B1;
	BigInteger bm2 = (bm1 + B2) * 2 - B0;
	BigInteger bi = B2;


	am2.fix(); am1.fix(); a0.fix(); a1.fix(); ai.fix();
	bm2.fix(); bm1.fix(); b0.fix(); b1.fix(); bi.fix();

	BigInteger cm2 = multiplyToomCook3(am2,bm2);
	BigInteger cm1 = multiplyToomCook3(am1,bm1);
	BigInteger c0 = multiplyToomCook3(a0,b0);
	BigInteger c1 = multiplyToomCook3(a1,b1);
	BigInteger ci = multiplyToomCook3(ai,bi);
	
//	cout << "a0 = " << ap << endl;
//	cout << "a(-2) = " << am2 << endl;
//	cout << "a(-1) = " << am1 << endl;
//	cout << "a(0) = " << a0 << endl;
//	cout << "a(1) = " << a1 << endl;
//	cout << "a(oo) = " << ai << endl;
//
//	cout << "b0 = " << bp << endl;
//	cout << "b(-2) = " << bm2 << endl;
//	cout << "b(-1) = " << bm1 << endl;
//	cout << "b(0) = " << b0 << endl;
//	cout << "b(1) = " << b1 << endl;
//	cout << "b(oo) = " << bi << endl;
//
//	cout << "c(0) = " << c0 << endl;
//	cout << "c(1) = " << c1 << endl;
//	cout << "c(-1) = " << cm1 << endl;
//	cout << "c(-2) = " << cm2 << endl;
//	cout << "c(oo) = " << ci << endl;
	
	cm2.fix(); cm1.fix(); c0.fix(); c1.fix(); ci.fix();

	BigInteger C4 = ci;
	BigInteger C0 = c0;
	BigInteger C3 = cm2 - c1;
	C3.fix(); C3.divide(3);
	BigInteger C1 = c1 - cm1;
	C1.fix(); C1.divide(2);
	BigInteger C2 = cm1 - c0;

	C3 = (C2 - C3) + C4 * 4;
	C3.fix(); C3.divide(2);

	C2 = C2 + C1 - C4;
	C1 = C1 - C3;

	C3.fix();
	C2.fix();
	C1.fix();

	C4.shift(L+L+L+L);
	C3.shift(L+L+L);
	C2.shift(L+L);
	C1.shift(L);

	BigInteger ans = C4 + C3 + C2 + C1 + C0;
	ans.fix();
	cout << "Product " << A << " x " << B << " = " << ans << endl;
	return ans;
}

int main(){
	string a, b;
	int t;
	cin >> t;
	while(t--){
		cin >> a >> b;
		BigInteger A(a);
		BigInteger B(b);
		auto start = chrono::steady_clock::now();
		int L = max(A.getLen(),B.getLen());
		BigInteger C = multiplyToomCook3(A,B);
		C.fixLeadingZeroes();
		auto end = chrono::steady_clock::now();
		cerr << "Tiempo de ejecucion: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " " << char(230) << "s" << endl;
		cout << C << endl;
	}
	return 0;
}
