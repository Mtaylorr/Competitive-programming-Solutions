//https://www.spoj.com/problems/GOT/
#include <bits/stdc++.h>

using namespace std;

#define pb push_back

const int N = int(3e5)+5;

int n, a[N], q;
int  qs[N], qe[N], qi[N], s, e, qa[N], qlca[N],qk[N];
bool occ[N];
int freq[N];

vector<vector<int> > adj;
vector<int> node2ind, ind2node, depth;
int spt[int(5e5)+5][20];
int lg[int(5e5)+5];

vector<int> st , et, dfsorder;


void init(){
    adj.clear();
    adj.resize(n+1);
    depth.resize(n+1);
    node2ind.resize(n+1);
    ind2node.clear();
    st.resize(n+1);
    et.resize(n+1);
    dfsorder.clear();
    memset(freq, 0, sizeof(freq));
    memset(occ, 0, sizeof(occ));
}

void dfs(int u, int dpth=0, int p=0){
    node2ind[u]=ind2node.size();
    ind2node.pb(u);
    depth[u]=dpth;
    st[u]=dfsorder.size();
    dfsorder.pb(u);
    for(int v:adj[u]){
        if(v==p)
            continue;
        dfs(v, dpth+1, u);
        ind2node.pb(u);
    }
    et[u]=dfsorder.size();
    dfsorder.pb(u);
}

void buildspt(){
    lg[0]=-1;
    for(int i=0;i<ind2node.size();i++){
        spt[i][0]=i;
        lg[i+1]= lg[i]+ !(i&i+1);
    }
    for(int j=1;(1<<j)<=ind2node.size();j++){
        for(int i=0;i+(1<<j)<=ind2node.size();i++){
            int a = spt[i][j-1];
            int b = spt[i+(1<<(j-1))][j-1];
            spt[i][j] = (depth[ind2node[a]]<depth[ind2node[b]] ? a:b);
        }
    }
}

int SPTMQ(int a , int b){
    int sz = b-a+1;
    int l = lg[sz];
    a = spt[a][l];
    b = spt[b-(1<<l)+1][l];
    return (depth[ind2node[a]]<depth[ind2node[b]] ? a:b);
}

int SPTLCA(int u , int v){
    int a = node2ind[u];
    int b = node2ind[v];
    if(a>b)
        swap(a,b);
    return ind2node[SPTMQ(a,b)];
}



void add(int val){
    freq[val]++;
}


void rem(int val){
    freq[val]--;

}

void change(int val){
    if(occ[val]^=1)
        add(a[val]);
    else{
        rem(a[val]);
    }
}
void update(int cur){
    while(e<qe[cur]){
        change(dfsorder[++e]);
    }
    while(s>qs[cur]){
        change(dfsorder[--s]);
    }
    while(e>qe[cur]){
        change(dfsorder[e--]);
    }
    while(s<qs[cur]){
        change(dfsorder[s++]);
    }
}

void mo(){
    int sq = sqrt(dfsorder.size());
    sort(qi, qi+q, [sq](int a, int b){return make_pair(qs[a]/sq,qe[a])<make_pair(qs[b]/sq, qe[b]);});
    s=0;
    e=-1;
    for(int i=0;i<q;i++){
        int cur = qi[i];
        update(cur);
        add(a[qlca[cur]]);
        qa[cur]=freq[qk[cur]]!=0;
        rem(a[qlca[cur]]);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    while(~scanf("%d%d",&n,&q)){
        for(int i=0;i<n;i++){
        cin >> a[i+1];
    }
    int u,v, k;
    init();
    for(int i=1;i<n;i++){

        scanf("%d%d",&u,&v);
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1);
    buildspt();
    for(int i=0;i<q;i++){
        scanf("%d%d%d",&u,&v,&k);
        qk[i]=k;
        qi[i]=i;
        if(st[u]>st[v])
            swap(u,v);
        int lca = SPTLCA(u,v);
        qlca[i]=lca;
        if(lca==u){
            qs[i] = st[u]+1;
            qe[i] = st[v];
        }else{
            qs[i] = et[u];
            qe[i] = st[v];
        }

    }
    mo();
    for(int i=0;i<q;i++){
        printf("%s\n", (qa[i]?"Find":"NotFind"));
    }
}
    return 0;
}
