//https://codeforces.com/problemset/problem/1632/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 1 << 17;
const int MOD = 998244353;

int n, a[N];
int dp[N];
int tree[4*N];

void build(int id=0, int ns=1, int ne=n){
    if(ns==ne){
        tree[id]=a[ns];
        return ;
    }
    int l = 2*id +1 ;
    int r = l +1 ;
    int md = ns+(ne-ns)/2;
    build(l,ns, md);
    build(r, md+1,ne);
    tree[id]=__gcd(tree[l],tree[r]);
}

int get(int qs, int qe, int id=0, int ns=1, int ne=n){
    if(qs>ne || qe<ns){
        return 0;
    }
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l = 2*id +1 ;
    int r = l +1 ;
    int md = ns+(ne-ns)/2;
    return __gcd(get(qs, qe, l, ns, md), get(qs, qe, r, md+1,ne));
}

void upd(int p, int v, int id=0, int ns=1, int ne=n){
    if(ne<p || ns>p){
        return ;
    }
    if(ns==ne){
        tree[id]=v;
        return ;
    }
    int l = 2*id +1 ;
    int r = l +1 ;
    int md = ns+(ne-ns)/2;
    upd(p, v, l, ns, md);
    upd(p, v, r,md+1, ne);
    tree[id]=__gcd(tree[l],tree[r]);
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    build();
    for(int i=1;i<=n;i++){
        int l = 1;
        int r = i;
        while(l<r){
            int md  = (l+r)/2;
            int h = get(md,i);
            int sz = (i-md+1);
            if(sz>h){
                l=md+1;
            }else{
                r=md;
            }
        }
        int h = get(l,i);
        int sz = (i-l+1);
        if(sz==h){
            upd(i,1);
            dp[i]=1+dp[l-1];
        }else{
            dp[i]=dp[i-1];
        }
       cout << dp[i] << " ";
    }
    return 0;
}
