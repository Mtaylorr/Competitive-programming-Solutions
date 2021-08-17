//https://codeforces.com/contest/348/problem/C

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = int(1e5) + 5;


#define pb push_back
#define fi first
#define se second

const int B=250;
int n,m,q;
int s,k,x;
int ans[N];
ll a[N];
vector<int> edg[N];
vector<int> incomp[N];
vector<int> bg;
int bigid[N];
ll sum[N];
ll added[N];
ll dp[B][N];

char c;


int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m >> q;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<m;i++){
        cin >> k;
        for(int j=0;j<k;j++){
            cin >> s;
            --s;
            sum[i]+=a[s];
            edg[s].pb(i);
        }
    }
    for(int i=0;i<n;i++){
        for(auto u:edg[i]){
            incomp[u].pb(i);
        }
    }
    for(int i=0;i<m;i++){
        if(incomp[i].size()>=B){
            bigid[i]=bg.size();
            bg.push_back(i);
        }else{
            bigid[i]=-1;
        }
    }
    for(int u:bg){
        for(int c:incomp[u]){
            for(int v: edg[c]){
                dp[bigid[u]][v]++;
            }
        }
    }
    while(q--){
        cin >> c;
        if(c=='+'){
            cin >> k >> x;
            --k;
            if(bigid[k]==-1){
                for(auto u:incomp[k]){
                    a[u]+=x;
                }
                for(int i=0;i<bg.size();i++){
                    sum[bg[i]]+= dp[i][k]*x;
                }
            }else{
                sum[k]+=(x*1LL*incomp[k].size());
                added[bigid[k]]+=x;
            }
        }else{
            cin >> k;
            --k;
            if(bigid[k]==-1){
                ll ans=0;
                for(int i=0;i<bg.size();i++){
                    ans+=added[i]*dp[i][k];
                }
                for(auto u:incomp[k]){
                    ans+=a[u];
                }
                cout << ans << endl;
            }else{
                ll ans=0;
                for(int i=0;i<bg.size();i++){
                    if(i==bigid[k])
                        continue;
                    ans+=added[i]*dp[i][k];
                }

                ans += sum[k];
                cout << ans << endl;
            }
        }

    }


    return 0;

}
