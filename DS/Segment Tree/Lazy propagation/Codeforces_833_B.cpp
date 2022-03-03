//https://codeforces.com/contest/833/problem/B
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 35e3 + 5;
const int MOD = 1e9 + 7 ;


int dp[55][N];
int n,k, a[N];
int freq[N];
int tree[2][4*N+2];
int lazy[2][4*N+2];
int pos[N];

void updlazy(int t, int id, int ns, int ne){
    if(!lazy[t][id])
        return ;
    tree[t][id]+=lazy[t][id];
    if(ns!=ne){
        int l = 2*id+1;
        int r = l+1;
        lazy[t][l]+=lazy[t][id];
        lazy[t][r]+=lazy[t][id];
    }
    lazy[t][id]=0;
}


void init(int t,int id=0, int ns=0, int ne=n){
    lazy[t][id]=0;
    if(ns==ne){
        tree[t][id]=0;
        return ;
    }
    int md = ns+(ne-ns)/2;
    int l = 2*id+1;
    int r = l+1;
    init(t, l, ns, md);
    init(t, r, md+1, ne);
    tree[t][id]=max(tree[t][l], tree[t][r]);
}

void increase(int qs, int qe, int t, int id=0, int ns=0, int ne=n){
    updlazy(t, id, ns, ne);
    if(ns>qe || ne<qs)
        return ;
    if(qs<=ns && qe>=ne){
        lazy[t][id]+=1;
        updlazy(t, id, ns, ne);
        return ;
    }
    int md = ns+(ne-ns)/2;
    int l = 2*id+1;
    int r = l+1;
    increase(qs, qe, t, l, ns  , md);
    increase(qs,qe, t, r, md+1, ne);
    tree[t][id]=max(tree[t][l], tree[t][r]);
}

void upd(int p, int v,int t, int id=0, int ns=0, int ne=n){
    updlazy(t, id, ns, ne);
    if(ns>p || ne<p)
        return ;
    if(ns==ne){
        tree[t][id]=v;
        return ;
    }
    int md = ns+(ne-ns)/2;
    int l = 2*id+1;
    int r = l+1;
    upd(p,v, t, l, ns, md);
    upd(p,v,t,r,md+1,ne);
    tree[t][id]=max(tree[t][l], tree[t][r]);
}

int  get(int qs, int qe, int t, int id=0, int ns=0, int ne=n){
    updlazy(t, id, ns, ne);
    if(qs>ne || qe<ns)
        return 0;
    if(qs<=ns && qe>=ne){
        return tree[t][id];
    }
    int md = ns+(ne-ns)/2;
    int l = 2*id+1;
    int r = l+1;
    return max(get(qs, qe, t, l, ns, md),get(qs, qe, t, r, md+1,ne));

}

int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=k;i++){
        int p = i%2;
        init(p);
        int cn=0;
        memset(pos, -1, sizeof(pos));
        for(int j=1;j<=n;j++){
            if(pos[a[j]]!=-1){
                if(i>1)
                    increase(pos[a[j]], j-1,p^1);
            }
            cn+=(pos[a[j]]==-1);
            pos[a[j]]=j;
            int x = get(0,j-1, p^1);
            dp[i][j] = x + cn;
            upd(j, x,p);
        }
    }
    cout << dp[k][n];
    return 0;
}
