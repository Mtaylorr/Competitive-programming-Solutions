//https://www.spoj.com/problems/DQUERY/
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll, ll> pl;
typedef long double ld;
 
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)
 
 
const int N = int(1e6) + 3;
const int MOD = int(1e9) + 7;
 
 
 
int batch;
int l[N],r[N];
int n,q;
vector<int> queries;
int ans[N];
int a[N];
unordered_map<int,int> cnt;
bool cmp(int x, int y){
    if(l[x]/batch!=l[y]/batch){
        return l[x]<l[y];
    }
    return r[x]<r[y];
}
int nb=0;
 
void add(int x){
    cnt[x]++;
    if(cnt[x]==1){
        nb++;
    }
}
 
void rem(int x){
    cnt[x]--;
    if(cnt[x]==0){
        nb--;
    }
}
 
int main() {
    FAST;
    //freopen("easy", "r", stdin);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    batch = sqrt(n);
    cin >> q;
    for(int i=0;i<q;i++){
        queries.pb(i);
        cin >> l[i] >> r[i];
        l[i]--;
        r[i]--;
    }
    sort(all(queries),cmp);
    int curl=0;
    int curr=-1;
    for(auto i:queries){
        while(curr<r[i]){
            curr++;
            add(a[curr]);
        }
        while(curl>l[i]){
            curl--;
            add(a[curl]);
        }
        while(curr>r[i]){
            rem(a[curr]);
            curr--;
        }
        while(curl<l[i]){
            rem(a[curl]);
            curl++;
        }
        ans[i] = nb;
    }
    for(int i=0;i<q;i++){
        cout << ans[i] << "\n";
    }
 
 
    return 0;
} 
