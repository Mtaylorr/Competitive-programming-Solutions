//https://codeforces.com/problemset/problem/1422/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 + 7;

int n,m;
map<int,int> code, decode;
int sx, sy, fx, fy;
int x[N],y[N];
set<int> ss;
vector<int> vx[N], vy[N];
int visx[N], visy[N];
int cn=1;
int distx[N], disty[N], dist[N];

set<pair<int,int> > pq;


void addx(int i, int d, int u){
    if(i<=0 || i>=cn)
        return ;
    if(visx[i])
        return ;
    int newd = d + abs(decode[i]-decode[u]);
    if(newd<distx[i]){
        distx[i]=newd;
        pq.insert({distx[i],i});
    }
}
void addy(int i, int d, int u){
    if(i<=0 || i>=cn)
        return ;
    if(visy[i])
        return ;
    int newd = d + abs(decode[i]-decode[u]);
    if(newd<disty[i]){
        disty[i]=newd;
        pq.insert({disty[i],-i});
    }
}

void dijk(){
    for(int i=0;i<m;i++){
        dist[i]=2e9+20;
    }
    for(int i=0;i<=cn;i++){
        distx[i]=2e9+20;
        disty[i]=2e9+20;
    }
    dist[m]=0;
    distx[code[sx]]=0;
    disty[code[sy]]=0;
    pq.insert({0,code[sx]});
    pq.insert({0,-code[sy]});
    pair<int,int> pa;
    while(!pq.empty()){
        pa=(*pq.begin());
        pq.erase(pq.begin());
        if(pa.se>0 && visx[pa.se])
            continue;
        if(pa.se<0 && visy[-pa.se])
            continue;

        int p = pa.se;
        int d = pa.fi;
        if(p>0){
            visx[p]=1;
            for(auto u:vx[p]){
                if(disty[code[y[u]]]>distx[p]){
                    disty[code[y[u]]]=distx[p];
                    pq.insert({distx[p],-code[y[u]]});
                }
            }
            addx(p+1, d,p);
            addx(p-1, d,p);
        }
        if(p<0){
            p*=-1;
            visy[p]=1;
            for(auto u:vy[p]){
                if(distx[code[x[u]]]>disty[p]){
                    distx[code[x[u]]]=disty[p];
                    pq.insert({disty[p],code[x[u]]});
                }
            }

            addy(p-1, d,p);
            addy(p+1, d,p);
        }
    }
}

int main() {
    //ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&m);
    scanf("%d%d%d%d",&sx,&sy,&fx,&fy);
    ss.insert(sx);
    ss.insert(sy);
    x[m]=sx;
    y[m]=sy;
    for(int i=0;i<m;i++){
        scanf("%d%d",&x[i],&y[i]);
        ss.insert(x[i]);
        ss.insert(y[i]);
    }
    for(auto u:ss){
        code[u]=cn;
        decode[cn]=u;
        cn++;
    }
    for(int i=0;i<m;i++){
        vx[code[x[i]]].pb(i);
        vy[code[y[i]]].pb(i);
    }

    dijk();
    int ans=2e9 + 20;
    for(int i=0;i<=m;i++){
        dist[i]=min(distx[code[x[i]]], disty[code[y[i]]]);
        ans=min(ans, abs(fx-x[i])+abs(fy-y[i])+dist[i]);
    }
    cout << ans;

    return 0;

}
