// https://codeforces.com/contest/995/problem/C
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


int n;
ll x[N];
ll y[N];
vector<int> v;

int ans[N];

ll add(ll a, ll b, ll c, ll d) {
    return (a + c) * (a + c) + (b + d) * (b + d);
}

ll curx, cury;

int cur[3];
ll par[N][4];
set<int> ss;

int main() {
    FAST;
    //freopen("easy", "r", stdin);
    cin >> n;
    ll mx = 1e12;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        ss.insert(i);
    }
    if (n == 1) {
        cout << 1;
        return 0;
    }
    int j = 0;
    while (ss.size() >= 3) {
       //  where there is at least 3 vectors we take 3
        for (int i = 0; i < 3; i++) {
            cur[i] = (*ss.begin());
            ss.erase(ss.begin());
        }
        bool cond = false;
        for (int i = 0; i < 3; i++) {
            if(cond)
                break;
            for (int k = i + 1; k < 3; k++) {
                if(cond)
                    break;
                ll xx = cur[i];
                ll yy = cur[k];
                ll v1 = add(x[xx], y[xx], x[yy], y[yy]); // xx + yy

                if (v1 <= mx) {
                  //  cout << xx <<  " " << yy << endl;
                    par[j][0] = xx;
                    par[j][1] = 0;
                    par[j][2] = yy;
                    par[j][3] = 0;
                    cond = true;
                    ss.insert(xx);
                    ss.insert(cur[0]+cur[1]+cur[2]-(xx+yy));
                    x[xx]+=x[yy];
                    y[xx]+=y[yy];
                    break;
                }
                ll v2 = add(x[xx], y[xx], -x[yy], -y[yy]); // xx-yy
                if (v2 <= mx) {
                    //cout << xx <<  " " << yy << endl;
                    par[j][0] = xx;
                    par[j][1] = 0;
                    par[j][2] = yy;
                    par[j][3] = 1;
                    cond=true;
                    x[xx]-=x[yy];
                    y[xx]-=y[yy];
                    ss.insert(xx);
                    ss.insert(cur[0]+cur[1]+cur[2]-(xx+yy));
                    break;
                }
            }
        }
        j++;
    }
  // if 2 are left then we combine them
    if(ss.size()==2){
        for (int i = 0; i < 2; i++) {
            cur[i] = (*ss.begin());
            ss.erase(ss.begin());
        }
        bool cond = false;
        for (int i = 0; i < 2; i++) {
            for (int k = i + 1; k < 2; k++) {
                if(cond)
                    break;
                ll xx = cur[i];
                ll yy = cur[k];
                ll v1 = add(x[xx], y[xx], x[yy], y[yy]);

                if (v1 < mx*1.5*1.5) {
                    par[j][0] = xx;
                    par[j][1] = 0;
                    par[j][2] = yy;
                    par[j][3] = 0;
                    cond = true;
                    ss.insert(xx);
                    x[xx]+=x[yy];
                    y[xx]+=y[yy];
                    break;
                }
                ll v2 = add(x[xx], y[xx], -x[yy], -y[yy]);
                if (v2 < mx*1.5*1.5) {
                    par[j][0] = xx;
                    par[j][1] = 0;
                    par[j][2] = yy;
                    par[j][3] = 1;
                    cond=true;
                    x[xx]-=x[yy];
                    y[xx]-=y[yy];
                    ss.insert(xx);
                    break;
                }
            }
        }
        j++;
    }

    for(int i=j-1;i>=0;i--){
        int xx = par[i][0]; //  the first vector combined at step i 
        int yy = par[i][2];  //  the second vector combined at step i 
        ans[yy]^=ans[xx]; //  update the state of the second since the first is the parent 
        // update the current vectors
        ans[yy]^=par[i][3]; 
        ans[xx]^=par[i][1];
    }
    for(int i=0;i<n;i++){
        cout << (ans[i]==0?1:-1) << " ";
    }


    return 0;
}
