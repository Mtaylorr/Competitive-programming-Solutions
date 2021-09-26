//https://vjudge.net/problem/UVA-1076
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N  = 10*25+5,M=25+5, alpha=128;

int trie[N][alpha], ndcnt, szs[N], F[N], ids[N], nxtId[N];
ll dp[N][M][1<<10];
char children[N][alpha];

vector<vector<int> > myIds;
char str[M];
int n,m;

char s[M];


int addnode(){
    memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
    ids[ndcnt]=-1;
    szs[ndcnt]=0;
    return ndcnt++;
}

int getNext(int f, char c){
    while(trie[f][c]==-1)
        f=F[f];
    f = trie[f][c];
    return f;
}

void buildFail(){
    queue<int> q;
    for(int i=0;i<alpha;i++){
        int & r = trie[0][i];
        if(~r){
            F[r]=0;
            nxtId[r]=0;
            q.push(r);
        }else{
            r=0;
        }
    }

    while(q.size()){
        int cur = q.front();
        q.pop();
        for(int i=0;i<szs[cur];i++){
            char c = children[cur][i];
            int f = F[cur];
            int &nxt = trie[cur][c];
            nxtId[nxt]=F[nxt]=getNext(f,c);
            q.push(nxt);
        }
    }
}

int ins(const char * str, int id){
    int cur;
    for(cur=0;*str;str++){
        int & nxt = trie[cur][*str];
        if(nxt==-1){
            nxt = addnode();
            children[cur][szs[cur]++]=*str;
        }
        cur=nxt;
    }
    if(ids[cur]==-1)
        ids[cur]=id;
    return ids[cur];
}

void init(){
    ndcnt=0;
    addnode();
}

int getNxtId(int cur){
    if(cur==0)
        return 0;
    int &nxt = nxtId[cur];
    if(ids[nxt]!=-1){
        return nxt;
    }
    return nxt = getNxtId(nxt);
}


long long runDP(int cur=0, int rem=n, int msk = (1<<m)-1){
    if(!rem)
        return !msk;
    long long &res = dp[cur][rem][msk];
    if(res!=-1)
        return res;
    res=0;
    for(char i='a';i<='z';i++){
        int nxt = getNext(cur, i);
        int newMsk = msk;
        for(int j=nxt;j;j=getNxtId(j)){
            if(ids[j]!=-1){
                for(auto k:myIds[ids[j]]){
                    newMsk&=~(1<<k);
                }
            }
        }
        res+=runDP(nxt, rem-1, newMsk);
    }
    return res;
}
void printSol(int cur=0, int rem=n, int msk = (1<<m)-1, const string & s=""){
    if(!rem){
        printf("%s\n",s.c_str());
        return ;
    }
    long long rf = runDP(cur, rem, msk);
    for(char i='a';i<='z';i++){
        int nxt = getNext(cur, i);
        int newMsk = msk;
        for(int j=nxt;j;j=getNxtId(j)){
            if(ids[j]!=-1){
                for(auto k:myIds[ids[j]]){
                    newMsk&=~(1<<k);
                }
            }
        }
        if(runDP(nxt, rem-1, newMsk))
            printSol(nxt, rem-1, newMsk, s+i);
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    int t=1;
    while(1){
        scanf("%d%d",&n,&m);
        if(n==0 && m==0)
            return 0;
        init();
        myIds.clear();
        myIds.resize(m+1);
        memset(dp, -1, sizeof(dp));
        for(int i=0;i<m;i++){
            scanf("%s",s);
            myIds[ins(s,i)].pb(i);
        }
        buildFail();
        ll res=runDP();
        printf("Case %d: %lld suspects\n", t++, res);
        if(res<=42){
            printSol();
        }

    }
    return 0;
}

