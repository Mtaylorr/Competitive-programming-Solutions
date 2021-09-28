//https://www.spoj.com/problems/EMOTICON/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 20*102 + 10, alpha = 128;

int trie[N][alpha],ndcnt=0, ids[N], szs[N], myId[N], F[N];
char child[N][alpha];
int isleaf[N];

int n,m;
char str[20];
string s;
int sz;

int addnode(){
    memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
    ids[ndcnt]=-1;
    szs[ndcnt]=0;
    isleaf[ndcnt]=0;
    return ndcnt++;
}

void init(){
    ndcnt=0;
    addnode();
}


void ins(const char * str , int id){
    int cur;
    for(cur=0;*str;str++){
        int & nxt = trie[cur][*str];
        if(nxt==-1){
            nxt=addnode();
            child[cur][szs[cur]++]=*str;
        }
        cur=nxt;
    }
    isleaf[cur]=1;
    ids[cur]=id;
}

int getNext(int f, char c){
    while(trie[f][c]==-1)
        f=F[f];
    return trie[f][c];
}

void buildFail(){
    queue<int> q;
    for(int i=0;i<alpha;i++){
        int &r  = trie[0][i];
        if(r==-1){
            r=0;
        }else{
            myId[r]=F[r]=0;
            q.push(r);
        }
    }

    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(int i=0;i<szs[cur];i++){
            char c = child[cur][i];
            int r = trie[cur][c];
            int f = getNext(F[cur], c);
            myId[r] = F[r] = f;
            isleaf[r] = isleaf[r] || isleaf[f];
            q.push(r);
        }
    }
}


int main(){
    while(1){
        init();
        cin >> n >> m;
        if(n==0 && m==0)
            return 0;
        for(int i=0;i<n;i++){
            cin >> str;
            ins(str,i);
        }
        buildFail();

        int res=0;
        int bef=0;
        int ans=0;
        cin.ignore();
        for(int i=0;i<m;i++){
            getline(cin ,s);
            int cur=0;
            sz=s.size();
            for(auto u:s){
                cur = getNext(cur, u);
                if(isleaf[cur]){
                    ans++;
                    cur=0;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

