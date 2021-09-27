//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2463
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N =20*20+10, alpha=128;
int ndcnt, szs[N], ids[N];
int trie[N][alpha];
char child[N][alpha];
int F[N], nxtId[N];
double prob[alpha];
char str[105];
bool isleaf[N];
vector<char> avchars;

int addnode(){
    memset(trie[ndcnt],-1, sizeof(trie[ndcnt]));
    szs[ndcnt]=0;
    isleaf[ndcnt]=0;
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
        int & nxt = trie[cur][*str];
        if(nxt==-1){
            nxt=addnode();
            child[cur][szs[cur]++]=*str;
        }
        cur = nxt;
    }
    if(ids[cur]==-1)
        ids[cur]=id;
    return ids[cur];
}

int getNext(int f, char c){
    while(trie[f][c]==-1)
        f=F[f];
    f=trie[f][c];
    return f;
}



void buildFail(){
    queue<int> q;
    for(int i=0;i<alpha;i++){
        int & nxt = trie[0][i];
        if(nxt!=-1){
            F[nxt]=0;
            nxtId[nxt]=0;
            q.push(nxt);
        }else{
            nxt = 0;
        }
    }
    while(q.size()){
        int cur = q.front();
        q.pop();
        for(int i=0;i<szs[cur];i++){
            int nxt = trie[cur][child[cur][i]];
            nxtId[nxt]=F[nxt] = getNext(F[cur], child[cur][i]);
            q.push(nxt);
        }
    }
}

int getNextId(int cur){
    if(cur==0)
        return cur;
    int &nxt = nxtId[cur];
    if(ids[nxt]!=-1)
        return nxt;
    return nxt =getNextId(nxt);
}


int t, k,n,l;
char c;
double dp[N][102];
bool vis[N][102];

double dfs(int cur=0, int rem=l){
    if(isleaf[cur])
        return 0.0;
    if(rem==0)
        return 1.0;
    if(vis[cur][rem]){
        return dp[cur][rem];
    }
    vis[cur][rem]=1;
    double res=0;
    for(auto c : avchars){
        res += prob[c] * dfs(getNext(cur,c), rem-1);
    }
    return dp[cur][rem]=res;
}



double p;

int main(){
    cout << fixed << setprecision(6);
    cin >> t;
    int tt=0;
    while(t--){
        memset(vis,0,sizeof(vis));
        init();
        avchars.clear();
        cin >> k;
        for(int i=0;i<k;i++){
           cin >> str;
            ins(str,i);
        }
        buildFail();
        for(int i=1;i<ndcnt;i++){
            for(int j=i;j;j=getNextId(j)){
                if(ids[j]!=-1 || isleaf[j]){
                    isleaf[i]=1;
                    break;
                }
            }
        }
        cin >> n;
        for(int i=0;i<n;i++){
            cin >> c >> p;

            prob[c]=p;
            avchars.pb(c);
        }
        scanf("%d",&l);
        long double ans = dfs();
        cout << "Case #"<< ++tt << ": " <<ans << endl;
    }
    return 0;
}

