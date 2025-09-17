#include <bits/stdc++.h>
using namespace std;

using ll = long long;

pair<ll,vector<int>> tsp_bruteforce(int n, const vector<vector<ll>>& cost){
    vector <int> cities;
    for (int i = 1; i < n; ++i) cities.push_back(i);
 
    ll best = LLONG_MAX;
    vector<int> bestPath;

    sort(cities.begin(), cities.end());

    //Chạy hết hoán vị
    for (bool cont = true; cont; cont = next_permutation(cities.begin(),cities.end())){
        ll path_cost = 0;
        int prev = 0;
        for (int city : cities){
            path_cost += cost[prev][city];
            prev = city;
        }
        path_cost += cost[prev][0];
        if (path_cost < best){
            best = path_cost;
            bestPath = cities;
        }
    }
    return {best, bestPath};
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

    auto [best, path] = tsp_bruteforce(n,cost);

    if (best == LLONG_MAX || path.empty()){
        cout << "No solutions\n";
        return 0;
    }
    //In lộ trình tối ưu
    cout << best << "\n";
    cout << 0;
    for (int v : path) cout << " " << v;
    cout << " " << 0 << "\n";
    return 0;
}