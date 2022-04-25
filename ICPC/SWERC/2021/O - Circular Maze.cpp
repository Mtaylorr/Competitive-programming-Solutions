#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e6 + 5, E= 2e5+5;
const int MOD = 998244353 ;

int t;
int n;
int teta[N], r[N], r1[N], r2[N], teta1[N], teta2[N];
int iswall[370];
int m,k;
char c;
int comps;
vector<int> points[N];
int t1[N], t2[N];
set<int> rs;
vector<int> adj[N];
bool vis[N];
vector<int> tmp;
bool ininterval(int l, int r, int p){
    if(p>=l && p<r){
        return 1;
    }
    p+=360;
    if(p>=l && p<r){
        return 1;
    }
    return 0;

}

void dfs(int u){
    if(vis[u])
        return ;
    vis[u]=1;
    for(auto v:adj[u]){
        dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    cin >> t;
    while(t--){
        rs.clear();
        cin >> n;
        m=k=0;
        rs.clear();
        comps=0;
        for(int i=0;i<n;i++){
            cin >> c;
            if(c=='C'){
                cin >> r[k] >> teta1[k] >> teta2[k];
                if(teta2[k]<=teta1[k]){
                    teta2[k]+=360;
                }
                rs.insert(r[k]);
                k++;

            }else{
                cin>> r1[m] >> r2[m] >> teta[m];
                m++;
            }
        }
        t1[comps]=0;
        t2[comps]=360;
        for(int i=0;i<360;i++){
            points[comps].pb(i);
        }
        comps++;
        r[k]=22;
        teta1[k]=0;
        teta2[k]=360;
        k++;
        rs.insert(22);
        int lastr=0;
        int lastcompst=0;
        for(auto cur_r:rs){
            memset(iswall, 0, sizeof(iswall));
            for(int i=0;i<k;i++){
                if(r[i]==cur_r){
                    for(int j=teta1[i];j<teta2[i];j++){
                        iswall[j%360]=1;
                    }
                }
            }
            int curcompst=comps;
            tmp.clear();
            for(int i=0;i<m;i++){
                if(r1[i]<=lastr && r2[i]>=cur_r){
                    tmp.pb(teta[i]);
                }
            }
            sort(tmp.begin(), tmp.end());
            if(tmp.size()<=1){
                t1[comps]=0;
                t2[comps]=360;
                for(int j=lastcompst;j<curcompst;j++){
                    for(auto p:points[j]){
                        if(ininterval(t1[comps], t2[comps], p)){
                            adj[comps].pb(j);
                            adj[j].pb(comps);
                            break;
                        }
                    }
                }
                for(int i=t1[comps];i<t2[comps];i++){
                    if(!iswall[i%360]){
                        points[comps].pb(i%360);
                    }
                }
                comps++;
            }else{
                for(int i=0;i<tmp.size();i++){
                    int j=(i+1)%tmp.size();
                    t1[comps]=tmp[i];
                    t2[comps]=tmp[j];
                    if(t2[comps]<=t1[comps]){
                        t2[comps]+=360;
                    }
                    for(int j=lastcompst;j<curcompst;j++){
                        for(auto p:points[j]){
                            if(ininterval(t1[comps], t2[comps], p)){
                                adj[comps].pb(j);
                                adj[j].pb(comps);
                                break;
                            }
                        }
                    }
                    for(int i=t1[comps];i<t2[comps];i++){
                        if(!iswall[i%360]){
                            points[comps].pb(i%360);
                        }
                    }
                    comps++;
                }
            }
            lastcompst=curcompst;
            lastr=cur_r;
        }

        dfs(0);
        if(vis[comps-1]){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
        for(int i=0;i<=comps;i++){
            adj[i].clear();
            points[i].clear();
            vis[i]=0;
        }
    }


    return 0;

}
