//https://codeforces.com/problemset/problem/780/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 2000 +5;
const int MOD = 1e9 + 7;

int n;
string s1[N], s2[N];
string tmp1,tmp2;
set<string> st;
map<string ,int> freq;
string ans[N];
bool done[N];
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> s1[i] >> s2[i];
        tmp1="";
        tmp1+=s1[i][0];
        tmp1+=s1[i][1];
        tmp1+=s1[i][2];
        tmp2="";
        tmp2+=s1[i][0];
        tmp2+=s1[i][1];
        tmp2+=s2[i][0];
        s1[i]=tmp1;
        s2[i]=tmp2;
        freq[tmp1]++;
        ans[i]=s1[i];
    }
    int nb=0;
    for(int i=0;i<n;i++){
        if(freq[s1[i]]==1){
            continue;
        }
        if(st.count(s2[i])){
            cout << "NO\n";
            return 0;
        }
        ans[i]=s2[i];
        st.insert(s2[i]);
        done[i]=1;
    }
    for(int j=0;j<n;j++){
        for(int i=0;i<n;i++){
            if(done[i])
                continue;
            if(freq[s1[i]]==1){
                if(st.count(s1[i])){
                    if(st.count(s2[i])){
                        cout << "NO\n";
                        return 0;
                    }
                    ans[i]=s2[i];
                    st.insert(s2[i]);
                    done[i]=1;
                }
            }
        }
    }

    cout << "YES\n";
    for(int i=0;i<n;i++){
        cout << ans[i] << "\n";
    }


    return 0;


}
