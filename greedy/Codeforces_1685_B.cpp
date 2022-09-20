//https://codeforces.com/problemset/problem/1685/B

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7 ;

int t;
int a,b,c,d;
string s;
int n;
int freq[2];
bool done[N];
vector<int> nb[3];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >>  t;
    while(t--){
        cin >> a >> b >> c >> d;
        cin >> s;
        n=s.size();
        freq[0]=freq[1]=0;
        for(int i=0;i<3;i++){
            nb[i].clear();
        }
        for(auto c:s){
            freq[c-'A']++;
        }
        if((freq[0]-c-d!=a) || (freq[1]-c-d!=b)){
            cout <<"NO\n";
            continue;
        }
        int bef =-1;
        int cur=0;
        for(int i=0;i<n;i++){
            int x = s[i]-'A';
            if(x!=bef){
                cur++;
            }else{
                if(cur>=2){
                    if(cur%2==1){
                        nb[2].pb(cur/2);
                    }else{
                        nb[1-x].pb(cur/2);
                    }
                }
                cur=1;
            }
            bef=x;
        }
        if(cur>=2){
            if(cur%2==1){
                nb[2].pb(cur/2);
            }else{
                nb[1-bef].pb(cur/2);
            }
        }
        for(int i=0;i<3;i++)
        sort(nb[i].rbegin(), nb[i].rend());

        while(c && nb[0].size()){
            int y = nb[0].back();
            int x = min(y,c);
            c-=x;
            y-=x;
            if(y){
                nb[0][nb[0].size()-1]=y;
            }else{
                nb[0].pop_back();
            }
        }
        while(d && nb[1].size()){
            int y = nb[1].back();
            int x = min(y,d);
            d-=x;
            y-=x;
            if(y){
                nb[1][nb[1].size()-1]=y;
            }else{
                nb[1].pop_back();
            }
        }
        for(auto &u:nb[0]){
            --u;
        }
        for(auto &u:nb[1]){
            --u;
        }
        while(d && nb[0].size()){
            int y = nb[0].back();
            if(y<=0){
                nb[0].pop_back();
                continue;
            }
            int x = min(y,d);
            d-=x;
            y-=x;
            if(y){
                nb[0][nb[0].size()-1]=y;
            }else{
                nb[0].pop_back();
            }
        }
        while(c && nb[1].size()){
            int y = nb[1].back();
            if(y<=0){
                nb[1].pop_back();
                continue;
            }
            int x = min(y,c);
            c-=x;
            y-=x;
            if(y){
                nb[1][nb[1].size()-1]=y;
            }else{
                nb[1].pop_back();
            }
        }
        int sm=0;
        for(auto u:nb[2]){
            sm+=u;
        }

        if(c+d<=sm){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }
    return 0;
}
