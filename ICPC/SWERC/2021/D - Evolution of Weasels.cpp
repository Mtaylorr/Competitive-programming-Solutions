#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E= 2e5+5;
const int MOD = 998244353 ;

int t;
string u, v;
string tmp1, tmp2;
int cnt;


void process(){
    bool cond=true;
    while(cond && tmp1.size()>=2){
        cond=false;
        for(int i=1;i<tmp1.size();i++){
            if(tmp1[i]==tmp1[i-1]){
                cond=true;
                tmp1 = tmp1.substr(0, i-1) + tmp1.substr(i+1, tmp1.size()-i);
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    cin >> t;
    while(t--){
        cin >> u;
        cin >> v;
        cnt=0;
        for(int i=0;i<u.size();i++){
            cnt+=(u[i]=='B');
        }
        for(int i=0;i<v.size();i++){
            cnt+=(v[i]=='B');
        }
        if(cnt%2!=0){
            puts("NO");
            continue;
        }
        tmp1="";
        tmp2="";
        for(auto c:u){
            if(c!='B')
                tmp1+=c;
        }
        for(auto c:v){
            if(c!='B')
                tmp2+=c;
        }
        process();
        u=tmp1;
        tmp1=tmp2;
        process();
        v=tmp1;
        if(u==v){
            puts("YES");
        }else{
            puts("NO");
        }
    }


    return 0;

}
