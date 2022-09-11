//https://codeforces.com/problemset/problem/474/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e6 + 5, E = 1 << 17;
const int MOD =  1e9 +7  ;

ll mul(ll u , ll v, ll mod=MOD){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
    return ((u%mod)-(v%mod)+mod)%mod;
}


int t;
int x[4],y[4],a[4],b[4];

vector<pair<int,int> > pts;
vector<ll> dist;

void rotate(int &x , int & y, int a, int b){
    int dx = x-a;
    int dy = y-b;
    swap(dx,dy);
    dx*=-1;
    x = a+dx;
    y = b+dy;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;

    while(t--){
        for(int i=0;i<4;i++){
            cin >> x[i] >> y[i] >> a[i] >> b[i];
        }
        int ans= 1e9;

        for(int msk=0;msk<(256);msk++){
            int m = msk;
            pts.clear();
            dist.clear();
            int steps = 0;
            for(int i=0;i<4;i++){
                int c = m%4;
                steps+=c;
                m/=4;
                int cx=x[i];
                int cy=y[i];
                for(int j=0;j<c;j++){
                    rotate(cx,cy,a[i],b[i]);
                }
                pts.pb({cx,cy});
            }
            for(int i=0;i<4;i++){
                for(int j=i+1;j<4;j++){
                    ll d = (pts[i].fi-pts[j].fi)*1ll*(pts[i].fi-pts[j].fi)+(pts[i].se-pts[j].se)*1ll*(pts[i].se-pts[j].se);
                    dist.pb(d);
                }
            }
            sort(dist.begin(),dist.end());
            if(dist[0]!=0){
                if(dist[0]==dist[1] &&dist[0]==dist[2]&& dist[0]==dist[3] && dist[4]==dist[5] && dist[3]!=dist[4]){
                    bool cond=true;
                    for(int i=0;i<4;i++){
                        int nb=0;
                        for(int j=0;j<4;j++){
                            if(j==i)
                                continue;
                            ll d = (pts[i].fi-pts[j].fi)*1ll*(pts[i].fi-pts[j].fi)+(pts[i].se-pts[j].se)*1ll*(pts[i].se-pts[j].se);
                            if(d==dist[0]){
                                nb++;
                            }
                        }
                        if(nb!=2){
                            cond=false;
                        }
                    }
                    if(cond){
                        ans=min(ans, steps);
                    }
                }
            }

        }
        if(ans<1e9){
            cout << ans << endl;
        }else{
            cout << -1 << endl;
        }
    }

    return 0;
}
