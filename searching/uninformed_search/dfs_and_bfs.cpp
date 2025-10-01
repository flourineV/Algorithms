#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
bool visited[MAXN];

int n, m; // n: số đỉnh, m: số cạnh

//DFS 
void dfs(int u){
    visited[u] = true;
    cout << u << " ";

    for (int v : adj[u]){
        if (!visited[v]) dfs(v);
    }
}

//BFS
void bfs(int u){
    queue <int> q;
    visited[u] = true;
    q.push(u);

    while (!q.empty()){
        int w = q.front();
        q.pop();
        cout << u << " ";
        
        for (int v : adj[w]){
            if (!visited[v]){
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //Nhập n,m;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;

        //Đồ thị vô hướng
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //DFS run
    memset(visited, false, sizeof(visited));
    cout << "DFS: ";
    dfs(1);
    cout << "\n";

    //BFS run
    memset(visited,false, sizeof(visited)); //Reset lại mảng visited
    bfs(1);
    cout << "\n";

    return 0;
}