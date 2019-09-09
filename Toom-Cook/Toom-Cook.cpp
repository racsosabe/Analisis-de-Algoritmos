#include<bits/stdc++.h>
using namespace::std;

const int k = 3;

void print(vector<int> &a){
	for(int i=a.size()-1; i>=0; i--) printf("%d",a[i]);
	putchar('\n');
}

void fix(vector<int> &a){
	int carry = 0;
	int len = a.size();
	for(int i=0; i<len; i++){
		a[i] += carry;
		if(a[i] < 0){
			int c = i + 1 < len? -(-a[i] + 9) / 10 : 0;
			carry = c;
		}
		else if(a[i] >= 10){
			carry = a[i] / 10;
		}
		else carry = 0;
		a[i] -= carry * 10;
	}
	if(carry < 0) a.emplace_back(carry);
	while(carry > 0){
		a.emplace_back(carry % 10);
		carry /= 10;
	}
	for(int i=0; i<a.size(); i++){
		if(a[i] >= 10){
			if(i + 1 < a.size()) a[i+1] += a[i] / 10;
			else a.emplace_back(a[i] / 10);
			a[i] %= 10;
		}
	}
	len = a.size();
	while(len > 1 and a[len-1] == 0) len -= 1;
	a.resize(len);
}

vector<int> get(vector<int> &a, int L, int R){
	vector<int> ans;
	for(int i=L; i<R; i++){
		if(i < a.size()) ans.emplace_back(a[i]);
	}
	ans.emplace_back(0);
	fix(ans);
	return ans;
}

vector<int> add(vector<int> a, vector<int> b, int sign = 1){
	vector<int> ans(a.begin(),a.end());
	for(int i=0; i<b.size(); i++){
		if(i < ans.size()) ans[i] += sign * b[i];
		else ans.emplace_back(sign * b[i]);
	}
	fix(ans);
	return ans;
}
vector<int> multiplyNormal(vector<int> &a, vector<int> &b){
	vector<int> ans(a.size() + b.size(),0);
	for(int i=0; i<a.size(); i++){
		for(int j=0; j<b.size(); j++){
			ans[i+j] += a[i] * b[j];
		}
	}
	fix(ans);
	return ans;
}

vector<int> scalarMultiplication(vector<int> a, int val){
	vector<int> b;
	while(val > 0){
		b.emplace_back(val % 10);
		val /= 10;
	}
	a = multiplyNormal(a,b);
	fix(a);
	return a;
}

vector<int> scalarDivision(vector<int> a, int val){
	int rem = 0;
	fix(a);
	for(int i=a.size()-1; i>=0; i--){
		rem = ((10 * rem + a[i]) % val + val) % val;
	}
	if(rem){
		puts("ERROR, not exact division");
		assert(rem == 0);
	}
	int carry = 0;
	vector<int> ans;
	for(int i=a.size()-1; i>=0; i--){
		carry = 10 * carry + a[i];
		int c;
		c = carry / val;
		carry -= c * val;
		ans.emplace_back(c);
	}
	reverse(ans.begin(),ans.end());
	fix(ans);
	return ans;
}


void getEvaluationPoints(vector<int> &m0, vector<int> &m1, vector<int> &m2, vector<int> &p0, vector<int> &p1, vector<int> &pm1, vector<int> &pm2, vector<int> &pi){
	vector<int> P0 = add(m0,m2,1);
	p0 = m0;
	p1 = add(P0,m1,1);
	pm1 = add(P0,m1,-1);
	pm2 = add(scalarMultiplication(add(pm1,m2),2),m0,-1);
	pi = m2;
}

void shift(vector<int> &a, int L){
	vector<int> ans;
	for(int i=0; i<L; i++) ans.emplace_back(0);
	for(int i=0; i<a.size(); i++) ans.emplace_back(a[i]);
	a = ans;
}

vector<int> multiplyTC3(vector<int> &a, vector<int> &b){
	int lenA = a.size();
	int lenB = b.size();
	if(max(lenA,lenB) <= 100){
		return multiplyNormal(a,b);
	}
	int len = max(lenA / k, lenB / k) + 1;
	vector<int> m0 = get(a,0,len);
	vector<int> m1 = get(a,len,len+len);
	vector<int> m2 = get(a,len+len,len+len+len);
	vector<int> p0, p1, pm1, pm2, pi;
	getEvaluationPoints(m0,m1,m2,p0,p1,pm1,pm2,pi);
	vector<int> n0 = get(b,0,len);
	vector<int> n1 = get(b,len,len+len);
	vector<int> n2 = get(b,len+len,len+len+len);
	vector<int> q0, q1, qm1, qm2, qi;
	getEvaluationPoints(n0,n1,n2,q0,q1,qm1,qm2,qi);
	vector<int> r0 = multiplyTC3(p0,q0);
	vector<int> r1 = multiplyTC3(p1,q1);
	vector<int> rm1 = multiplyTC3(pm1,qm1);
	vector<int> rm2 = multiplyTC3(pm2,qm2);
	vector<int> ri = multiplyTC3(pi,qi);
	vector<int> R0 = r0;
	vector<int> R4 = ri;
	vector<int> R3 = scalarDivision(add(rm2,r1,-1),3);
	vector<int> R1 = scalarDivision(add(r1,rm1,-1),2);
	vector<int> R2 = add(rm1,r0,-1);
	R3 = add(scalarDivision(add(R2,R3,-1),2),scalarMultiplication(ri,2));
	R2 = add(R2,add(R1,R4,-1));
	R1 = add(R1,R3,-1);
	shift(R1,len);
	shift(R2,len+len);
	shift(R3,len+len+len);
	shift(R4,len+len+len+len);
	vector<int> ans = add(R0,add(R1,add(R2,add(R3,R4))));
	fix(ans);
	return ans;
}

void getVector(vector<int> &v, string &s){
	for(int i=s.size() - 1; i >= 0; i--){
		v.emplace_back(s[i] - '0');
	}
}

int checkNegative(string &s){
	int ans = 0;
	if(s[0] == '-'){
		ans += 1;
		s = s.substr(1);
		while(s.size() and s[0] == '0') s = s.substr(1);
		if(s == "0") ans -= 1;
	}
	return ans;
}

int main(){
	string a, b;
	int t;
	cin >> t;
	while(t--){
		cin >> a >> b;
		int neg = 0;
		vector<int> A;
		vector<int> B;
		neg += checkNegative(a);
		neg += checkNegative(b);
		getVector(A,a);
		getVector(B,b);
		vector<int> C = multiplyTC3(A,B);
		if(neg&1){
			putchar('-');
		}
		print(C);
	}
	return 0;
}
