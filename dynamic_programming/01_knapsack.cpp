#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    cin >> n >> W; // n = số món, W = sức chứa

    vector<int> weight(n+1), value(n+1);
    for (int i = 1; i <= n; i++){
        cin >> weight[i] >> value[i];
    }
    vector<int> dp(W+1,0);

    for (int i = 1; i <= n; i++){
        for (int w = W; w >= weight[i]; w--){
            dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
        }
    }

    cout << dp[W] << "\n";
    return 0;
}