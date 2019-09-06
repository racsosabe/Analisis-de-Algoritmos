#include<bits/stdc++.h>
//#define TEST      
#define D_MAX 100000
#define D     100000
using namespace std;
class Calc
{
    int A[D];  
    int B[D];
    public:
        Calc();                                         
        void calcToomCook();                                
    private:
        void multiplyNormal(int *, int *, int, int *);      
        void multiplyToomCook3(int *, int *, int , int *);  
        void doCarry(int *, int);                           
        void display(int *, int *, int *);          
};
Calc::Calc()
{
     int i;  
    for (i = 0; i < D; i++) 
    {
        A[i] = rand() % 10;
        B[i] = rand() % 10;
    }
}
void Calc::calcToomCook()
{
    int a[D_MAX];       
    int b[D_MAX];       
    int z[D_MAX * 2];
    int i;              
    string A;
    string B;
    cin >> A >> B;
    reverse(A.begin(),A.end());
    reverse(B.begin(),B.end());

        for (i = 0; i < D; i++)
    {
	if(i < A.size()) a[i] = A[i] - '0';
	else a[i] = 0;
	if(i < B.size()) b[i] = B[i] - '0';
	else b[i] = 0;
    }
	for(i = D; i<D_MAX; i++){
		a[i] = 0;
		b[i] = 0;
	}
	memset(z,0,sizeof z);
    multiplyToomCook3(a, b, D_MAX, z);
    doCarry(z, D_MAX * 2);
#ifdef TEST
    }
    t2 = clock();  
    tt = (double)(t2 - t1) / CLOCKS_PER_SEC; 
#endif
display(a, b, z);
}
/*
 * Multiplication Standard
 */
