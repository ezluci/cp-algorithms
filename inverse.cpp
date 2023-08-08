void addSelf(int &x, int y) {
    x += y;
    if(x >= MOD) {
        x -= MOD;
    }
}
 
int add(int x, int y) {
    addSelf(x, y);
    return x;
}
 
void multSelf(int &x, int y) {
    x = (long long) x * y % MOD;
}
 
int mult(int x, int y) {
    multSelf(x, y);
    return x;
}

int fact(int n) {
    static vector<int> data(1, 1);
    for(int i = data.size(); i <= n; i++) {
        data.emplace_back(mult(data[i - 1], i));
    }
    return data[n];
}
 
int inv(int n) {
    static vector<int> data(2, 1);
    for(int i = data.size(); i <= n; i++) {
        data.emplace_back(mult(data[MOD % i], MOD - MOD / i));
    }
    return data[n];
}
 
int ifact(int n) {
    static vector<int> data(2, 1);
    for(int i = data.size(); i <= n; i++) {
        data.emplace_back(mult(data[i - 1], inv(i)));
    }
    return data[n];
}
 
int comb(int n, int k) {
    return mult(fact(n), mult(ifact(k), ifact(n - k)));
}
