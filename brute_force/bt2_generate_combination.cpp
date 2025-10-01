#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<int> arr; //tập n phần tử
vector<int>curr; //tập con m phần tử

void generateCombination(int i){
    if ((int)curr.size() == m){
        for (int x : curr){
            cout << x << " ";
        }
        cout << "\n";
        return;
    }

    if (i >= n) return;

    //Chọn i
    curr.push_back(arr[i]);
    generateCombination(i + 1);
    curr.pop_back();

    //Không chọn i
    generateCombination(i + 1);
}


int main(){
    cin >> n >> m;
    arr.resize(n);

    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }

    generateCombination(0);
    return 0;
}