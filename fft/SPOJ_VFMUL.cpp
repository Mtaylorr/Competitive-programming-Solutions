//https://www.spoj.com/problems/VFMUL/
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

string mul(const string & a , const string & b){
    int dega = a.size()-1;
    int degb = b.size()-1;
    int resdeg = dega+degb, ressize = resdeg+1;
    ressize=(1<<int(ceil(log(ressize)/log(2))));
    valarray<complex<double> > A(0.0,ressize),B(0.0,ressize);
    for(int i=dega;i>=0;i--){
        A[dega-i]=a[i]-'0';
    }
    for(int i=degb;i>=0;i--){
        B[degb-i]=b[i]-'0';
    }
    A=fft(A);
    B=fft(B);
    A*=B;
    A=inv_fft(A);
    int cr=0;
    string res="";
    for(int i=0;i<A.size();i++){
        cr +=  int(round(A[i].real()));
        res+= '0'+(cr%10);
        cr/=10;
    }
    res+='0'+cr;
    int nb=0;
    for(int i=res.size()-1;i>0 && res[i]=='0';i--){
        nb++;
    }
    res = res.substr(0,res.size()-nb);
    reverse(res.begin(),res.end());
    return res;
}


int main(){
    freopen("input.txt", "r",stdin);
    int n;
    string s1,s2;
    cin >> n;
    while(n--){
        cin >> s1 >> s2;
        cout << mul(s1,s2) << endl;
    }
    return 0;
}
