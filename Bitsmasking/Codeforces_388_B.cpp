//https://codeforces.com/problemset/problem/388/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e6 + 5, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int k;
int adj[1005][1005];
int st[50];

void add(int x, int y){
    adj[x][y]=adj[y][x]=1;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> k;
    int cur=2;
    st[1]=2;
    add(1,cur++);
    add(1,cur++);
    int lg=1;
    for(int i=4;i<=k;i*=2){
        lg++;
        st[lg]=cur;
        add(cur,cur-1);
        add(cur, cur-2);
        add(cur+1,cur-1);
        add(cur+1, cur-2);
        cur+=2;
    }
    int len = 32;
    if(k%2){
        int bef = 0;
        for(int i=0;i<len;i++){
            add(bef,cur);
            bef=cur;
            cur++;
        }
        add(bef,1);
    }
    k/=2;
    lg = 1;
    while(k){
        if(k%2){
            int bef = 0;
            for(int i=0;i<len-lg;i++){
                add(bef,cur);
                bef=cur;
                cur++;
            }
            add(bef,st[lg]);
            add(bef, st[lg]+1);
        }
        lg++;
        k/=2;
    }
    cout << cur << endl;
    for(int i=0;i<cur;i++){
        for(int j=0;j<cur;j++){
            cout << "NY"[adj[i][j]];
        }
        cout << "\n";
    }
    return 0;

}
