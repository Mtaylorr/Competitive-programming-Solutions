//https://codeforces.com/contest/163/problem/E

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e6 + 5, alpha = 26;
int trie[N][alpha], szs[N], myId[N], F[N];
bool isleaf[N];
vector<int> listids[N];
int ids[N];
int ndcnt=0;
char child[N][alpha];
char str[N];
int n,k;
int en[N];
int tree[2*N];

char c;
int x;
char s[N];
vector<int> adj[N];
bool vis[N];
int ti[N], to[N], tt=1;
bool exist[N];

int convc(char c){
    return c-'a';
}

void add_tree(int x, int v){
    for(;x<=tt;x+=(x)&(-x))
        tree[x]+=v;
}

int get_tree(int x){
    int res=0;
    for(;x;x-=(x)&(-x))
        res+=tree[x];
    return res;
}

void add(int x, int d){
    if(exist[x]==0 && d==1 || exist[x]==1 && d==-1){
        add_tree(ti[en[x]], d);
        add_tree(to[en[x]], -d);
        exist[x]=!exist[x];
    }
}

int addnode(){
    memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
    szs[ndcnt]=0;
    return ndcnt++;
}

void init(){
    ndcnt=0;
    addnode();
}

int ins(const char * str){
    int cur;
    for(cur=0;*str;str++){
       int &r = trie[cur][convc(*str)];
       if(r==-1){
            r = addnode();
            child[cur][szs[cur]++]= *str;
       }
       cur=r;
    }
    return cur;
}

int getNext(int f, char c){
    while(trie[f][convc(c)]==-1)
        f= F[f];
    return trie[f][convc(c)];
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
            int &r  = trie[cur][convc(c)];
            int f = getNext(F[cur],c);
            F[r] = f;
            q.push(r);
        }
    }
}

void dfs(int u){
    vis[u]=1;
    ti[u]=tt++;
    for(auto v:adj[u]){
        dfs(v);
    }
    to[u]=tt++;
}
ll solve(){
    ll res=0;
    char * ss = s;
    for(int cur=0;*ss;ss++){
        cur = getNext(cur, *ss);
        res+=get_tree(ti[cur]);
    }
    return res;
}


int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&k);
    init();
    for(int i=0;i<k;i++){
        scanf("%s",str);
        en[i] = ins(str);
    }
    buildFail();
    for(int i=1;i<ndcnt;i++){
        adj[F[i]].pb(i);
    }


    for(int i=0;i<ndcnt;i++){
        if(vis[i]==0)
            dfs(i);
    }
    for(int i=0;i<k;i++){
        add(i, 1);
    }
    for(int i=0;i<n;i++){
        scanf(" %c",&c);
        switch(c){
        case '?':
            scanf("%s",s);
            printf("%lld\n",solve());
            break;
        case '-':
            scanf("%d",&x);
            add(--x,-1);
            break;
        case '+':
            scanf("%d",&x);
            add(--x,1);
            break;
        }
    }





    return 0;
}

