//https://www.spoj.com/problems/POLYMUL/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 + 7 ;

valarray<complex<double> > fft(const valarray<complex<double> >&x, int sign=-1){
    int N = x.size();
    if(N==1){
        return x;
    }
    valarray<complex<double> > odd,even;
    even = x[slice(0,N/2,2)];
    odd = x[slice(1,N/2,2)];
    even=fft(even, sign);
    odd=fft(odd, sign);
    valarray<complex<double> > X(N);
    complex<double> cm1=1, cm2 = exp(complex<double>(0,sign*2*acos(-1)/N));
    for(int i=0;i<N/2;i++){
        X[i] = even[i] + cm1*odd[i];
        X[i+N/2]=even[i] -cm1*odd[i];
        cm1*=cm2;
    }
    return X;
}

valarray<complex<double> > inv_fft(const valarray<complex<double> >&x){
    complex<double> N = x.size();
    return fft(x,1)/N;
}

int a[N], b[N];
int t,n;

valarray<complex<double> > mul(){
    int ressize = 2*n+1;
    ressize = 1<<int(ceil(log(ressize)/log(2)));
    valarray<complex<double> >A(0.0, ressize), B(0.0,ressize);
    for(int i=n,j=0;~i;i--,j++){
        A[j]=a[i];
        B[j]=b[i];
    }
    A=fft(A);
    B=fft(B);
    A*=B;
    A=inv_fft(A);
    return A;
}



int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<=n;i++){
            scanf("%d",&a[i]);
        }
        for(int i=0;i<=n;i++){
            scanf("%d",&b[i]);
        }
        valarray<complex<double> > res = mul();
        for(int i=2*n;i>=0;i--){
            cout << (long long)(round(res[i].real())) << " ";
        }
        cout << endl;
    }

    return 0;
}

