//https://codeforces.com/contest/1721/problem/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e6 + 5, E = 1 << 17;
const int MOD =  998244353;


string s;
string t;
int q;
int F[N];
string pat;

int dp[N][26];

int getNextLen(int len , char c){
    int cur_len = len;
    if(len<s.size() && dp[len][c-'a']!=-1){
        return dp[len][c-'a'];
    }
    if(pat[len]==c){
        len++;
        if(cur_len<s.size()){
            return dp[cur_len][c-'a']=len;
        }
        return len;
    }
    if(len){
        int to_return = getNextLen(F[len-1], c);
        if(cur_len<s.size()){
            return dp[cur_len][c-'a']=to_return;
        }
        return to_return;
    }
    if(cur_len<s.size()){
        return dp[cur_len][c-'a']=0;
    }
    return 0;

}

void compute_f(int j=1){
    F[0]=0;
    for(int i=j;pat[i]!='#';i++){
        F[i]=getNextLen(F[i-1], pat[i]);
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    memset(dp, -1, sizeof(dp));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s;
    pat=s;
    pat+="#";
    compute_f();
    pat.pop_back();
    cin >> q;
    while(q--){
        cin >> t;
        pat+=t;
        pat+='#';
        compute_f(s.size());
        for(int i=s.size();i<s.size()+t.size();i++){
            cout << F[i] << " ";
        }
        cout << endl;
        for(int j=0;j<=t.size();j++){
            pat.pop_back();
        }
    }

    return 0;
}
