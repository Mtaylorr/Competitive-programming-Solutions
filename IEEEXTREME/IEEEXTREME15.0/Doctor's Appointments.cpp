// 100%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e5 +5 ;

int t,n;
int l[N], r[N];
set<pair<int,int> > ss;
vector<pair<pair<int,int>,int> > v;

vector<int> ord;
int main(){
    //freopen("input.txt", "r", stdin);
    cin >> t;
    while(t--){
        v.clear();
        ss.clear();
        ord.clear();
        cin >> n ;
        for(int i=0;i<n;i++){
            cin >> l[i] >> r[i];
            v.pb({{l[i],r[i]},i});
        }
        sort(v.begin(),v.end());
        bool cond=true;
        int j=0;
        for(int i=1;i<=n;i++){
            while(j<n && v[j].first.first<=i){
                ss.insert({v[j].first.second,v[j].second});
                j++;
            }

            if(ss.empty()){
                cond=false;
                break;
            }
            if((*ss.begin()).first<i){
                cond=false;
                break;
            }
            ord.pb((*ss.begin()).second);
            ss.erase(ss.begin());
        }
        if(cond){
            for(int i=0;i<n;i++){
                cout << ord[i] +1<< " ";
            }
            cout << endl;
        }else{
            puts("impossible");
        }
    }
    return 0;
}
