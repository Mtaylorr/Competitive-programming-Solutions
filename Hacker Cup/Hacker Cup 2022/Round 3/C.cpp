#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e6 + 100, M = 1000 + 5, E = 2e6 + 5;
const int MOD[] = {(int)(1e9 + 7) , (int)(1e9 + 9)};
const double eps = 1e-7;
const int BASE[] = {31, 17};

int T;
ll po[2][N];
pair<int,int>  hv[N], hw[N];
map<pair<int,int>,int> freq;
int n,q;
int l;
string v[N], w[N];


int mul(int u , int v, int mod=MOD[0]){
    return ((u%mod)*1ll*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD[0]){
    return ((u%mod)+0ll+(v%mod)+mod)%mod;
}

int sub(int u, int v , int mod=MOD[0]){
    return ((u%mod)+0ll-(v%mod)+mod)%mod;
}

string meta= "meta";

pair<int,int> gethash(string &s){
    int h[]={0,0};
    for(int i=s.size()-1;i>=0;i--){
        for(int j=0;j<2;j++){
            h[j]=add(mul(h[j],BASE[j]),(s[i]-'a') +1 );
        }

    }
    return {h[0], h[1]};
}

int main() {
    //freopen("input.txt", "r", stdin);
    freopen("second_mistake_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    for(int tt=1;tt<=T;tt++){
        freq.clear();
        cout << "Case #" << tt << ": ";
        cin >> n;
        for(int i=0;i<n;i++){
            cin >> v[i];
            hv[i]=gethash(v[i]);
        }
        cin >> q;
        for(int i=0;i<q;i++){
            cin >> w[i];
            hw[i]=gethash(w[i]);
        }
        l=v[0].size();
        po[0][0]=po[1][0]=1;
        for(int j=0;j<2;j++)
        for(int i=1;i<=l;i++){
            po[j][i]=mul(po[j][i-1],BASE[j]);
        }
        for(int i=0;i<q;i++){
            for(int j=0;j<l;j++){
                for(int k=0;k<4;k++){
                    if(w[i][j]==meta[k]){
                        continue;
                    }
                    pair<int,int> curh = hw[i];
                    int h[2]={0,0};
                    h[0]=curh.fi;
                    h[1]=curh.se;
                    int diff = -((w[i][j]-'a' )+1)+((meta[k]-'a')+1);
                    for(int o=0;o<2;o++){
                        h[o]=add(h[o], mul(po[o][j],diff));
                    }
                    curh = {h[0],h[1]};
                    freq[curh]++;
                }
            }
        }
        ll ans=0;
        if(l>=2) {
            for (int j = 0; j < l - 1; j++) {
                for(int i=0;i<q;i++){
                        for(int k=0;k<4;k++){
                            if(w[i][j]==meta[k]){
                                continue;
                            }
                            pair<int,int> curh = hw[i];
                            int h[2]={0,0};
                            h[0]=curh.fi;
                            h[1]=curh.se;
                            int diff = -((w[i][j]-'a' )+1)+((meta[k]-'a')+1);
                            for(int o=0;o<2;o++){
                                h[o]=add(h[o], mul(po[o][j],diff));
                            }
                            curh = {h[0],h[1]};
                            freq[curh]--;
                        }

                }
                for(int i=0;i<n;i++){
                    for(int k=0;k<4;k++){
                        if(v[i][j]==meta[k]){
                            continue;
                        }
                        pair<int,int> curh = hv[i];
                        int h[2]={0,0};
                        h[0]=curh.fi;
                        h[1]=curh.se;
                        int diff = -((v[i][j]-'a' )+1)+((meta[k]-'a')+1);
                        for(int o=0;o<2;o++){
                            h[o]=add(h[o], mul(po[o][j],diff));
                        }
                        curh = {h[0],h[1]};
                        ans+=freq[curh];
                    }

                }
            }
        }
        cout << ans << "\n";
    }



    return 0;

}
