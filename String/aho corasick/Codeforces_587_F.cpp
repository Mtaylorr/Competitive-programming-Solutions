//https://codeforces.com/contest/587/problem/F
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e5+10, alpha = 128;
int trie[N][alpha], szs[N], ids[N], F[N], ndcnt;
char child[N][alpha];
int last[N];
vector<int> en[N];
vector<int> q[N];
vector<int> adj[N];
int n,m;
char str[N];
vector<int> queries[N];
int l[N], r[N], k;
ll ans[N];
ll SQsum[N], SQtot[N];

int addnode(){
    memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
    ids[ndcnt]=-1;
    szs[ndcnt]=0;
    return ndcnt++;
}
void init(){
    ndcnt=0;
    addnode();
}

void ins(const char * str, int id){
    int cur;
    for(cur=0;*str;str++){
        int &r = trie[cur][*str];
        if(r==-1){
            r=addnode();
            child[cur][szs[cur]++]=*str;
        }
        cur=r;
        q[cur].pb(id);
    }
    en[cur].pb(id);
    last[id]=cur;
}

int getNext(int f, char c){
    while(trie[f][c]==-1)
        f=F[f];
    return trie[f][c];
}

void buildFail(){
    queue<int> q;
    for(int i=0;i<alpha;i++){
        int &r = trie[0][i];
        if(r==-1){
            r=0;
        }else{
            F[r]=0;
            q.push(r);
        }
    }
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(int i=0;i<szs[cur];i++){
            char c = child[cur][i];
            int r = trie[cur][c];
            int f = F[cur];
            F[r] = getNext(f, c);
            q.push(r);
        }
    }
}

ll cumSum[N];

void buildCTree(){
    for(int i=1;i<ndcnt;i++){
        adj[F[i]].pb(i);
    }
}


ll dfsbig(int v, int i){
    ll cnt=0;
    for(auto u:q[v])
        if(u==i)
            ++cnt;
    for(auto u:adj[v]){
        cnt+=dfsbig(u, i);
    }
    for(auto x:en[v]){
        cumSum[x]+= cnt;
    }
    return cnt;
}

void calcBig(int i){
    if(queries[i].size()==0)
        return;
    dfsbig(0, i);
    for(int i=1;i<n;i++){
        cumSum[i]+=cumSum[i-1];
    }
    for(auto id:queries[i]){

        ans[id]= cumSum[r[id]] - (l[id]==0?0: cumSum[l[id]-1]);
    }
    for(int i=0;i<n;i++){
        cumSum[i]=0;
    }
}

int B ;
int sz[N];

void add(int x, ll val){
    while(x<n && x%B)
        SQsum[x++]+=val;
    while(x<n){
        SQtot[x/B]+=val;
        x+=B;
    }
}

ll get(ll x){
    return (x<0 ?0 :SQsum[x] + SQtot[x/B]);
}

void dfs(int v){
    for(auto u:en[v]){
        add(u,1);
    }
    for(auto i:q[v]){
        if(sz[i]<=B){
            for(auto j:queries[i]){
                ans[j]+= (get(r[j])-get(l[j]-1));
            }
        }
    }
    for(auto u:adj[v]){
        dfs(u);
    }
    for(auto u:en[v]){
        add(u,-1);
    }
}


int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&m);
    init();
    for(int i=0;i<n;i++){
        scanf("%s",str);
        sz[i]=strlen(str);
        ins(str,i);

    }
    buildFail();
    buildCTree();
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&l[i],&r[i], &k);
        --l[i];
        --r[i];
        queries[--k].pb(i);
    }
    B=sqrt(n);
    for(int i=0;i<n;i++){
        if(sz[i]>B){
            calcBig(i);
        }
    }
    dfs(0);
    for(int i=0;i<m;i++){
        cout << ans[i] << "\n";
    }
    return 0;
}

