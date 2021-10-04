//https://codeforces.com/problemset/problem/963/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e5+7, alpha=128;
char str[N];
char s[N];

int trie[N][alpha],ids[N],F[N],nxtId[N], szs[N];
bool isleaf[N];
char child[N][alpha];
int ndcnt;
int myId[N];
int sz[N];

int k[N];

int addnode(){
    memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
    szs[ndcnt]=0;
    ids[ndcnt]=-1;
    return ndcnt++;
}

void init(){
    ndcnt=0;
    addnode();
}

void ins(const char * str,int id){
    int cur;
    for(cur=0;*str;str++){
        int &r = trie[cur][*str];
        if(r==-1){
            r=addnode();
            child[cur][szs[cur]++]=*str;
        }
        cur=r;
    }
    ids[cur]=id;
}

int getNext(int f, char c){
    while(trie[f][c]==-1){
        f=F[f];
    }
    return trie[f][c];
}

void buildFail(){
    queue<int> q;
    for(int i=0;i<alpha;i++){
        int &r = trie[0][i];
        if(r==-1)
            r=0;
        else{
            nxtId[r]=F[r]=0;
            q.push(r);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<szs[cur];i++){
            char c = child[cur][i];
            int r = trie[cur][c];
            int f = F[cur];
            nxtId[r]=F[r] = getNext(f, c);
            q.push(r);
        }
    }
}

int getNextId(int cur){
    if(cur==0)
        return cur;
    int &r = nxtId[cur];
    if(ids[r]!=-1)
        return r;
    return r = getNextId(r);
}

vector<vector<int> > match(const char * s, int nb){
    vector<vector<int> > res(nb);
    int cur=0;
    for(int i=0;s[i];i++){
        cur = getNext(cur, s[i]);
        for(int j=cur;j;j=getNextId(j)){
            if(ids[j]!=-1)
                res[ids[j]].pb(i);
        }
    }
    return res;
}

int n;

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%s",s);
    scanf("%d",&n);
    int m = strlen(s);
    init();
    for(int i=0;i<n;i++){
        scanf("%d",&k[i]);
        scanf("%s",str);
        sz[i]=strlen(str);
        ins(str, i);
    }
    buildFail();
    vector<vector<int> > res = match(s,n);
    for(int i=0;i<n;i++){
        if(res[i].size()<k[i]){
            cout << -1 << endl;
        }else{
            int ans=m;
            for(int j=0;j+k[i]-1<res[i].size();j++){
                ans=min(ans, res[i][j+ k[i]-1] - res[i][j]);
            }
            cout << ans+sz[i] << endl;
        }
    }

    return 0;
}

