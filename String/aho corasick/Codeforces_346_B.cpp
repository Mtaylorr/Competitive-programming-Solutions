//https://codeforces.com/problemset/problem/346/B

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 105, alpha=128;
char str[N];
char s1[N], s2[N];

int trie[N][alpha],ids[N],F[N], szs[N];
bool isleaf[N];
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
            q.push(r);
        }
    }
}

int dp[105][105][105];
int n,m;

int solve(int x=0, int y=0,  int cur=0){
    if(isleaf[cur])
        return dp[x][y][cur]=-1e7;
    if(x>=n || y>=m){
        return dp[x][y][cur]=0;
    }
    if(dp[x][y][cur]!=-1)
        return dp[x][y][cur];
    int res=max(solve(x+1, y, cur), solve(x,y+1,cur));
    if(s1[x]==s2[y]){
        res=max(res, 1+solve(x+1, y+1, getNext(cur, s1[x])));
    }
    return dp[x][y][cur]=res;
}


int main(){
    freopen("input.txt", "r", stdin);
    memset(dp, -1, sizeof(dp));
    scanf("%s",s1);
    scanf("%s",s2);
    n=strlen(s1);
    m=strlen(s2);
    scanf("%s",str);
    init();
    ins(str);
    buildFail();
    int x = solve();
    int i=0;
    int j=0;
    int cur=0;
    if(x==0){
        cout << 0;
        return 0;
    }
    while(i<n && j<m){

        int nxcur = getNext(cur, s1[i]);
        if(s1[i]==s2[j] && dp[i+1][j+1][nxcur]==x-1){
            cout << s1[i];
            x--;
            cur=nxcur;
            i++;j++;
        }else if(dp[i][j+1][cur]==x)
            j++;
        else
            i++;
    }
    return 0;
}

