#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

#define mod 100000007

using namespace std;

class analyzer;
unordered_map<string, analyzer> mclass;

class analyzer {
public:
    int type;
    string var, expr;
    bool computed;
    long long cacheLen;
    void* old;

    analyzer(int t, string v, string e = "")
        : type(t), var(v), expr(e), computed(false), cacheLen(0) {
		old = (analyzer*)new analyzer();
    }

    analyzer() : type(0), var(""), expr(""), computed(false), cacheLen(0) {}

    long long caculateLen() {
		//analyzer old = *this;
        
        long long len = 0;
        string token;
        for (size_t i = 0; i < expr.size();) {
            while (i < expr.size() && expr[i] == ' ') ++i;
            if (i >= expr.size()) break;

            size_t j = i;
            while (j < expr.size() && expr[j] != ' ') ++j;
            token = expr.substr(i, j - i);
            i = j;

            if (!token.empty()) {
                if (token[0] == '$') {
                    string subVar = token.substr(1);
                    len += mclass[subVar].caculateLen();
                }
                else {
                    len += token.size();
                }
            }
            len %= mod;
        }
        return len % mod;
    }

    friend ostream& operator<<(ostream& out, analyzer& a) {
        if (a.type == 2 || a.type == 1) {
            out << a.caculateLen();
        }
        else {
            out << (a.expr.size() % mod);
        }
        return out;
    }

};

int main() {
    int op, n;
    string var, expr;

    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        string temp;
        getline(cin, temp);

        stringstream ss(temp);
        ss >> op >> var;

        if (op == 3) {
            cout << mclass[var] << endl;
        }
        else {
            expr = temp;

            auto p = expr.find(" ");
            expr.erase(0, p + 1);
            p = expr.find(" ");
            expr.erase(0, p + 1);

            // 重新赋值时，旧缓存会被覆盖，自然失效
            mclass[var] = analyzer(op, var, expr);
        }
    }
}
