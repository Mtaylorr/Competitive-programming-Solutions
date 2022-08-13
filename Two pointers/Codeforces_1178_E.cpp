//https://codeforces.com/problemset/problem/1178/E

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e2 +5 , E = 1<<17;
const int MOD = 1e9 + 7;

string s;
vector<string> strings;
string abc="abc";
int freq[3];

void init(){
    for(int i=0;i<3;i++){
        freq[i]=0;
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s;

    string ansl="";
    string ansr="";
    int l=0;
    int r=s.size()-1;
    while(l<=r){
        if(s[l]==s[r]){
            ansl+=s[l];
            if(l!=r)
                ansr+=s[r];
            l++;r--;
            continue;
        }
        if(s[l]==s[r-1]){
            ansl+=s[l];
            if(l!=r-1){
                ansr+=s[l];
            }
            l++;r-=2;
            continue;
        }
        if(s[l+1]==s[r]){
            ansr+=s[r];
            if(l+1!=r){
                ansl+=s[r];
            }
            r-=1;
            l+=2;
            continue;
        }
        l++;r--;
    }
    reverse(ansr.begin(),ansr.end());
    cout << ansl+ansr << endl;
    return 0;

}
