//https://codeforces.com/problemset/problem/1482/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5, E = 1 << 17;
const int MOD =  998244353;

int t;
int n;
int a[N];
deque<int> val[N];
int l[N], r[N];
int id[N];
vector<int> ans;

void init(){
    ans.clear();
    for(int i=0;i<n;i++){
        val[i].clear();
        val[i].pb(i);
        id[i]=i;
        l[i]=i;
        r[i]=i;
    }
}

int getid(int u){
    return (id[u]==u?id[u]:id[u]=getid(id[u]));
}

void uni(int u, int v){
    u=getid(u);
    v=getid(v);
    if(u==v)
        return ;
    if(val[v].size()<=val[u].size()){
        id[v]=u;
        r[u]=r[v];
        while(!val[v].empty()){
            val[u].push_back(val[v].front());
            val[v].pop_front();
        }
    }else{
        id[u]=v;
        l[v]=l[u];
        while(!val[u].empty()){
            val[v].push_front(val[u].back());
            val[u].pop_back();
        }
    }
}

void rem_left(int x){
    x=getid(x);
    ans.pb(val[x].front());
    val[getid(x)].pop_front();
}

int get_right(int x){
    return val[x].back();
}

int get_left(int x){
    return val[x].front();
}



int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n;
        for(int i=0;i<n;i++){
            cin >> a[i];
        }
        init();
        int i=0;
        while(1){
            int x = getid(i);
            if(l[x]==(r[x]+1)%n && (val[x].size()==0 || (__gcd(a[get_left(x)], a[get_right(x)]))!=1)){
                break;
            }
            int lf = get_right(x);
            int nx = (r[x]+1)%n;
            nx = getid(nx);
            int rg = get_left(nx);
            if(__gcd(a[lf],a[rg])!=1){
                uni(x,nx);
                i=nx;
            }else{
                rem_left(nx);
                if(val[nx].size()==0){
                    uni(x,nx);
                    i=(r[nx]+1)%n;
                }else{
                    i=nx;
                }

            }
        }
        cout << ans.size() << " ";
        for(auto u:ans){
            cout << u+1 << " ";
        }
        cout << endl;
    }

    return 0;
}
