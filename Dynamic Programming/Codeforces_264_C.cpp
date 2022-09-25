//https://codeforces.com/contest/264/problem/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 1e9 + 7  ;
const double eps = 1e-7;

int n,q;
ll dp[N];
int v[N],c[N];
int a,b;

deque<ll> dq;

void init(){
    for(int i=0;i<n;i++){
        dp[i]=-1e18;
    }
    dq.clear();
}



int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for(int i=0;i<n;i++){
        cin >> v[i];
    }
    for(int i=0;i<n;i++){
        cin >> c[i];
        c[i]--;
    }
    while(q--){
        cin >> a >> b;
        init();
        ll ans=0;
        ll rs = 0;

        for(int i=0;i<n;i++){
            if(!dq.empty() && dp[c[i]]==dq.front()){
                dq.pop_front();
            }
            ll x = dp[c[i]];
            ll y = -1e18;
            if(!dq.empty()){
                y=max(y, dq.front());
            }
            x+=a*1ll*v[i];
            y=max(y,0ll);
            y+=b*1ll*v[i];
            rs=max(x,y);
            ans=max(ans, rs);
            dp[c[i]]=max(dp[c[i]],rs);
            if(dq.empty()){
                dq.push_front(dp[c[i]]);
            }else if(dq.front()<=dp[c[i]]){
                dq.push_front(dp[c[i]]);
            }else{
                while(dq.back()<dp[c[i]]){
                    dq.pop_back();
                }
                dq.push_back(dp[c[i]]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
