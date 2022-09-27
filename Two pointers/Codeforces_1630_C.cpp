//https://codeforces.com/problemset/problem/1630/C

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 1e9 + 7   ;
const double eps = 1e-7;

int n;
int a[N];
int lf[N],rg[N];

vector<pair<int,int> > ranges, inter;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(lf, -1 ,sizeof(lf));
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        if(lf[a[i]]==-1){
            lf[a[i]]=i;
        }
        rg[a[i]]=i;
    }
    int ans=n;
    for(int i=1;i<=n;i++){
        if(lf[i]!=-1){
            ranges.pb({lf[i],rg[i]});
            ans--;
            if(lf[i]!=rg[i]){
                ans--;
            }
        }
    }
    sort(ranges.begin(),ranges.end());
    int curr=-1;
    for(auto u:ranges){
        if(u.se<curr){
            ans++;
            if(u.fi!=u.se){
                ans++;
            }
            continue;
        }
        inter.pb(u);
        curr=max(curr, u.se);
    }
    vector<int> tmp;
    for(int i=0;i<inter.size();){
        int j=i;
        tmp.clear();
        while(j<inter.size() && inter[j].fi<=inter[i].se){
            tmp.pb(j);
            j++;
        }

        if(tmp.size()==1){
            i=j;
            continue;
        }
        if(tmp.size()==2){
            i=j-1;
            ans++;
            continue;
        }
        for(int k=1;k<tmp.size()-1;k++){
            if(inter[tmp[k]].fi!=inter[tmp[k]].se){
                ans+=2;
            }else{
                ans++;
            }
        }
        ans++;
        i=j-1;
    }
    cout << ans;

    return 0;
}
