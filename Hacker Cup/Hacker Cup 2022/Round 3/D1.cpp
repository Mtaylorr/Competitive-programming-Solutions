#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 6e5 + 100, M = 1000 + 5, E = 2e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;
const int alpha = 256;
const int BASE = 128;

int T;
pair<int,int> tree[4*N];
int id[4*N];
int col[4*N];

vector<int> s[4*N];
int n,m,a,b,k;
bool done[N];
int nb=0;

pair<int,int> mrg(pair<int,int> &a, pair<int,int> &b){
    return {min(a.fi,b.fi), max(a.se, b.se)};
}

void upd(int p, int i=0, int ns=0, int ne=n-1){
    if(ns>p || ne<p){
        return ;
    }
    if(ns==ne){
        tree[i]={id[p],id[p]};
        return ;
    }
    int l=2*i+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(p,  l, ns,md);
    upd(p,  r, md+1, ne);
    tree[i]=mrg(tree[l],tree[r]);
}

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]={ns,ns};
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build( l, ns,md);
    build(r, md+1, ne);
    tree[id]=mrg(tree[l],tree[r]);
}

pair<int,int> get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    if(ns>qe || ne<qs){
        return {1e9, -1};
    }
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    pair<int,int> pl = get(qs, qe, l,ns, md);
    pair<int,int> pr = get(qs, qe, r, md+1,ne);
    return mrg(pl,pr);
}

int getid(int u){
    return (u==id[u]?u:id[u]=getid(id[u]));
}

void uni(int u, int v){
    u=getid(u);
    v=getid(v);
    if(u==v)
        return ;
    if(s[u].size()<s[v].size()){
        swap(u,v);
    }
    set<int> batchs;
    for(auto x:s[v]){
        id[x]=u;
        upd(x);

        s[u].pb(x);
        if(!done[x/k]&&x<n)
            batchs.insert(x/k);
    }
    s[v].clear();
    for(auto v:batchs){
        if(done[v])
            continue;
        int l = k*v;
        int r = min(n-1, k*(v+1)-1);
        pair<int,int> x = get(l,r);
        if(x.fi==x.se){
            nb++;
            done[v]=1;
        }
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    freopen("first_time_chapter_1_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    for(int tt=1;tt<=T;tt++){
        cout << "Case #" << tt << ": ";
        cin >> n >> m >> k;
        int len=0;
        int tot=0;
        nb=0;
        for(int i=0;i<n;i++){
            done[i]=0;
            id[i]=i;
            s[i].clear();
            s[i].pb(i);
            col[i]=len++;
        }
        tot = (n+k-1)/k;
        build();
        for(int i=0;i<n;i++){
            int v = i/k;
            if(done[v])
                continue;
            int l = k*v;
            int r = min(n-1, k*(v+1)-1);
            pair<int,int> x = get(l,r);
            if(x.fi==x.se){
                nb++;
                done[v]=1;
            }
        }
        int ans = -1;
        for(int i=0;i<m;i++){
            cin >> a >> b;
            a--;b--;
            uni(col[a],col[b]);
            col[b]=getid(col[b]);
            //cout << b<<" "<<col[b] << " " << s[col[b]].size() << endl;
            id[len]=len;
            s[len].clear();
            s[len].pb(len);
            col[a]=len++;

            if(tot==nb){
                if(ans==-1){
                    ans=i+1;
                }
            }
        }
        cout << ans << "\n";

    }



    return 0;

}
