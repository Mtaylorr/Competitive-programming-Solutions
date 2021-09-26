//https://vjudge.net/problem/UVA-10679
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N  = 1e6+2, alpha=128;

int trie[N][alpha], ndcnt, szs[N], F[N], ids[N], nxtId[N];
char children[N][alpha];

int t,n;
char str[N];
char s[(int)1e3+5];


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

vector<vector<int> > match(char *str, int cnt){
    vector<vector<int> > v(cnt);
    for(int cur=0, i=0;str[i];i++){
        cur = getNext(cur, str[i]);
        for(int j=cur;j;j=getNxtId(j)){
            if(ids[j]!=-1){
                v[ids[j]].pb(i);
            }
        }
    }
    return v;
}

int newids[N];

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%s",str);
        scanf("%d",&n);
        init();
        for(int i=0;i<n;i++){
            scanf("%s",s);
            newids[i] = ins(s, i);
        }
        buildFail();
        vector<vector<int> > res = match(str, n);
        for(int i=0;i<n;i++){
            if(res[newids[i]].size()){
                puts("y");
            }else{
                puts("n");
            }
        }
    }
    return 0;
}

