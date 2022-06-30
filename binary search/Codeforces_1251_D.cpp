//https://codeforces.com/problemset/problem/1251/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int t,n;
ll s;
int l[N],r[N];
vector<int> ls;
bool vis[N];
vector<int> tmp;
map<int,int> freq;
vector<pair<int,int> > ranges;

bool ok(int u){
    for(int i=0;i<n;i++){
        vis[i]=0;
    }
    int nb=0;
    ll sum=0;
    for(int i=0;i<n;i++){
        if(l[i]>u){
            nb++;
            sum+=l[i];
        }
    }
    if(nb>n/2){
        return 0;
    }
    tmp.clear();
    for(int i=0;i<n;i++){
        if(l[i]<=u && r[i]>=u){
            tmp.pb(l[i]);
        }
    }
    sort(tmp.rbegin(), tmp.rend());
    for(int i=0;i<tmp.size();i++){
        if(nb<(n/2 +1)){
            sum+=u;
            nb++;
        }else{
            sum+=tmp[i];
        }
    }
    for(int i=0;i<n;i++){
        if(r[i]<u){
            sum+=l[i];
        }
    }
    return nb==(n/2+1) && sum<=s;
}

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("game.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        ls.clear();
        cin >> n >> s;
        for(int i=0;i<n;i++){
            cin >> l[i]  >> r[i];
            ls.pb(l[i]);
        }
        sort(ls.begin(),ls.end());
        int le = ls[n/2];
        int rg = 1e9;
        while(le<rg){
            int md = (le+rg+1)/2;
            if(ok(md)){
                le=md;
            }else{
                rg=md-1;
            }
        }
        cout << le << endl;
    }
    return 0;

}
