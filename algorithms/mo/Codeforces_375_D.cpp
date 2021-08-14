//https://codeforces.com/problemset/problem/375/D

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
typedef long long ll;

const int N = int(3e5)+5;

int n, a[N], q;
int  qs[N], qe[N], qi[N], qk[N], s, e;
int qa[N];
int occ[N];
int freq[N];
int cntfreq[N];
int st[N], et[N];

vector<int> adj[N];
vector<int> dfsorder;


void dfs(int u, int p=-1){
    st[u] = dfsorder.size();
    dfsorder.pb(u);
    for(auto v:adj[u]){
        if(v==p)
            continue;
        dfs(v,u);
    }
    et[u]=dfsorder.size();
    dfsorder.pb(-1);
}


void add(int val){
    if(val==-1)
        return;
    freq[a[val]]++;
    cntfreq[freq[a[val]]]++;
}

void rem(int val){
    if(val==-1)
        return;
    cntfreq[freq[a[val]]]--;
    freq[a[val]]--;
}

void update(const int & cur){
    while(e<qe[cur])
        add(dfsorder[++e]);

    while(s>qs[cur])
        add(dfsorder[--s]);

    while(e>qe[cur])
        rem(dfsorder[e--]);

    while(s<qs[cur])
        rem(dfsorder[s++]);

}

void mo(){
    int sq = sqrt(n);
    sort(qi, qi+q, [sq](int a, int b){return make_pair(qs[a]/sq,qe[a])<make_pair(qs[b]/sq, qe[b]);});
    s=0;
    e=-1;
    for(int i=0;i<q;i++){
        int cur = qi[i];
        update(cur);
        qa[cur]= cntfreq[qk[cur]];
    }
}

int main(){
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);

    }
    int u,v;
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        u--;v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0);
    for(int i=0;i<q;i++){
        scanf("%d%d" , &qs[i],&qe[i]);
        qk[i] = qe[i];
        qe[i] = et[qs[i]-1];
        qs[i] = st[qs[i]-1];
        qi[i] = i;
    }
    mo();
    for(int i=0;i<q;i++){
        printf("%d\n",qa[i]);
    }
    return 0;
}
