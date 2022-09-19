//https://codeforces.com/problemset/problem/792/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7 ;

ll n;
int q;
string s;
ll u;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    int mxbit=0;
    ll cur=1;
    while(cur<n+1){
        cur*=2;
        mxbit++;
    }
    mxbit--;
    while(q--){
        cin >> u;
        cin >> s;
        int mnbit=0;
        while(1){
            if((1ll<<mnbit)&u){
                break;
            }
            mnbit++;
        }
        for(auto c:s){
            if(c=='U'){
                if(mnbit==mxbit){
                    continue;
                }
                if(u&(1ll<<mnbit)){
                    u-=(1ll<<mnbit);
                }
                mnbit++;
                if((u&(1ll<<mnbit))==0){
                    u+=((1ll<<mnbit));
                }
            }else{
                if(mnbit!=0){
                    if(c=='L'){
                        u-=(1ll<<mnbit);
                    }
                    mnbit--;
                    u+=(1ll<<mnbit);

                }
            }
        }
        cout << u << endl;
    }


    return 0;


}
