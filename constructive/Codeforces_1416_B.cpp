//https://codeforces.com/problemset/problem/1416/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 6e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int n, a[N],t;
vector<pair<pair<int,int>,int> > ans;


int main() {
    freopen("input.txt", "r", stdin);
    //freopen("game.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        ans.clear();
        cin >> n;
        int sum=0;
        for(int i=0;i<n;i++){
            cin >> a[i];
            sum+=a[i];
        }
        if(sum%n){
            cout << -1 << endl;
            continue;
        }
        int target = sum/n;
        for(int i=1;i<n;i++){
            int _x = ((i+1)-(a[i]%(i+1)))%(i+1);
            if(_x){
                ans.pb({{1,i+1},_x});
                a[i]+=_x;
                a[0]-=_x;
            }
            _x = a[i]/(i+1);
            if(_x){
                ans.pb({{i+1,1},_x});
                a[i]-=_x*(i+1);
                a[0]+=_x*(i+1);
            }
        }
        for(int i=1;i<n;i++){
            ans.pb({{1,i+1},target});
        }
        cout << ans.size() << endl;
        for(auto u:ans){
            cout << u.fi.fi << " " << u.fi.se << " " << u.se << endl;
        }
    }
    return 0;

}
