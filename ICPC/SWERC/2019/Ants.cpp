#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5;
const int MOD = 10567201 ;

int n;
int vis[N];
string s;

int main()
{
    //freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    while(n--){
        cin >> s;
        if(s[0]=='-')
            continue;
        if(s.size()>=8)
            continue;
        int x = stoi(s);
        if(x<=1e6){
            vis[x]=1;
        }
    }
    int j=0;
    while(vis[j])
        j++;
    cout << j << endl;

    return 0;
}
