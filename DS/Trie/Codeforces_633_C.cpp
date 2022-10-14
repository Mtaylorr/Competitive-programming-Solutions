//https://codeforces.com/problemset/problem/633/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;

int nxt[N];
int dp[N];
int n,m;
string t;
string s[N];
int ndcnt=0;
int trie[E][32];
int isend[E];

int addnode(){
    memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
    isend[ndcnt]=-1;
    return ndcnt++;
}

void init(){
    ndcnt=0;
    addnode();
}

void ins(string &s, int p){
    int cur=0;
    for(int j=0;j<s.size();j++) {
        int id = tolower(s[j]) - 'a';
        int &nx = trie[cur][id];
        if (nx == -1) {
            nx = addnode();
        }
        cur = trie[cur][id];
    }
    isend[cur]=p;
}

int solve(int p){
    if(p>=n){
        return 1;
    }
    if(dp[p]!=-1){
        return dp[p];
    }
    int cur=0;
    for(int j=p;j<min(j+1000, n);j++){
        int id = t[j]-'a';
        int nx = trie[cur][id];
        if(nx==-1)
            break;
        cur=trie[cur][id];
        if(isend[cur]!=-1 && solve(j+1)){
            nxt[p]=j;
            return dp[p]=1;
        }
    }
    return dp[p]=0;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    init();
    cin >> n;
    cin >> t;
    cin >> m;
    for(int i=0;i<m;i++){
        cin >> s[i];
        ins(s[i],i);
    }
    reverse(t.begin(),t.end());
    bool rs = solve(0);
    int l=0;
    vector<int> ans;
    while(l<n){
        int r = nxt[l];
        int cur=0;
        for(int j=l;j<=r;j++){
            cur=trie[cur][t[j]-'a'];
        }
        ans.pb(isend[cur]);
        l=r+1;
    }
    for(int i=ans.size()-1;i>=0;i--){
        cout << s[ans[i]] << " ";
    }

    return 0;

}
