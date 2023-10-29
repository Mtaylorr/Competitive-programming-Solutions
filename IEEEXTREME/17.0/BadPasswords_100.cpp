#include <bits/stdc++.h>

using namespace std;

int main() {
    //freopen("a.txt", "r", stdin);
    int n;
    cin>>n;
    vector<unordered_set<string>> lists;
    for (int i=0 ; i<n ; i++) {
        int m;
        cin>>m;
        unordered_set<string> v;
        for (int j=0 ; j<m ; j++) {
            string e;
            cin>>e;
            v.insert(e);
        }
        
        lists.push_back(v);
    }
    
    int p;
    cin>>p;
    
    while(p--) {
        string s1, s2;
        cin>>s1;
        cin>>s2;
        int i=0;
        int n = s1.size();
        int m = s2.size();
        
        while(i<min(n, m) && s1[i] == s2[i])
            i++;
            
        int j1 = n-1;
        int j2 = m-1;
        
        while(i<min(n, m) && s1[i] == s2[i])
            i++;
    
        while(j1 > -1 && j2 > -1 && s1[j1] == s2[j2]) {
            j1--;
            j2--;
        }

        bool found = 0;
        for (int k=0 ; k<=i ; k++) {
            if (found) break;
            string sb1 = "";
            string sb2 = "";
            for (int d=1 ; d<=10 ; d++) {
                if (found) break;
                if (k+d-1 >= n)
                    break;

                sb1 += s1[k+d-1];

                if (k+d-1 < j1)
                    continue;

                int sb1r = n-k-d;
                int sb2s = m-k-sb1r;

                if (sb2s <= 0 || sb2s > 10 || k+sb2s-1 < j2)
                    continue;

                sb2 = s2.substr(k, sb2s);

                for (auto &a:lists) {
                    if (found) break;
                    found = a.count(sb1) && a.count(sb2);
                }

                if (found) break;
            }
        }

        if (found) {
                        cout<<"REJECT\n";
                    } else {
                        cout<<"OK\n";
                    }
        
    }
}
