//https://codeforces.com/problemset/problem/103/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 + 7 ;


int n;
int w[N];
int p,a[N],b[N];
vector<int> queries[N];
ll sum[N];
set<int> ss;
vector<int> v[N];
int idx[N];
ll ans[N];


bool cmp(int x, int y){
    return a[x]>a[y];
}

int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d\n", &w[i]);
    }
    scanf("%d",&p);
    for(int i=0;i<p;i++){
        scanf("%d%d",&a[i],&b[i]);
        a[i]--;
        queries[b[i]].pb(i);
    }
    for(int i=1;i<=n;i++){
        ss.clear();
        for(auto u:queries[i]){
            ss.insert(a[u]%i);
            v[a[u]%i].pb(u);
        }
        for(auto u:ss){
            sort(v[u].begin(),v[u].end(),cmp);
            idx[u]=0;
        }
        for(auto u:ss){
            int x = (n-1-u)/i;
            int j = x*i+u;
            ll cursum=0;

            for(int k=j;k>=0;k-=i){
                cursum+=w[k];
                while(idx[u]<v[u].size() && a[v[u][idx[u]]]==k){
                    ans[v[u][idx[u]]]=cursum;
                    idx[u]++;
                }
                if(idx[u]>=v[u].size())
                    break;
            }
        }
        for(auto u:queries[i]){
            v[a[u]%i].clear();
        }
    }
    for(int i=0;i<p;i++){
        cout << ans[i] << endl;
    }

    return 0;
}
