//https://codeforces.com/contest/777/problem/E
#include <bits/stdc++.h>

using namespace std;
const int N = 3e5+2;

#define fi first
#define se second

typedef long long ll;

int n;
int a,b,h;
vector<pair<pair<int,int> ,int > > v;
set<int> ss;
map<int,int> code;
ll tree[N];
int cn=1;

void upd(int x, ll v){
    for(;x<=cn;x+=(x)&(-x)){
        tree[x]=max(tree[x],v);
    }
}

ll get(int x){
    ll res=0;
    for(;x;x-=(x)&(-x)){
        res=max(res,tree[x]);
    }
    return res;
}



int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d%d%d",&a,&b,&h);
        v.push_back({{b,a},h});
        ss.insert(a);
        ss.insert(b);
    }

    for(auto u:ss){
        code[u]=cn++;
    }
    for(int i=0;i<n;i++){
        v[i].fi.fi = code[v[i].fi.fi];
        v[i].fi.se = code[v[i].fi.se];
    }
    sort(v.begin(),v.end());
    ll ans=0;
    for(int i=n-1;i>=0;i--){
        ll res  = get(v[i].fi.fi-1);
        ans=max(ans, res+v[i].se);
        upd(v[i].fi.se, res+v[i].se);
    }
    cout << ans ;
    return 0;
}
