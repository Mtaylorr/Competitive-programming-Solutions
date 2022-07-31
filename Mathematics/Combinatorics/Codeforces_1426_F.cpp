//https://codeforces.com/problemset/problem/1426/F
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 4e6 +5 ;
const int MOD = 1e9 + 7;


ll mul(ll u , ll v, ll mod=MOD){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
    return ((u%mod)-(v%mod)+mod)%mod;
}

int n;
string s;
int po[N];
int cntu[4][N];
int cntd[4][N];
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    po[0]=1;
    cin >> n;
    for(int i=1;i<=n;i++){
        po[i]=mul(3, po[i-1]);
    }
    cin >> s;
    for(int i=1;i<=n;i++){
        for(int j=0;j<4;j++){
            cntu[j][i]=cntu[j][i-1];
        }
        if(s[i-1]!='?'){
            cntu[s[i-1]-'a'][i]++;
        }else{
            cntu[3][i]++;
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=0;j<4;j++){
            cntd[j][i]=cntd[j][i+1];
        }
        if(s[i-1]!='?'){
            cntd[s[i-1]-'a'][i]++;
        }else{
            cntd[3][i]++;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        char c = s[i-1];
        if(c=='?' || c=='b'){
            int cur = mul(cntu[0][i-1], cntd[2][i+1]);
            int cntunknown = cntu[3][i-1]+cntd[3][i+1];
            cur=mul(cur, po[cntunknown]);
            ans=add(ans, cur);
            if(cntd[3][i+1]){
                cur = mul(cntu[0][i-1], cntd[3][i+1]);
                cntunknown = cntu[3][i-1]+cntd[3][i+1]-1;
                cur=mul(cur, po[cntunknown]);
                ans=add(ans, cur);
            }
            if(cntu[3][i-1]){
                cur = mul(cntu[3][i-1], cntd[2][i+1]);
                cntunknown = cntu[3][i-1]+cntd[3][i+1]-1;
                cur=mul(cur, po[cntunknown]);
                ans=add(ans, cur);
            }
            if(cntd[3][i+1] && cntu[3][i-1]){
                cur = mul(cntu[3][i-1], cntd[3][i+1]);
                cntunknown = cntu[3][i-1]+cntd[3][i+1]-2;
                cur=mul(cur, po[cntunknown]);
                ans=add(ans, cur);
            }
        }
    }
    cout << ans;
    return 0;

}
