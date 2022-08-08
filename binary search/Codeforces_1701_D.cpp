//https://codeforces.com/contest/1701/problem/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 + 5 , E = 2e6 + 5;
const int MOD = 1e9 + 7 ;

int n, b[N],a[N];
int l[N], r[N];
vector<int> v;
int t;

int getl(int p, int b){
    int l=1;
    int r=n;
    while(l<r){
        int md = (l+r)/2;
        if(p/md<b){
            r=md-1;
        }else if(p/md>b){
            l=md+1;
        }else{
            r=md;
        }
    }
    return l;
}
int getr(int p, int b){
    int l=1;
    int r=n;
    while(l<r){
        int md = (l+r+1)/2;
        if(p/md<b){
            r=md-1;
        }else if(p/md>b){
            l=md+1;
        }else{
            l=md;
        }
    }
    return l;
}

set<pair<int,int> > ss;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n;
        v.clear();
        for(int i=0;i<n;i++){
            cin >> b[i];
            l[i] = getl(i+1,b[i]);
            r[i] = getr(i+1,b[i]);
            v.pb(i);
        }
        ss.clear();
        sort(v.begin(),v.end(), [](int a, int b){return make_pair(l[a],r[a])<make_pair(l[b],r[b]);});
        int j=0;
        pair<int,int> pa;
        for(int i=1;i<=n;i++){
            while(j<n && l[v[j]]<=i){
                ss.insert({r[v[j]],v[j]});
                j++;
            }
            pa=(*ss.begin());
            a[pa.se]=i;
            ss.erase(ss.begin());

        }
        for(int i=0;i<n;i++){
            cout << a[i] << " ";
        }
        cout << endl;
    }

    return 0;

}
