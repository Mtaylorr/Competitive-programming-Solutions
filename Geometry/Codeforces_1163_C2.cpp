//https://codeforces.com/problemset/problem/1163/C2
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 + 5, E = 1 << 17;
const int MOD =  998244353 ;


map<pair<int,int> ,int> freq;
map<pair<int,int> ,set<pair<int,int> > > val;

int x[N],y[N];
int n;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            int dx = x[j]-x[i];
            int dy = y[j]-y[i];
            if(dx==0){
                freq[{0,1}]++;
                val[{0,1}].insert({x[i],0});
            }else if(dy==0){
                freq[{1,0}]++;
                val[{1,0}].insert({y[i],0});
            }else{
                int d = __gcd(abs(dx), abs(dy));
                dx/=d;
                dy/=d;
                if(dx<0){
                    dx*=-1;
                    dy*=-1;
                }
                int _x = x[i]%dx;
                if(_x<0){
                    _x+=dx;
                }
                int _y = y[i]-((x[i]-_x)/dx)*dy;
                val[{dx,dy}].insert({_x,_y});
            }
        }
    }
    ll ans=0;
    ll nb=0;
    for(auto &u:val){
        nb+=u.se.size();
    }
    for(auto &u:val){
        ll l = u.se.size();
        ll r = nb-u.se.size();
        ans+=l*r;
    }
    cout << ans/2 << endl;
    return 0;
}
