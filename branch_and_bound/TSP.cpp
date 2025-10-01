#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll bestCost = LLONG_MAX;
vector<int> bestPath;
vector<ll> minEdge; //cạnh nhỏ nhất từ mỗi thành phố

//Branch & Bound

void tsp_bnb(int n, const vector<vector<ll>>& cost, vector<int>& path, vector<bool> &visited, ll currCost, int level){
    //bound: currCost + tổng minEdge của các city chưa đi

    ll bound = currCost;
    for (int i = 0; i < n; i++){
        if (!visited[i]) bound += minEdge[i];
    }

    if (bound >= bestCost) return;

    if (level == n){
        ll totalCost = currCost + cost[path.back()][0];
        if (totalCost < bestCost){
            bestCost = totalCost;
            bestPath = path;
        } 
        return;
    }

    for (int city = 1; city < n; city++){
        if (!visited[city]){
            visited[city] = true;
            path.push_back(city);
            tsp_bnb(n, cost, path, visited, currCost + cost[path[path.size() - 2]][city], level + 1);
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

    //Chuẩn bị mảng minEdge
    minEdge.assign(n, LLONG_MAX);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i != j) minEdge[i] = min(minEdge[i], cost[i][j]);
        }
    }

    vector<bool> visited(n,false);
    visited[0] = true;
    vector<int> path = {0};

    tsp_bnb(n, cost, path, visited, 0, 1);
    cout << bestCost << "\n";
    cout << "0" << "";
    for (int v : bestPath){
        cout << v << " ";
    }
    cout << 0 << "\n";
    return 0;
}