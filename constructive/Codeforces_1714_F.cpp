//https://codeforces.com/contest/1714/problem/F
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 4e6 +5 ;
const int MOD = 1e9 + 7;

int t;
int n;
int d;
vector<pair<int,pair<int,int> > > v;


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        v.clear();
        cin >> n;
        cin >> d;
        v.pb({d,{0,1}});
        cin >> d;
        v.pb({d,{1,2}});
        cin >> d;
        v.pb({d,{0,2}});
        sort(v.begin(),v.end());
        int x = v[0].fi + v[1].fi - v[2].fi;
        if(x<0 || x%2){
            cout << "NO\n";
            continue;
        }
        x/=2;
        int y  = v[0].fi-x;
        int z = v[1].fi-x;
        if(x+y+z>n-1){
            cout << "NO\n";
            continue;
        }
        int r1 = 3-v[2].se.fi - v[2].se.se;
        int md = r1;
        int cur=3;
        cout << "YES\n";
        while(x){
            cout << md+1 << " " << cur+1<<endl;
            md=cur;
            cur++;
            x--;
        }

        int r2 = v[0].se.fi+v[0].se.se-r1;
        y--;
        int curmd = md;
        while(y>0){
            cout << curmd+1 << " "<< cur+1 << endl;
            curmd=cur;
            y--;
            cur++;
        }

        cout << r2+1 << " " << curmd+1 << endl;
        int r3 = 3-r1-r2;
        curmd = md;
        z--;
        while(z>0){
            cout << curmd+1 << " "<< cur+1 << endl;
            curmd=cur;
            z--;
            cur++;
        }
        cout << r3+1 << " " << curmd+1 << endl;
        while(cur<n){
            cout << r3+1 << " " << cur+1 << endl;
            cur++;
        }
    }
    return 0;

}
