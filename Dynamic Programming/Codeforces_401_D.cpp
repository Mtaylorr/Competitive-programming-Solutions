//https://codeforces.com/problemset/problem/401/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 4e5 + 5, E = 1 << 17;
const int MOD =  1e9 + 7;

ll dp[1<<19][100];
string n;
int sz;
int target ;
int m;

ll solve(int mask, int md){
    if(mask==target){
        return md==0;
    }
    if(dp[mask][md]!=-1){
        return dp[mask][md];
    }
    ll rs=0;
    int cur=1;
    int bef=-1;
    for(int i=0;i<sz;i++){
        int x = n[i]-'0';
        cur*=2;
        if(x==bef){
            continue;
        }

        if(mask==0 && x==0)
            continue;
        if(mask&(cur/2))
            continue;
        bef=x;
        rs+=solve(mask+cur/2, (md*10 + x)%m );
    }
    return dp[mask][md]=rs;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    cin >> n >> m;
    sort(n.begin(),n.end());
    sz=n.size();
    target=(1<<(n.size()))-1;
    cout << solve(0,0);
    return 0;
}
