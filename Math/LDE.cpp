#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 100e6 +5 ;
const int MOD = 998244353 ;

void getNextr(long long & r0, long long &r1,const long long &r){
    long long t = r0-r*r1;
    r0=r1;
    r1=t;
}

long long egcd(long long r0, long long r1, long long &x0, long long &y0){
    long long x1=y0=0,y1=x0=1;
    while(r1){
        long long r = r0/r1;
        getNextr(r0,r1,r);
        getNextr(x0,x1,r);
        getNextr(y0,y1,r);
    }
    return r0;
}

bool solveLDE(long long a, long long b, long long c, long long &x , long long &y , long long &g){
    g = egcd(a,b,x,y);
    long long m = c/g;
    x*=m;
    y*=m;
    return !(c%g);
}

int main(){
    freopen("input.txt", "r",stdin);
    long long a,b,c,x,y,g;
    cin >> a >> b >> c;
    if(!solveLDE(a,b,c,x,y,g)){
        cout << "No Solution";
    }else{
        cout << x << " " << y << endl;
    }
    return 0;
}
