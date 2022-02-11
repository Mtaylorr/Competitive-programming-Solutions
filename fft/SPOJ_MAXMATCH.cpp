//https://www.spoj.com/problems/MAXMATCH/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 + 7 ;

valarray<complex<double> > fft(const valarray<complex<double> > &x,int sign=-1){
    int N = x.size();
    if(N==1){
        return x;
    }
    valarray<complex<double> > even = x[slice(0,N/2,2)];
    valarray<complex<double> > odd = x[slice(1,N/2,2)];
    even=fft(even,sign);
    odd=fft(odd,sign);
    valarray<complex<double> > X(N);
    complex<double> cm1=1,cm2=exp(complex<double>(0,sign*2*acos(-1)/N));
    for(int k=0;k<N/2;k++){
        X[k] = even[k]+cm1*odd[k];
        X[k+N/2] = even[k]-cm1*odd[k];
        cm1*=cm2;
    }
    return X;
}

valarray<complex<double> > inv_fft(const valarray<complex<double> > &x){
    complex<double> N = x.size();
    return fft(x,1)/N;
}

valarray<int> mul(const string & a , char c){
    int asz = a.size();
    int ressize = asz+asz-1;

    ressize=1<<int(ceil(log(ressize)/log(2)));
    valarray<complex<double> > A(0.0,ressize),B(0.0,ressize);

    for(int i=asz-1,j=0;~i;i--,j++){
        A[j]=a[j]==c;
        B[j]=a[i]==c;
    }

    A=fft(A);
    B=fft(B);
    A*=B;
    A=inv_fft(A);
    valarray<int> res(asz-1);
    for(int i=0;i<res.size();i++){
        res[i]=int(round(A[i].real()));
    }
    return res;
}


int main(){
    freopen("input.txt", "r",stdin);
    int n;
    string s;
    cin >> s;
    valarray<int> res = mul(s,'a');
    res+=mul(s,'b');
    res+=mul(s,'c');
    int mx=res.max();
    int cnt=0;

    cout << mx << endl;
    string sep="";
    for(int i=res.size()-1;i>=0;i--){
        if(res[i]==mx)
            cout <<sep << res.size()-i ,sep=" ";
    }
    cout << endl;
    return 0;
}
