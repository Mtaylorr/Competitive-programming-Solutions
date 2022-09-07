//https://codeforces.com/contest/1216/problem/E2
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5, E = 1 << 17;
const int MOD =  998244353 ;


ll get(ll x){
    string s = to_string(x);
    ll big=1;
    for(int i=0;i<s.size();i++){
        big*=10;
    }
    ll ans=0;
    for(int j=s.size()-1;j>=0;j--){
        ll upper = min(big-1,x);
        ll lower = (big/10);
        ll l = x-upper+1;
        ll r = x-lower+1;
        ans+=(((r-l+1)*(l+r))/2) * (j+1);
        big/=10;
    }
    return ans;
}

int q;
ll k;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> q;
    while(q--){
        cin >> k;
        int l = 1 ;
        int r= 5e8;
        while(l<r){
            int md  = (l+r)/2;
            ll x = get(md);
            if(x<k){
                l=md+1;
            }else{
                r=md;
            }
        }
        k-=get(l-1);
        ll upper = 1;
        for(int j=0;;j++){
            l = upper;
            upper*=10;
            r = upper-1;
            ll sz = r-l+1;
            if(k>sz*(j+1)){
                k-=sz*(j+1);
                continue;
            }
            k--;
            ll x = k/(j+1) + l;
            string s = to_string(x);
            cout << s[k%(j+1)] << endl;
            break;
        }
    }
    return 0;
}