void Calc::multiplyNormal(int *a, int *b, int tLen, int *z)
{
    int i, j;  
   for(i = 0; i < tLen * 2; i++) z[i] = 0;
   for (j = 0; j < tLen; j++) {
        for (i = 0; i < tLen; i++) {
            z[j + i] += a[i] * b[j];
#ifdef TEST
            cnt_mul++; 
#endif
        }
    }
}
void Calc::multiplyToomCook3(int *a, int *b, int tLen, int *z)
{
    int *a0 = &a[0];                // Multiplicand / right side array pointer
    int *a1 = &a[tLen / 3];         // Multiplicand / central array pointer
    int *a2 = &a[tLen * 2/ 3];      // Multiplicand / left side array pointer
    int *b0 = &b[0];                // Multiplier / right side array pointer
    int *b1 = &b[tLen / 3];         // Multiplier / central array pointer
    int *b2 = &b[tLen * 2/ 3];      // Multiplier / left side array pointer
    int *c0 = &z[(tLen / 3) *  0];  // c0     
    int *c2 = &z[(tLen / 3) *  2];  // c2     
    int *c4 = &z[(tLen / 3) *  4];  // c4    
    int c1      [(tLen / 3) * 2];   // c1    
    int c3      [(tLen / 3) * 2];   // c3     
    int a_m2    [tLen / 3];         // a( -2) 
    int a_m1    [tLen / 3];         // a( -1) 
    int a_0     [tLen / 3];         // a(  0) 
    int a_1     [tLen / 3];         // a(  1) 
    int a_inf   [tLen / 3];         // a(inf) 
    int b_m2    [tLen / 3];         // b( -2) 
    int b_m1    [tLen / 3];         // b( -1) 
    int b_0     [tLen / 3];         // b(  0) 
    int b_1     [tLen / 3];         // b(  1)
    int b_inf   [tLen / 3];         // b(inf) 
    int c_m2    [(tLen / 3) * 2];   // c( -2)
    int c_m1    [(tLen / 3) * 2];   // c( -1)
    int c_0     [(tLen / 3) * 2];   // c(  0) 
    int c_1     [(tLen / 3) * 2];   // c(  1) 
    int c_inf   [(tLen / 3) * 2];   // c(inf) 
    int i;                          
    if (tLen <= 9) 
    {
        multiplyNormal(a, b, tLen, z);
        return;
    }
    // ==== a(-2) = 4 * a2 - 2 * a1 + a0, b(1) = 4 * b2 - 2 * b1 + b0
    for(i = 0; i < tLen / 3; i++)
    {
        a_m2[i] = (a2[i] << 2) - (a1[i] << 1) + a0[i];
        b_m2[i] = (b2[i] << 2) - (b1[i] << 1) + b0[i];
    }
    // ==== a(-1) = a2 - a1 + a0, b(1) = b2 - b1 + b0
    for(i = 0; i < tLen / 3; i++) 
    {
        a_m1[i] = a2[i] - a1[i] + a0[i];
        b_m1[i] = b2[i] - b1[i] + b0[i];
    }
    // ==== a(0) = a0, b(0) = b0
    for(i = 0; i < tLen / 3; i++) {
        a_0[i] = a0[i];
        b_0[i] = b0[i];
    }
    // ==== a(1) = a2 + a1 + a0, b(1) = b2 + b1 + b0
    for(i = 0; i < tLen / 3; i++) {
        a_1[i] = a2[i] + a1[i] + a0[i];
        b_1[i] = b2[i] + b1[i] + b0[i];
    }
    // ==== a(inf) = a2, b(inf) = b2
    for(i = 0; i < tLen / 3; i++) {
        a_inf[i] = a2[i];
        b_inf[i] = b2[i];
    }
    // ==== c(-2) = a(-2) * b(-2)
    multiplyToomCook3(a_m2,  b_m2,  tLen / 3, c_m2 );
    // ==== c(-1) = a(-1) * b(-1)
    multiplyToomCook3(a_m1,  b_m1,  tLen / 3, c_m1 );
    // ==== c(0) = a(0) * b(0)
    multiplyToomCook3(a_0,   b_0,   tLen / 3, c_0  );
    // ==== c(1) = a(1) * b(1)
    multiplyToomCook3(a_1,   b_1,   tLen / 3, c_1  );
    // ==== c(inf) = a(inf) * b(inf)
    multiplyToomCook3(a_inf, b_inf, tLen / 3, c_inf);
    // ==== c4 = 6 * c(inf) / 6
    for(i = 0; i < (tLen / 3) * 2; i++)
        c4[i] = c_inf[i];
        // ==== c3 = -c(-2) + 3 * c(-1) - 3 * c(0) + c(1) + 12 * c(inf) / 6
    for(i = 0; i < (tLen / 3) * 2; i++)
    {
        c3[i]  = -c_m2[i];
        c3[i] += (c_m1[i] << 1) + c_m1[i];
        c3[i] -= (c_0[i] << 1) + c_0[i];
        c3[i] += c_1[i];
        c3[i] += (c_inf[i] << 3) + (c_inf[i] << 2);
        c3[i] /= 6;
    }
    // ==== c2 = 3 * c(-1) - 6 * c(0) + 3 * c(1) - 6 * c(inf) / 6
    for(i = 0; i < (tLen / 3) * 2; i++) {
        c2[i]  = (c_m1[i] << 1) + c_m1[i];
        c2[i] -= (c_0[i] << 2) + (c_0[i] << 1);
        c2[i] += (c_1[i] << 1) + c_1[i];
        c2[i] -= (c_inf[i] << 2) + (c_inf[i] << 1);
        c2[i] /= 6;
    }
    // ==== c1 = c(-2) - 6 * c(-1) + 3 * c(0) + 2 * c(1) - 12 * c(inf) / 6
    for(i = 0; i < (tLen / 3) * 2; i++) {
        c1[i]  = c_m2[i];
        c1[i] -= (c_m1[i] << 2) + (c_m1[i] << 1);
        c1[i] += (c_0[i] << 1) + c_0[i];
        c1[i] += (c_1[i] << 1);
        c1[i] -= (c_inf[i] << 3) + (c_inf[i] << 2);
        c1[i] /= 6;
    }
    // ==== c0 = 6 * c(0) / 6
    for(i = 0; i < (tLen / 3) * 2; i++)
        c0[i] = c_0[i];
    // ==== z = c4 * x^4 + c3 * x^3 + c2 * x^2 + c1 * x + c0
    for(i = 0; i < (tLen / 3) * 2; i++) z[i + tLen / 3] += c1[i];
    for(i = 0; i < (tLen / 3) * 2; i++) z[i + (tLen / 3) * 3] += c3[i];
}
void Calc::doCarry(int *a, int tLen) {
    int cr;  
    int i;   
    cr = 0;
    for(i = 0; i < tLen; i++) {
        a[i] += cr;
        if(a[i] < 0) {
            cr = -(-(a[i] + 1) / 10 + 1);
        } else {
            cr = a[i] / 10;
        }
        a[i] -= cr * 10;
    }
    // Overflow
    if (cr != 0) printf("[ OVERFLOW!! ] %d\n", cr);
}
/*
 * Result output
 */
void Calc::display(int *a, int *b, int *z)
{
    int i; 
    int aLen = D_MAX, bLen = D_MAX, zLen = D_MAX * 2;
    while (zLen > 1 and z[zLen - 1] == 0) if (z[zLen - 1] == 0) zLen--;
    // z 
    for (i = zLen - 1; i >= 0; i--) {
        printf("%d", z[i]);
    }
    puts("");
#ifdef TEST
    printf("Counts of multiply / 1 loop = %d\n", cnt_mul);     // Multiplication count
    printf("Total time of all loops     = %f seconds\n", tt);  // processing time
#endif
}
int main()
{
    try
    {
        Calc objCalc;
        objCalc.calcToomCook();
    }
    catch (...) {
        cout << "Exception occurred!" << endl;
        return -1;
    }
    return 0;
}

