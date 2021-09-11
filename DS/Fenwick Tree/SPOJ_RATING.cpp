//https://www.spoj.com/problems/RATING/
#include <bits/stdc++.h>

using namespace std;
const int N = 4e5 + 5;

#define fi first
#define se second

typedef long long ll;

int n;
vector<pair<int,int> > a[N];
int x,y;
int ans[N];
int tree[N];

void upd(int x, int v){
    for(;x<=3e5;x+=(x)&(-x)){
        tree[x]+=v;
    }
}

int get(int x){
    int res=0;
    for(;x;x-=(x)&(-x)){
        res+=tree[x];
    }
    return res;
}

int low[N];

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d%d",&x,&y);
        a[x].push_back({i,y});
    }
    for(int i=1;i<=3e5;i++){

        for(auto u:a[i]){
            ans[u.fi]+=get(u.se);
            low[u.fi]=get(u.se-1);
        }
        for(auto u:a[i]){
           upd(u.se, 1);
        }
        for(auto u:a[i]){
            ans[u.fi]+=get(u.se-1)-low[u.fi];
        }
    }
    for(int i=0;i<n;i++){
        cout << ans[i] << "\n";
    }
    return 0;
}
