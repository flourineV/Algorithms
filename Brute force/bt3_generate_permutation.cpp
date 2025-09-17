#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> arr; //tập gốc
vector<int>curr; //tập hoán vị đang xây
vector<bool> used; //đánh dấu phần tử đã dùng

void generatePermutation(){
    if ((int)curr.size() == n){
        for (int v : curr){
            cout << v << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < n; i++){
        if (!used[i]){
            used[i] = true;
            curr.push_back(i);
            generatePermutation();
            curr.pop_back();
            used[i] = false;
        }
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++){
        cin >> n;
    }
    generatePermutation();
    return 0;
}