//https://codeforces.com/problemset/problem/803/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7 ;

vector<int> pos;
string s;
int n,k;

bool ok(int u){
    int rs=0;
    for(int i=0;i<pos.size()-1;){
        int j=i+1;
        while(j<pos.size() && pos[j]-pos[i]<=u){
            j++;
        }
        j--;
        if(j>i){
            i=j;
            rs++;
        }else{
            return 0;
        }
    }
    return rs<=k;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> k;
    cin.ignore();
    getline(cin, s);
    pos.pb(-1);
    for(int i=0;i<s.size();i++){
        if(s[i]=='-' || s[i]==' '){
            pos.pb(i);
        }
    }
    pos.pb(s.size()-1);
    int l=0;
    int r = 1e6;
    while(l<r){
        int md  = (l+r)/2;
        if(ok(md)){
            r=md;
        }else{
            l=md+1;
        }
    }
    cout << l << endl;
    return 0;
}
