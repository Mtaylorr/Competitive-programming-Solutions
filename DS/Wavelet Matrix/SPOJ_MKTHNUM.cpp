// Mtaylor
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
typedef long long ll;
const int N = 3e5 + 5;
 
struct BitVectorRank {
    typedef unsigned u32;
    typedef size_t Index;
    Index length, blockslength, count;
    vector<u32> blocks;
    vector<Index> ranktable;
    BitVectorRank(Index len = 0) { init(len); }
    void init(Index len) {
        length = len;
        blockslength = (len + 31) / 32 + 1;
        blocks.assign(blockslength, 0);
    }
    inline void set(Index i) {
        // add element to set
        blocks[i / 32] |= 1 << i % 32;
    }
    void build() {
        count = 0;
        if (length == 0) return;
        ranktable.assign(blockslength + 1, 0);
        for (Index i = 0; i < blockslength; i++) {
            ranktable[i] = count;
            count += popcount(blocks[i]);
        }
        ranktable[blockslength] = count;
    }
    inline bool access(Index pos) const {
        // check if element in index pos exist (0 based)
        return blocks[pos / 32] >> pos % 32 & 1;
    }
    inline Index rank(Index pos) const {
        // count the the number of elements between [0..pos)
        int block_idx = pos / 32;
        return ranktable[block_idx] + popcount(blocks[block_idx] & (1U << pos % 32) - 1);
    }
    inline Index rank(bool b, Index pos) const { return b ? rank(pos) : pos - rank(pos); }
    inline Index rank(bool b, Index left, Index right) const { return rank(b, right) - rank(b, left); }
 
   private:
    static inline int popcount(u32 x) {
        x = x - ((x >> 1) & 0x55555555);
        x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
        return ((x + (x >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
    }
};
 
struct Compressor {
    vector<ll> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(ll x) { values.pb(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(ll x) { return lower_bound(all(values), x) - values.begin(); }
    int greatestSmallerThanOrEqual(ll x) { return (upper_bound(all(values), x) - values.begin()) - 1; }
    int greaterThanOrEqual(ll x) { return (lower_bound(all(values), x) - values.begin()); }
    ll decompress(int p) { return values[p]; }
} compressor;
 
struct WaveletMatrix {
    typedef BitVectorRank BitVector;
    typedef unsigned int Val;
    typedef size_t Index;
    int bitnum;
    Index length;
    Val maxval;
    vector<BitVector> bitvectors;
    vector<Index> mids;
    Compressor compressor;
 
    WaveletMatrix() { init(vector<Val>()); }
    void init(const vector<Val> &data, bool compress = false) {
        if (compress) {
            compressor.init();
        }
        for (auto &u : data) {
            compressor.add(u);
        }
        compressor.run();
        length = data.size();
        maxval = length == 0 ? 0 : *max_element(data.begin(), data.end());
        bitnum = 1;
        while ((maxval >> 1 >> (bitnum - 1)) != 0) ++bitnum;
 
        bitvectors.assign(bitnum, BitVector(length));
        mids.resize(bitnum);
 
        vector<Val> cur = data, next;
        next.resize(length);
        for (int i = 0; i < bitnum; i++) {
            Val mask = Val(1) << (bitnum - 1 - i);
            Index zeros = 0;
            for (Index j = 0, n = length; j < n; j++) zeros += (cur[j] & mask) == 0;
            mids[i] = zeros;
 
            BitVector &bv = bitvectors[i];
            Index zeroPos = 0, onePos = zeros;
            for (Index j = 0, n = length; j < n; j++) {
                bool b = (cur[j] & mask) != 0;
                if (b)
                    next[onePos++] = cur[j], bv.set(j);
                else
                    next[zeroPos++] = cur[j];
            }
            bv.build();
            next.swap(cur);
        }
    }
    Val access(Index pos) {
        Val val = 0;
        for (int i = 0; i < bitnum; i++) {
            const BitVector &bv = bitvectors[i];
            bool dir = bv.access(pos);
            val = val << 1 | (dir ? 1 : 0);
            pos = bv.rank(dir, pos);
            if (dir) pos += mids[i];
        }
        return val;
    }
 
    Val kth_min(int left, int right, int k) {
        // k 0 based
        return kth_max(left, right, right - left - 1 - k);
    }
    Val kth_max(int left, int right, int k) {
        // k 0 based
        if (k < 0 || right - left <= k) {
            return -1;
        }
        Val val = 0;
        for (int i = 0; i < bitnum; i++) {
            const BitVector &bv = bitvectors[i];
            int count = bv.rank(true, left, right);
            bool dir = k < count;
            val = val << 1 | (dir ? 1 : 0);
            if (!dir) k -= count;
            left = bv.rank(dir, left), right = bv.rank(dir, right);
            if (dir) left += mids[i], right += mids[i];
        }
        return val;
    }
    int rank_all(Val val, int left, int right, int &res_lt, int &res_gt) {
        if (val > maxval) {
            res_lt = right - left;
            res_gt = 0;
            return 0;
        }
        res_lt = res_gt = 0;
        for (int i = 0; i < bitnum; i++) {
            const BitVector &bv = bitvectors[i];
            bool dir = val >> (bitnum - i - 1) & 1;
            int leftcount = bv.rank(dir, left), rightcount = bv.rank(dir, right);
            (dir ? res_lt : res_gt) += (right - left) - (rightcount - leftcount);
            left = leftcount, right = rightcount;
            if (dir) left += mids[i], right += mids[i];
        }
        return right - left;
    }
} wm;
 
template <typename T>
struct CompressedWaveletMatrix {
    typedef size_t Index;
    WaveletMatrix wm;
    Compressor compressor;
    CompressedWaveletMatrix() { wm.init(vector<WaveletMatrix::Val>()); }
    void init(const vector<T> &data) {
        compressor.init();
        for (auto &u : data) {
            compressor.add(u);
        }
        vector<WaveletMatrix::Val> ndata;
        compressor.run();
        for (auto &u : data) {
            ndata.push_back(compressor.compress(u));
        }
        wm.init(ndata);
    }
 
    T access(Index pos) { return compressor.values[wm.access(pos)]; }
 
    T kth_min(int left, int right, int k) {
        // k 0 based
        return compressor.values[wm.kth_min(left, right, k)];
    }
 
    T kth_max(int left, int right, int k) {
        // k 0 based
        return compressor.values[wm.kth_max(left, right, k)];
    }
    int rank_all(T val, int left, int right, int &res_lt, int &res_gt) {
        WaveletMatrix::Val p = compressor.greaterThanOrEqual(val);
        return wm.rank_all(p, left, right, res_lt, res_gt);
    }
};
CompressedWaveletMatrix<ll> cwm;
 
int n, q;
vector<ll> a;
int l, r, x;
void test_case() {
    cin >> n >> q;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cwm.init(a);
    for (int i = 0; i < q; i++) {
        cin >> l >> r >> x;
        --l, --r, --x;
        int ans = cwm.kth_min(l, r + 1, x);
        cout << ans << endl;
    }
}
 
int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
