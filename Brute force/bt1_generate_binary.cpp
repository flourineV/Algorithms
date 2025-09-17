#include <bits/stdc++.h>
using namespace std;

int n;

void generateBinary(int i, string &s){
    if (i == n){
        cout << s << "\n";
        return;
    }
    s[i] = 0; generateBinary(i+1,s);
    s[i] = 1; generateBinary(i+1,s);

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    string s = "";
    for (int i = 0; i < n; i++) s+='0';
    generateBinary(0, s);
    return 0;
}