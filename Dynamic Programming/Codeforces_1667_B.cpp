//https://codeforces.com/problemset/problem/1667/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 + 5;
const int MOD = 998244353;

int tree[3][4*N];
int n;
int cn;
ll a[N];
ll sum[N];
set<ll> s;
map<ll,ll> code, decode;

void init(int b , int id=0, int ns=0 ,int ne=cn-1){
    if(ns==ne){
        tree[b][id]=-1e9;
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    init(b,l,ns, md);
    init(b,r, md+1,ne);
    tree[b][id]=-1e9;
}

void upd(int p, int v,int b,int id=0,  int ns=0, int ne=cn-1){
    if(ns>p || ne<p)
        return ;
    if(ns==ne){
        tree[b][id]=max(v,tree[b][id]);
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(p,v,b,l,ns,md);
    upd(p,v,b,r, md+1,ne);
    tree[b][id]=max(tree[b][l],tree[b][r]);
}

int get(int qs, int qe,int b, int id=0, int ns=0, int ne=cn-1){
    if(qs>qe)
        return -1e9;
    if(qs>ne || qe<ns)
        return -1e9;
    if(qs<=ns && qe>=ne){
        return tree[b][id];
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return max(get(qs, qe, b,l, ns, md), get(qs, qe, b,r, md+1,ne));

}

int t;

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        s.clear();
        code.clear();
        decode.clear();
        cin >> n;
        for(int i=1;i<=n;i++){
            cin >> a[i];
        }
        s.insert(0);
        for(int i=1;i<=n;i++){
            sum[i]=a[i]+sum[i-1];
            s.insert(sum[i]);
        }
        cn=0;
        for(auto u:s){
            code[u]=cn;
            decode[cn]=u;
            cn++;
        }
        init(0);
        init(1);
        init(2);
        upd(code[0],0,0);
        upd(code[0],0,1);
        upd(code[0],0,2);
        ll rs;
        for(int i=1;i<=n;i++){
            int p = code[sum[i]];
            ll x = get(p,p,0);
            rs=-1e9;
            rs=max(rs, x);
            x = get(0,p-1,1);
            rs=max(rs, x + i);
            x= get(p+1, cn-1,2);
            rs=max(rs, x -(i));
            upd(p, rs,0);
            upd(p,rs-i,1);
            upd(p, rs+i,2);
        }
        cout << rs << endl;
    }


    return 0;

}
