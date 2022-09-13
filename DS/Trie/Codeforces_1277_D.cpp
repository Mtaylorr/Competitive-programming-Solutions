//https://codeforces.com/problemset/problem/1277/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, E = 5e6;
const int MOD = 1e9 + 7;

int trie[E][2], ndcnt;
bool isEnd[E];
int nb[2][2];
int fix[2][2];
vector<int> pos[2][2];
string a[N];
int t,n;

int addnode(){
    memset(trie[ndcnt],-1, sizeof(trie[ndcnt]));
    isEnd[ndcnt]=0;
    return ndcnt++;
}

void init(){
    memset(nb,0,sizeof(nb));
    memset(fix,0,sizeof(fix));
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            pos[i][j].clear();
        }
    }
    ndcnt=0;
    addnode();
}

void add(string &s){
    int cur=0;
    for(int i=0;i<s.size();i++){
        int d = s[i]-'0';
        int &nx = trie[cur][d];
        if(nx==-1){
            nx=addnode();
        }
        cur=nx;
    }
    isEnd[cur]=1;
}

bool get(string &s){
    int cur=0;
    for(int i=0;i<s.size();i++){
        int d= s[i]-'0';
        int nx = trie[cur][d];
        if(nx==-1)
            return 0;
        cur=nx;
    }
    return isEnd[cur];
}

string tmp;


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        init();
        cin >> n;
        for(int i=0;i<n;i++){
            cin >> a[i];
            add(a[i]);
        }

        for(int i=0;i<n;i++){
            int x = a[i][0]-'0';
            int y = a[i][a[i].size()-1]-'0';
            nb[x][y]++;
            if(x!=y){
                tmp=a[i];
                reverse(tmp.begin(),tmp.end());
                if(get(tmp)==0){
                    pos[x][y].pb(i);
                }else{
                    fix[x][y]++;
                }
            }
        }
        if(nb[0][1]==0 && nb[1][0]==0){
            if(nb[0][0] && nb[1][1]){
                cout << -1 << "\n";
                continue;
            }
            cout << 0 << "\n";
            continue;
        }
        if(abs(nb[0][1]-nb[1][0])<=1){
            cout << 0 << "\n";
        }else if(nb[0][1]>nb[1][0]){
            int needed = (nb[0][1]+nb[1][0])/2 - nb[1][0];
            int possible = nb[0][1]-fix[0][1];
            if(possible>=needed){
                cout << needed << "\n";
                for(int i=0;i<needed;i++){
                    cout << pos[0][1][i]+1 << " ";
                }
                cout << "\n";
            }else{
                cout << -1 << "\n";
                continue;
            }
        }else{
            int needed = (nb[0][1]+nb[1][0])/2 - nb[0][1];
            int possible = nb[1][0]-fix[1][0];
            if(possible>=needed){
                cout << needed << "\n";
                for(int i=0;i<needed;i++){
                    cout << pos[1][0][i]+1 << " ";
                }
                cout << "\n";
            }else{
                cout << -1 << "\n";
                continue;
            }
        }
    }

    return 0;


}
