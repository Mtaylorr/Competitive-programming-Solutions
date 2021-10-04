//https://www.spoj.com/problems/SUB_PROB/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 2e6 + 5, alpha=128;
char s[N], str[1005];

int trie[N][alpha],ids[N],nxtId[N],F[N], szs[N];
char child[N][alpha];
int ndcnt;
int myId[N];

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

int ins(const char * str, int id){
    int cur;
    for(cur=0;*str;str++){
        int &r = trie[cur][*str];
        if(r==-1){
            r=addnode();
            child[cur][szs[cur]++]=*str;
        }
        cur=r;
    }
    if(ids[cur]==-1)
        ids[cur]=id;

    return ids[cur];
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
            F[r]=nxtId[r]=0;
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
            F[r] = nxtId[r] = getNext(f, c);
            q.push(r);
        }
    }
}

int getNextId(int cur){
    if(cur==0)
        return cur;
    int &r = nxtId[cur];
    if(ids[r]!=-1)
        return cur;
    return r = getNextId(r);
}

int ans[N];

void match(){
    int cur=0;
    for(int i=0;s[i];i++){
        cur = getNext(cur,s[i]);
        for(int j=cur;j;j=getNextId(j)){
            if(ids[j]!=-1)
                ans[ids[j]]=1;
        }
    }
}
int n;


int main(){
    freopen("input.txt", "r", stdin);
    scanf("%s",s);
    scanf("%d",&n);
    init();
    for(int i=0;i<n;i++){
        scanf("%s",str);
        myId[i]=ins(str,i);
    }
    buildFail();
    match();
    for(int i=0;i<n;i++){
        printf((ans[myId[i]]?"Y\n":"N\n"));
    }
    return 0;
}

