//https://codeforces.com/contest/7/problem/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e6 + 5;
const int MOD = 1e9 +7 ;

int dp[N];
string s;
string t;
int n;
bool vis[N];
int m;

int z[2*N];

void Z_algo(){
    z[0]=0;
    int l=1,r=1;
    for(int i=1;i<m;i++){
        int x = z[i-l];
        if(i+x>=r){
            l=i;
            r=max(r,i);
            while(r<m && s[r-l]==s[r])
                r++;
            z[i]=r-l;
        }else{
            z[i]=z[i-l];
        }

    }
}

int main()
{
    freopen("input.txt", "r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s;
    n=s.size();
    t=s;
    reverse(t.begin(),t.end());
    s+='#';
    s+=t;
    m=2*n+1;
    Z_algo();
    for(int i=n+1;i<m;i++){
        if(z[i]==m-i){
            vis[m-i-1]=1;
        }
    }
    ll ans=0;
    for(int i=0;i<n;i++){
        if(vis[i]){
            dp[i]=1;
            if(i>=1){
                dp[i]+=(dp[(i-1)/2]);
            }
        }
        ans+=dp[i];
    }
    cout << ans << endl;
    return 0;

}
