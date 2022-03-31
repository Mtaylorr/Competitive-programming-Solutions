//https://codeforces.com/problemset/problem/508/D

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 + 7 ;

#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])


int n,in[3845],out[3845];
string s;
bool vis[N];
vector<int> adj[3845];
int code[200];
int decode[200];
vector<int> euler;


void dfs(int u){
    while(adj[u].size()){
        int v = adj[u].back();
        adj[u].pop_back();
        dfs(v);
    }
    euler.pb(u);
}




int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    int cn=0;
    for(int i=0;i<=122;i++){
        char c = char(i);
        if(c<='Z' && c>='A'){
            code[i]=cn;
            decode[cn]=i;
            cn++;
        }
        if(c<='z' && c>='a'){
            code[i]=cn;
            decode[cn]=i;
            cn++;
        }
        if(c<='9' && c>='0'){
            code[i]=cn;
            decode[cn]=i;
            cn++;
        }
    }
    for(int i=0;i<n;i++){
        cin >> s;
        int x = code[s[0]]*62+code[s[1]];
        int y= code[s[1]]*62+code[s[2]];
        //cout << x << " " << y << endl;
        adj[x].pb(y);
        in[y]++;
        out[x]++;
    }
    int nb1=0;
    int nb2=0;
    int x=0;
    for(int i=0;i<3845;i++){
        if(in[i]==out[i])
            continue;
        if(abs(in[i]-out[i])!=1)
        {
            puts("NO");
            return 0;
        }
        if(out[i]>in[i]){
            nb1++;
            x=i;
        }else if(out[i]<in[i]){
            nb2++;
        }
    }
    if(nb1>=2 || nb2>=2 || (nb1+nb2)%2!=0){
        puts("NO");
        return 0;
    }
    if(nb1==0){
        for(int i=0;i<3845;i++){
            if(in[i]){
                x=i;
                break;
            }
        }
    }
    dfs(x);
    euler.pop_back();
    if(euler.size()!=n){
        puts("NO");
        return 0;
    }
    cout << "YES\n";
    cout << char(decode[x/62]) << char(decode[x%62]);
    reverse(euler.begin(),euler.end());
    dfs(x);
    for(int i=0;i<n;i++){
        cout <<  char(decode[euler[i]%62]);
    }



    return 0;

}
