const int MOD[2] = {(int) (1e9 + 7), (int) (1e9 + 9)};


const int BASE[2] = {37, 31};

struct modularOperations {
    static int mul(int u, int v, int mod) {
        return ((u % mod) * 1ll * (v % mod)) % mod;
    }

    static int add(int u, int v, int mod) {
        return ((u % mod) + 0ll + (v % mod) + mod) % mod;
    }

    static int sub(int u, int v, int mod) {
        return ((u % mod) + 0ll - (v % mod) + mod) % mod;
    }

    static int powe(int u, int v, int mod) {
        int ans = 1;
        int acc = u;
        while (v) {
            if (v % 2) {
                ans = mul(ans, acc, mod);
            }
            acc = mul(acc, acc, mod);
            v /= 2;
        }
        return ans;
    }

    static int inv(int u, int mod) {
        return powe(u, mod - 2, mod);
    }
} mop;

const int invBASE[2] = {mop.inv(BASE[0], MOD[0]), mop.inv(BASE[1], MOD[1])};


struct CHASH {
    static const int SEPERATOR = int(1e9) + 11;/// make sure this is bigger than both mods !!!!
    int h1;
    int h2;

    CHASH(int _h1, int _h2 = 0) {
        h1 = _h1;
        h2 = _h2;
    }

    CHASH() {
        h1 = 0;
        h2 = 0;
    }

    CHASH left() {
        /// multiply the hash by the BASE
        return CHASH(mop.mul(h1, BASE[0], MOD[0]), mop.mul(h2, BASE[1], MOD[1]));
    }

    CHASH right() {
        /// divide the hash by the BASE
        return CHASH(mop.mul(h1, invBASE[0], MOD[0]), mop.mul(h2, invBASE[1], MOD[1]));
    }

    CHASH operator+(const CHASH &a) const {
        return CHASH(h1 + a.h1, h2 + a.h2);
    }

    CHASH operator-(const CHASH &a) const {
        return CHASH(h1 - a.h1, h2 - a.h2);
    }


    static CHASH fromOneHash(ll h) {
        /// Convert the long long number to CHASH struct : the number should be  h1 + SEPERATOR * h2
        return CHASH((int) (h % SEPERATOR), (int) (h / SEPERATOR));
    }

    ll convertToOneHash() {
        /// Convert the 2D hash to one single long long number
        return h1 + h2 * 1ll * SEPERATOR;
    }

    static CHASH fromPair(pair<int, int> p) {
        /// convert the pair of 2 integer to CHASH struct
        return CHASH((int) (p.fi), (int) (p.se));
    }

    pair<int, int> convertToPair() {
        /// convert the CHASH struct to a pair of 2 integer
        return {h1, h2};
    }
};

class CustomHashing {
public :

    int MAX_LENGTH;
    int D;
    vector<vector<int> > po;

    CustomHashing(int max_length = 1, int dimension = 2) {
        MAX_LENGTH = max_length;
        D = dimension;
    }

    void init() {
        po.resize(this->D);
        for (int i = 0; i < D; i++) {
            po[i].assign(MAX_LENGTH + 1, 0);
            po[i][0] = 1;
            for (int j = 1; j <= MAX_LENGTH; j++) {
                po[i][j] = mop.mul(po[i][j - 1], BASE[i], MOD[i]);
            }
        }
    }

    CHASH getHash(string &s, bool rev = 0) {
        CHASH h;
        if (!rev) {
            for (int i = 0; i < s.size(); i++) {
                int v = (s[i] - 'a') + 1;
                h = h.left() + CHASH(v,v);
            }
        } else {
            for (int i = s.size() - 1; i >= 0; i--) {
                int v = (s[i] - 'a') + 1;
                h = h.left() + CHASH(v,v);
            }
        }
        return h;
    }

    CHASH getHash(vector<int> &s, bool rev = 0, int offset = 0) {
        /// Don't forget to change the BASE values to numbers greater than the maximum value !!!!
        ///  add offset to make all integer >=0
        CHASH h;
        if (!rev) {
            for (int i = 0; i < s.size(); i++) {
                int v = s[i]+1+offset;
                h = h.left() + CHASH(v,v);
            }
        } else {
            for (int i = s.size() - 1; i >= 0; i--) {
                int v = s[i]+1+offset;
                h = h.left() + CHASH(v,v);
            }
        }
        return h;
    }

};
