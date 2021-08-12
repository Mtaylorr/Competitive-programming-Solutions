//https://codeforces.com/contest/598/problem/C
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)

const long double  pi=  (4*atan(1));

const int N = int(2e6) + 3;
const int MOD = int(1e9) + 7;


int n;
long double x[N], y[N],ang[N];

vector<int> v;

long double getang(long double x, long double y){
    if(y==0){
        if(x>0)
            return 0;
        return pi;
    }else if (x == 0) {
        if (y > 0)
            return 0.5 * pi;
        return 1.5 * pi;
    }
    else if(x>0 && y>0){
        return atan(y/x);
    }else if(x>0 && y<0){
        return 2*pi - atan(abs(y)/abs(x));
    }else if(x<0 && y>0){
        return pi- atan(abs(y)/abs(x));
    }else{
        return 1.0*pi+ atan(abs(y)/abs(x));
    }
}

long double norm(int i){
    return sqrt(x[i]*x[i]+y[i]*y[i]);
}

long double getcos(int i, int j){
    return min(abs(ang[j]-ang[i]), 2*pi-abs(ang[j]-ang[i]));
}

bool cmp(int a, int b){
    return ang[a]<ang[b];
}

int main() {
    FAST;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
        ang[i]=getang(x[i],y[i]);
        v.pb(i);
    }
    sort(all(v),cmp);
    int pos = 0;
    long double mi = 500;
    for(int i=0;i<n;i++){
        long double co = getcos(v[i],v[(i+1)%n]);
        if(mi>co){
            mi=co;
            pos=i;
        }
    }
    cout << v[pos]+1 << " "<< v[(pos+1)%n]+1 << endl;

    return 0;
}
