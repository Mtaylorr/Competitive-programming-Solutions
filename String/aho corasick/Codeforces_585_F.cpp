//https://codeforces.com/contest/585/problem/F

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e5+7, alpha=128;
const int MOD = 1e9 +  7;
char s[N];
char x[N], y[N];
char str[N];

int trie[N][alpha],ids[N],F[N],nxtId[N], szs[N];
bool isleaf[N];
char child[N][alpha];
int ndcnt;
int d;

int k[N];

int addnode(){
    memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
    szs[ndcnt]=0;
    ids[ndcnt]=-1;
    isleaf[ndcnt]=0;
    return ndcnt++;
}

void init(){
    ndcnt=0;
    addnode();
}

void ins(const char * str){
    int cur;
    for(cur=0;*str;str++){
        int &r = trie[cur][*str];
        if(r==-1){
            r=addnode();
            child[cur][szs[cur]++]=*str;
        }
        cur=r;
    }
    isleaf[cur]=1;
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
            F[r]=0;
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
            F[r] = getNext(f, c);
            isleaf[r]=(isleaf[r]|| isleaf[F[r]]);
            q.push(r);
        }
    }
}

int  add(ll u, ll v, ll mod=MOD){
	return ((u%mod)+(v%mod)+mod)%mod;
}
int d2;
int n;

int dp[51][50*1005][2][2][2];

int solve(int i=0, int v=0 , bool b1=1, bool b2=1, bool b=0){
    if(i>=d)
        return b;
    int &r = dp[i][v][b1][b2][b];
    if(r!=-1)
        return r;
    r=0;
    char mn = '0';
    char mx = '9';
    if(b1==1)
        mn=x[i];
    if(b2==1)
        mx=y[i];
    for(char c=mn;c<=mx;c++){
        int nexcur = getNext(v, c);
        r=add(r, solve(i+1, nexcur, b1&&(c==mn) , b2&&(c==mx), b || (isleaf[nexcur])));
    }
    return r;
}

int main(){
    freopen("input.txt", "r", stdin);
    memset(dp, -1, sizeof(dp));
    scanf("%s",s);
    n=strlen(s);
    scanf("%s",x);
    scanf("%s",y);
    d=strlen(x);
    d2 = d/2;
    init();
    for(int i=0;i+d/2<=n;i++){
        for(int j=0;j<d2;j++){
            str[j]=s[i+j];
        }
        str[d/2]=0;
        ins(str);
    }
    buildFail();
    printf("%d\n",solve());


    return 0;
}

