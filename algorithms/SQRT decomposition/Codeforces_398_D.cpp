//https://codeforces.com/contest/398/problem/D

#include <bits/stdc++.h>

using namespace std;


#define pb push_back
#define fi first
#define se second

const int B=650;
const int NB = 650;
const int N = 5e4 + 2;
const int Q = 25e4 +2;
int n,m,q;
int o[N];
vector<pair<int,int> > fr;
unordered_set<int> adj[N];
char qt[Q];
int qu[Q], qv[Q];
vector<int> bg;
int bigid[N];
int sum[N];
int mxsz[N];
int dp[NB][N];

void addOnline(int u){
    o[u]=1;
    for(int i=0;i<bg.size();i++){
        if(bg[i]==u)
            continue;
        if(dp[i][u]){
            dp[i][u] = 2;
            sum[bg[i]]++;
        }
    }
}

void addOffline(int u){
    o[u]=0;
    for(int i=0;i<bg.size();i++){
        if(bg[i]==u)
            continue;
        if(dp[i][u]){
            dp[i][u] = 1;
            sum[bg[i]]--;
        }
    }
}

void addFriends(int u,int v){
    if(bigid[u]==-1){
        adj[u].insert(v);
    }else{
        dp[bigid[u]][v]=1+(o[v]);
        sum[u]+=o[v];
    }

    if(bigid[v]==-1){
        adj[v].insert(u);
    }else{
        dp[bigid[v]][u]=1+(o[u]);
        sum[v]+=o[u];
    }
}

void remFriends(int u,int v){
    if(bigid[u]==-1){
        adj[u].erase(v);
    }else{
        dp[bigid[u]][v]=0;
        sum[u]-=o[v];
    }

    if(bigid[v]==-1){
        adj[v].erase(u);
    }else{
        dp[bigid[v]][u]=0;
        sum[v]-=o[u];
    }
}

int countOnline(int u){
    if(bigid[u]==-1){
        int res=0;
        for(auto v:adj[u]){
            res+=(o[v]);
        }
        return res;
    }else{
        return sum[u];
    }
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    int k;
    scanf("%d",&k);
    for(int i=0;i<k;i++){
        int x;
        scanf("%d",&x);
        o[--x]=1;
    }
    for(int i=0;i<m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        --x;--y;
        fr.pb({x,y});
        adj[x].insert(y);
        adj[y].insert(x);
    }

    for(int i=0;i<q;i++){
        cin >> qt[i];
        switch(qt[i]){
        case 'O':
            scanf("%d",&qu[i]);
            --qu[i];
            break;
        case 'F':
            scanf("%d",&qu[i]);
            --qu[i];
            break;
        case 'A':
            scanf("%d%d",&qu[i],&qv[i]);
            --qu[i],--qv[i];
            adj[qu[i]].insert(qv[i]);
            adj[qv[i]].insert(qu[i]);
            mxsz[qu[i]]=max(mxsz[qu[i]],(int) adj[qu[i]].size());
            mxsz[qv[i]]=max(mxsz[qv[i]],(int) adj[qv[i]].size());
            break;
        case 'D':
            scanf("%d%d",&qu[i],&qv[i]);
            --qu[i],--qv[i];
            adj[qu[i]].erase(qv[i]);
            adj[qv[i]].erase(qu[i]);
            break;
        case 'C':
            scanf("%d",&qu[i]);
            --qu[i];
            break;
        }
    }

    for(int i=0;i<n;i++){
        if(mxsz[i]>B){
            bigid[i]=bg.size();
            bg.pb(i);
        }else{
            bigid[i]=-1;
        }
    }
    for(int i=0;i<n;i++){
        adj[i].clear();
    }
    for(int i=0;i<m;i++){
        adj[fr[i].fi].insert(fr[i].se);
        adj[fr[i].se].insert(fr[i].fi);
    }
    for(auto u:bg){
        for(int v:adj[u]){
            if(o[v]){
                dp[bigid[u]][v]=2;
                sum[u]++;
            }else{
                dp[bigid[u]][v]=1;
            }
        }
    }

    for(int i=0;i<q;i++){
        int u = qu[i];
        int v = qv[i];
        switch(qt[i]){
        case 'O':
            addOnline(u);
            break;
        case 'F':
            addOffline(u);
            break;
        case 'A':
            addFriends(u,v);
            break;
        case 'D':
            remFriends(u,v);
            break;
        case 'C':
            printf("%d\n",countOnline(u));
            break;
        }
    }


    return 0;

}
