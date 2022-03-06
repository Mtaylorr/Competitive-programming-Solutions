#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 +7 ;


int s,l,n;
int u,v;
vector<int> adj[N];
unordered_map<string,int> id;
string decode[250];
string t;
string p;
vector<int> ord;
int rnk[250];
int a[N];
bool cmp(int x, int y){
    return decode[x]<decode[y];
}

int tree[202][N];

void upd(int id, int p, int x){
    for(;p<=n;p+=(p)&(-p)){
        tree[id][p]+=x;
    }
}

int get(int id, int p, bool flag){
    int rs=0;
    int rs2=0;
    for(;p;p-=(p)&(-p)){
        rs+=tree[id][p];
        rs2+=flag*tree[s][p];
    }
    return rs-flag*rs2;
}

int getrange(int id, int l, int r, bool flag){
    return get(id,r,flag)-get(id,l-1,flag);
}


void add(int x, int i, int val){
    upd(s,i,val);
    for(auto v:adj[x]){
        upd(v,i,val);
    }
}
bool vis[N];

queue<int> pos[250];

int main()
{
    freopen("input.txt", "r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s >> l >> n;
    for(int i=0;i<s;i++){
        cin >> t;
        id[t]=i;
        decode[i]=t;
        ord.pb(i);
    }
    sort(ord.begin(),ord.end(),cmp);
    for(int i=0;i<ord.size();i++){
        rnk[ord[i]]=i;
    }
    for(int i=0;i<l;i++){
        cin >> t >> p;
        u = id[t];
        v = id[p];
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for(int i=1;i<=n;i++){
        cin >> t;
        a[i]=id[t];
        pos[a[i]].push(i);
        add(a[i],i,1);
    }
    for(int i=1;i<=n;i++){
        if(vis[i])
            continue;
        bool cond=true;
        while(cond){
            cond=false;
            for(int j=0;j<rnk[a[i]];j++){
                int u = ord[j];
                while(!pos[u].empty() && pos[u].front()<i)
                    pos[u].pop();
                while(!pos[u].empty()){
                    int l = pos[u].front();
                    if(getrange(u,i,l-1,1)==0){
                        add(u,l,-1);
                        vis[l]=1;
                        pos[u].pop();
                        cout << decode[u] << " ";
                        cond=true;
                    }else{
                        break;
                    }
                }
                if(cond)
                    break;
            }
        }
        cout << decode[a[i]] << " ";
    }



    return 0;

}
