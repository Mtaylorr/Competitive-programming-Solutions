#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5, E = 1 << 17;
const int MOD =  998244353 ;
const double eps = 1e-7;

int n,v1,v2,k,L;

double calc(double u){
    int nb  = (n+k-1)/k;
    double curp = 0;
    double ans=0;
    for(int i=0;i<nb;i++){
        double d =min(u, L-curp);
        if(d<0)
            d=0;
        double t = (L*1.0-(d*1.0))/(v1*1.0) + (d/(v2*1.0));

        ans=max(ans, t);
        curp += (2*d*v1)/((v1+v2)*1.0);
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> L >> v1 >> v2 >> k;
    double l=0;
    double r = L;
    for(int i=0;i<1000;i++){
        double m1 =  l +(r-l)/3;
        double m2 = r -(r-l)/3;
        double d1 = calc(m1);
        double d2 = calc(m2);
        if(d1<=d2+eps){
            r=m2;
        }else{
            l=m1;
        }
    }
    cout << fixed << setprecision(10) << calc(r);
    return 0;
}
