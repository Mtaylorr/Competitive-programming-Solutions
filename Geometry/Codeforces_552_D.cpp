//https://codeforces.com/problemset/problem/552/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 + 5 , E = 2e6 + 5;
const int MOD = 1e9 + 7 ;

int n;
int x[N],y[N];
map<pair<int,int>,int> freq;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll ans=0;
    cin >> n;
    for(int i=0;i<n;i++){
        cin  >> x[i] >> y[i];
    }
    for(int i=0;i<n;i++){
        freq.clear();
        int nb=0;
        for(int j=0;j<n;j++){
            if(j==i)
                continue;
            int dx = x[j]-x[i];
            int dy = y[j]-y[i];
            int d = __gcd(abs(dx), abs(dy));
            dx/=d;
            dy/=d;
            if(dx<0){
                dx*=-1;
                dy*=-1;
            }else if(dx==0){
                dy=abs(dy);
            }
            ans+=nb-freq[{dx,dy}];
            freq[{dx,dy}]++;
            nb++;
        }
    }
    cout << ans/3 << endl;
    return 0;

}
