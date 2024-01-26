#include <bits/stdc++.h>

#include "testlib.h"

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

using namespace std;

void generateTree(int n, int child_lb, int child_ub, int dpth_lb, int dpth_ub,
                  vector<pair<int, int> >& ans, vector<int>& g_nodes,
                  bool apply_permutation) {
    /*
        n        : the number of nodes
        child_lb : is the minimum number of children of good nodes
        child_ub : is the maximum number of children of good nodes
        dpth_lb  : is the minimum depth to go from good node to a child good
       node dpth_ub  : is the maximum depth to go from good node to another good
       node ans      : vector of pairs contains the edges of the tree
        ===============================================================================
        ## Definitions
        We call a good node is the node that will explore and add childrens to
       it, other nodes will only be used in the path to get the appropriate
       depth
        ===============================================================================
        ##Example of usage :
        Generate a full binary Tree:
            child_lb = 2, child_ub = 2, dpth_lb = 1, dpth_ub = 1
        -----------------------------
        Generate a Tree with every node has a depth of size >= k passing through
            it from it's subtree if possible child_lb = 2, child_ub = any, dpth_lb =
            k/2, dpth_ub = k/2 + small value (to add randomness)
        -----------------------------
        Generate total random Tree: child_lb = 0, child_ub = 0, dpth_lb = 0, dpth_ub = 0
        ================================================================================
        This is the general format of the tree:
                         u                    dpth_lb <= L1, L2, L3 <= dpth_ub
                /   /    |     \    \ L1      child_lb <= k <= child_ub
            L3 /   /     |L2    \    xk       If possible , it will stop
       generating as soon /   /      x..     \            as it reaches n nodes.
             x1  x2               xk-1
    */
    assert(child_lb <= child_ub);
    assert(dpth_lb <= dpth_ub);
    ans.clear();
    g_nodes.clear();
    vector<int> perm;
    for (int i = 1; i <= n; i++) {
        perm.push_back(i);
    }
    shuffle(perm.begin(), perm.end());
    queue<int> good_nodes;
    int cur = 2;
    good_nodes.push(1);
    g_nodes.pb(1);
    for (int i = 1; i <= n - 1; i++) {
        if (good_nodes.size() == 0) {
            break;
        }
        int u = good_nodes.front();
        good_nodes.pop();
        int childrens = rnd.next(child_lb, child_ub);
        for (int j = 0; j < childrens; j++) {
            if (cur > n) break;
            int p = u;
            int d = rnd.next(dpth_lb, dpth_ub);
            for (int k = 0; k < d; k++) {
                if (cur > n) break;
                ans.push_back({p, cur});
                p = cur;
                cur++;
            }
            g_nodes.push_back(p);
            good_nodes.push(p);
        }
    }
    while (cur <= n) {
        ans.push_back({cur, rnd.next(1, cur - 1)});
        cur++;
    }
    //  apply permutation if you want here
    if (apply_permutation) {
        for (auto& u : ans) {
            u.fi = perm[u.fi - 1];
            u.se = perm[u.se - 1];
        }
        for (auto& u : g_nodes) {
            u = perm[u - 1];
        }
    }
}
