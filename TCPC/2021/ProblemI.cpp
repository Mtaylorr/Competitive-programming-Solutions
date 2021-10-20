#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e6+5;

int n;
string a,b;
int cur[N];

int get(char a , char b){
    if(a<=b)
        return b-a;
    return ('z'-a) + (b-'a') + 1;
}

int main(){
    freopen("input.txt", "r", stdin);
    //freopen("cipher.in", "r", stdin);
    getline(cin, a);
    getline(cin, b);
    n= a.size();
    int l;
    for(l=1;l<=n;l++){
        for(int i=0;i<l;i++){
            cur[i]=-1;
        }
        int j=0;
        bool cond=true;
        for(int i=0;i<n;i++){
            if(a[i]==' ')
                continue;
            int x = get(b[i],a[i]);
            if(cur[j]==-1){
                cur[j]=x;
            }else if(cur[j]!=x){
                cond=false;
            }
            j++;
            j%=l;
            if(!cond)
                break;
        }
        if(cond)
            break;
    }
    for(int i=0;i<l;i++){
        cout << char('a'+cur[i]);
    }
    return 0;
}
