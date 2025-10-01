// Một bảng 3x3 với các ô trong đó có số từ 1 ->8 và 1 ô trống,
// các ô được đặt ở các vị trí ngẫu nhiên, ô trống và ô số có thể đổi chỗ cho nhau,
// tìm cách di chuyển các ô sao cho các con số về đúng thứ tự,
// bài toán đặt ra ở đây là tìm phương án tối ưu sao cho số lần di chuyển là ít nhất.

// Code cả 4 thuật toán dfs, bfs, best-first search và A* search
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    vector<int> state;        // trạng thái 8 puzzle
    int g, h;                 // g = cost từ start (số lần chuyển vị trí tile đã thực hiện), h = heuristic (số tile nằm sai vị trí)
    vector<vector<int>> path; // lưu vết đường đi
};

// Định nghĩa goal state
vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};

// In trạng thái
void printState(const vector<int> &s)
{
    for (int i = 0; i < 9; i++)
    {
        cout << (s[i] ? to_string(s[i]) : " ") << " ";
        if ((i + 1) % 3 == 0)
            cout << "\n";
    }
    cout << "-----\n";
}

// heuristic h1(n): số ô sai vị trí
int misplaced(const vector<int> &s)
{
    int cnt = 0;
    for (int i = 0; i < 9; i++)
    {
        if (s[i] && s[i] != goal[i])
            cnt++;
    }
    return cnt;
}

// heuristic h2(n): Manhattan distance
int manhattan(const vector<int> &s)
{
    int dist = 0;
    for (int i = 0; i < 9; i++)
    {
        if (s[i] == 0)
            continue;
        int val = s[i] - 1;
        dist += abs(i / 3 - val / 3) + abs(i % 3 - val % 3);
    }
    return dist;
}

vector<vector<int>> neighbors(const vector<int> &s)
{
    vector<vector<int>> res;                           // tất cả các trạng thái
    int idx = find(s.begin(), s.end(), 0) - s.begin(); // tìm index của ô 0 trong state
    int x = idx / 3, y = idx % 3;                      // tọa độ của ô 0(x,y) trong state
    vector<pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto [dx, dy] : moves)
    {
        int nx = x + dx, ny = y + dy;
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3)
        {
            vector<int> ns = s;
            swap(ns[x * 3 + y], ns[nx * 3 + ny]); // tọa độ trong mảng 1 chiều, lúc ra 2 chiều thì chia, lúc về 1 chiều thì nhân
            res.push_back(ns);
        }
    }
    return res;
}

// Check visited
string encode(const vector<int> &s)
{
    string key = "";
    for (int v : s)
        key += to_string(v);
    return key;
}

void DFS(vector<int> start)
{
    stack<Node> st;
    unordered_set<string> visited;
    st.push({start, 0, 0, {start}});

    while (!st.empty())
    {
        Node cur = st.top();
        st.pop();
        if (cur.state == goal)
        {
            cout << "DFS found solution in " << cur.path.size() - 1 << "steps\n";
            for (auto &p : cur.path)
                printState(p);
            return;
        }
        string key = encode(cur.state);
        if (visited.count(key))
            continue; // nếu trạng thái này đã đi rồi
        visited.insert(key);
        for (auto &n : neighbors(cur.state))
        {
            auto newPath = cur.path;
            newPath.push_back(n);
            st.push({n, 0, 0, {newPath}});
        }
    }
    cout << "DFS failed \n";
}

void BFS(vector<int> start)
{
    queue<Node> q;
    unordered_set<string> visited;

    q.push({start, 0, 0, {start}});

    while (!q.empty())
    {
        Node cur = q.front();
        q.pop();
        if (cur.state == goal)
        {
            cout << "BFS found solution in " << cur.path.size() - 1 << "steps\n";
            for (auto &p : cur.path)
                printState(p);
            return;
        }

        string key = encode(cur.state);
        if (visited.count(key))
            continue;
        visited.insert(key);

        for (auto &n : neighbors(cur.state))
        {
            auto newPath = cur.path;
            newPath.push_back(n);
            q.push({n, 0, 0, newPath});
        }
    }
    cout << "BFS failed\n";
}

void GreedyBestFS(vector<int> start)
{
    auto cmp = [](Node &a, Node &b)
    { return a.h > b.h; }; // dùng hàm heuristic ở đây
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    unordered_set<string> visited;
    pq.push({start, 0, misplaced(start), {start}});

    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (cur.state == goal)
        {
            cout << "GreedyBestFS found solution in " << cur.path.size() - 1 << "steps\n";
            for (auto &p : cur.path)
                printState(p);
            return;
        }

        string key = encode(cur.state);
        if (visited.count(key))
            continue;
        visited.insert(key);

        for (auto &n : neighbors(cur.state))
        {
            auto newPath = cur.path;
            newPath.push_back(n);
            pq.push({n, 0, misplaced(n), newPath}); // g đang = 0
        }
    }
    cout << "Greedy Best-First failed\n";
}

void Astar(vector<int> start)
{
    auto cmp = [](Node &a, Node &b)
    { return (a.g + a.h) > (b.g + b.h); };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    unordered_set<string> visited;
    pq.push({start, 0, manhattan(start), {start}});

    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (cur.state == goal)
        {
            cout << "A* found solution in " << cur.path.size() - 1 << " steps\n";
            for (auto &p : cur.path)
                printState(p);
            return;
        }
        string key = encode(cur.state);
        if (visited.count(key))
            continue;
        visited.insert(key);
        for (auto &n : neighbors(cur.state))
        {
            auto newPath = cur.path;
            newPath.push_back(n);
            pq.push({n, cur.g + 1, manhattan(n), newPath});
        }
    }
    cout << "A* failed\n";
}

int main()
{
    vector<int> start = {1, 2, 3, 4, 0, 6, 7, 5, 8}; // trạng thái ban đầu

    DFS(start);
    BFS(start);
    GreedyBestFS(start);
    Astar(start);

    return 0;
}
