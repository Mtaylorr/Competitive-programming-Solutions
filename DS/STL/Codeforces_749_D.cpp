//https://codeforces.com/problemset/problem/749/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 5e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 998244353   ;
const double eps = 1e-7;


int n,k,q;
int a[N],b[N];
int l[N];
vector<int> pos[N];
set<pair<int,int> > st;


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
        pos[a[i]].pb(i);
    }
    for(int i=1;i<=n;i++){
        if(pos[i].size()){
            st.insert({-pos[i].back(),i});
        }
    }
    cin >> q;
    while(q--){
        cin >> k ;
        for(int i=0;i<k;i++){
            cin >> l[i];
            if(pos[l[i]].size()){
                st.erase({-pos[l[i]].back(),l[i]});
            }
        }
        if(st.size()==0){
            cout << 0 << " "<<  0 << "\n";
        }else{
            pair<int,int>  p = *st.begin();
            st.erase(st.begin());
            int x = -1;
            if(st.size()){
                x=-(*st.begin()).fi;
            }
            int y = upper_bound(pos[p.se].begin(), pos[p.se].end(),x)-pos[p.se].begin();
            cout << p.se << " " << b[pos[p.se][y]] << "\n";
            st.insert(p);
        }

        for(int i=0;i<k;i++){
            if(pos[l[i]].size()){
                st.insert({-pos[l[i]].back(),l[i]});
            }
        }
    }


    return 0;
}
