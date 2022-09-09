//https://codeforces.com/problemset/problem/550/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5, E = 1 << 17;
const int MOD =  998244353 ;


int k,n,m;
vector<pair<int,int> > edges;

void add(int x, int y){
    cout << 2*x +1 << " " << 2*y +1 << "\n";
    cout << 2*x +2 << " " << 2*y +2 << "\n";
    edges.pb({2*x,2*y});
    edges.pb({2*x+1,2*y+1});
}
vector<int>tmp;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> k;
    if(k==1){
        cout << "YES\n";
        cout << 2 << " " << 1 << endl;
        cout << 1 << " " << 2 << endl;
        return 0;
    }
    if(k%2==0){
        cout << "NO\n";
        return 0;
    }
    n = 2*(k + k-1 + (k-1) * (k-1));
    m = (n*k) / 2 ;
    cout << "YES\n";
    cout << n << " " << m << "\n";
    cout << 1 << " "<< 2 << "\n";
    for(int i=0;i<k;i++){
        for(int j=i+1;j<k;j++){
            add(i,j);
        }
    }
    for(int j=k;j<k+(k-1);j++){
        add(j-(k-1),j);
    }
    int st = k+(k-1);
    int cur = 0;
    for(int j=k;j<k+(k-1);j++) {

        tmp.clear();
        for (int o = 0; o < k - 1; o++) {
            add(j, st + cur);
            tmp.pb(st+cur);
            if (cur % (2 * (k - 1)) < k - 1) {
                add(st + cur, st + cur + k - 1);
            }
            cur++;
        }
        for(int i=0;i<tmp.size()-1;i++){
            for(int o=i+1;o<tmp.size();o++){
                add(tmp[i],tmp[o]);
            }
        }
    }
    return 0;
}
