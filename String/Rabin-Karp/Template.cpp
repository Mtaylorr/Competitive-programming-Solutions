const int MOD[2] = {(int)(1e9 + 7), (int)(1e9 + 9)};
const int BASE[2] = {37, 31}; // Don't forget to change when dealing with integer
                                //{100003,100043}
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

    static int powe(int u, ll v, int mod) {
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

    static int inv(const int u, int mod) { return powe(u, mod - 2, mod); }
} mop;
const int invBASE[2] = {mop.inv(BASE[0], MOD[0]), mop.inv(BASE[1], MOD[1])};
struct CHASH {
    static const int SEPERATOR =int(1e9) + 11;  
        /// make sure this is bigger than both mods !!!!
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

    void left() {
        /// multiply the hash by the BASE
        h1 = (h1*1ll*BASE[0])%MOD[0];
        h2 = (h2*1ll*BASE[1])%MOD[1];
    }

    void right() {
        /// divide the hash by the BASE
        h1 = (h1*1ll*invBASE[0])%MOD[0];
        h2 = (h2*1ll*invBASE[1])%MOD[1];
    }

    CHASH operator+(const CHASH &a) const {
        return CHASH((this->h1+0ll+a.h1)%MOD[0], (this->h2+0ll+a.h2)%MOD[1]);
    }
    CHASH& operator+=(const CHASH &a) {
        this->h1 = (this->h1+0ll+a.h1)%MOD[0];
        this->h2 = (this->h2+0ll+a.h2)%MOD[1];
        return *this;
    }

    CHASH operator-(const CHASH &a) const {
        return CHASH((this->h1+0ll-a.h1+MOD[0])%MOD[0],  (this->h2+0ll-a.h2+MOD[1])%MOD[1]);
    }

    CHASH& operator-=(const CHASH &a) {
        this->h1 = (this->h1+0ll-a.h1+MOD[0])%MOD[0];
        this->h2 = (this->h2+0ll-a.h2+MOD[1])%MOD[1];
        return *this;
    }

    static CHASH fromOneHash(ll h) {
        /// Convert the long long number to CHASH struct : the number should be
        /// h1 + SEPERATOR * h2
        return CHASH((int)(h % SEPERATOR), (int)(h / SEPERATOR));
    }

    ll convertToOneHash() {
        /// Convert the 2D hash to one single long long number
        return h1 + h2 * 1ll * SEPERATOR;
    }

    static CHASH fromPair(pair<int, int> p) {
        /// convert the pair of 2 integer to CHASH struct
        return CHASH((int)(p.fi), (int)(p.se));
    }

    pair<int, int> convertToPair() {
        /// convert the CHASH struct to a pair of 2 integer
        return {h1, h2};
    }
};

class CustomHashing {
   public:
    int MAX_LENGTH;
    int D;
    vector<vector<int> > po;

    CustomHashing(int max_length = 1, int dimension = 2) {
        MAX_LENGTH = max_length;
        D = dimension;
        init();
    }

    void init() {
        po.resize(this->D);
        for (int i = 0; i < D; i++) {
            po[i].assign(MAX_LENGTH + 1, 0);
            po[i][0] = 1;
            for (int j = 1; j <= MAX_LENGTH; j++) {
                po[i][j] = (po[i][j - 1]*1ll*BASE[i])% MOD[i];
            }
        }
    }

    CHASH get_ith_Hash(char &c, int i) {
        int v = (c-'a')+1;
        return CHASH((v*1ll*po[0][i])%MOD[0],(v*1ll*po[1][i])%MOD[1]);
    }
    CHASH get_ith_Hash(int &c, int i, int offset = 0) {
        int v = c + offset + 1;
        return CHASH((v*1ll*po[0][i])%MOD[0],(v*1ll*po[1][i])%MOD[1]);
    }

    CHASH getHash(string &s, bool rev = 0) {
        CHASH h;
        if (!rev) {
            for (int i = 0; i < s.size(); i++) {
                int v = (s[i] - 'a') + 1;
                h.left();
                h+=CHASH(v,v);
            }
        } else {
            for (int i = s.size() - 1; i >= 0; i--) {
                int v = (s[i] - 'a') + 1;
                h.left();
                h+=CHASH(v,v);
            }
        }
        return h;
    }

    CHASH getHash(vector<int> &s, bool rev = 0, int offset = 0) {
        /// Don't forget to change the BASE values to numbers greater than the
        /// maximum value !!!!
        ///  add offset to make all integer >=0
        CHASH h;
        if (!rev) {
            for (int i = 0; i < s.size(); i++) {
                int v = s[i] + 1 + offset;
                h.left();
                h+=CHASH(v,v);
            }
        } else {
            for (int i = s.size() - 1; i >= 0; i--) {
                int v = s[i] + 1 + offset;
                h.left();
                h+=CHASH(v,v);
            }
        }
        return h;
    }
}ch(200000);
