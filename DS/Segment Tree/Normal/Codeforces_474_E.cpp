//https://codeforces.com/problemset/problem/474/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 3e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7 ;

pair<int,int> tree[4*N];

map<ll,int> code;
set<ll> dis;
int n,d;
ll h[N];
int par[N];
int cn;
pair<int,int> better(pair<int,int> &a , pair<int,int > &b){
    if(a.fi>b.fi){
        return a;
    }
    if(a.fi<b.fi)
        return b;
    return a;
}


void upd(int qp, int qv, int qi, int id=0, int ns=0, int ne=cn-1){
    if(ns>qp || ne<qp){
        return ;
    }
    if(ns==ne){
        tree[id]={qv, qi};
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = (ns)+(ne-ns)/2;
    upd(qp, qv, qi,  l, ns, md);
    upd(qp, qv, qi, r, md+1,ne);
    tree[id]=better(tree[l],tree[r]);
}

pair<int,int> get(int qs, int qe, int id=0, int ns=0, int ne=cn-1){
    if(qs>ne || qe<ns){
        return {0,0};
    }
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    pair<int,int> rl = get(qs, qe,l, ns,md);
    pair<int,int> rr = get(qs, qe, r, md+1,ne);
    return better(rl, rr);
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> d;
    for(int i=0;i<n;i++){
        cin >> h[i];
        dis.insert(h[i]);
        dis.insert(h[i]-d);
        dis.insert(h[i]+d);
    }
    for(auto u:dis){
        code[u]=cn++;
    }
    int rs=-1;
    int rsi=-1;
    for(int i=0;i<n;i++){
        pair<int,int>x =get(code[h[i]+d],cn-1);
        pair<int,int> y = get(0,code[h[i]-d]);
        x = better(x,y);
        x.fi+=1;
        par[i+1]=x.se;
        upd(code[h[i]], x.fi, i+1);
        if(x.fi>rs){
            rs=x.fi;
            rsi=i+1;
        }
    }
    cout << rs << endl;
    vector<int> tmp;
    while(rsi!=0){
        tmp.pb(rsi);
        rsi=par[rsi];
    }
    reverse(tmp.begin(),tmp.end());
    for(auto u:tmp){
        cout << u << " ";
    }
    return 0;
}
