#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll bestCost = LLONG_MAX;
vector<int> bestPath;

void tsp_backtrack(int n, const vector<vector<ll>>& cost, vector<int>&path, vector<bool>& visited, ll currCost, int level){
    if (currCost >= bestCost) return; //cắt nhánh

    if (level == n){
        ll totalCost = currCost + cost[path.back()][0];
        if (totalCost < bestCost){
            bestCost = totalCost;
            bestPath = path;
        }
    }

    for (int city = 1; city < n; city++){
        if (!visited[city]){
            visited[city] = true;
            path.push_back(city);
            
            //duyệt hết cây
            tsp_backtrack(n, cost, path, visited, currCost + cost[path[path.size() - 2]][city], level + 1);
            path.pop_back();
            visited[city] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n; //nhập số lượng thành phố

    vector<vector<ll>> cost(n, vector<ll>(n));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cin >> cost[i][j];
        }
    }
    vector<bool> visited(n, false);
    vector<int> path = {0};
    visited[0] = true;

    tsp_backtrack(n, cost, path, visited, 0, 1);

    //In lộ trình tối ưu
    cout << bestCost << "\n";
    for (int v : bestPath) cout << v;
    cout << " " << 0 << "\n";
    return 0;
}