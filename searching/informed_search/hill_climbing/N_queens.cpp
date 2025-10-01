#include <bits/stdc++.h>
using namespace std;

// hill_climbing: O(kN) với k = số bước thực hiện
// steepeat ascent hill_climbing: O(kN^3) / O(kN^4)

// Tính số xung đột (số cặp queen tấn công nhau)
int computeConflicts(const vector<int> &state)
{
    int n = state.size();
    int conflicts = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (state[i] == state[j] || abs(state[i] - state[j]) == abs(i - j)) // trùng thẳng hoặc trùng chéo
            {
                conflicts++;
            }
        }
    }
    return conflicts;
}

// Sinh neighbor tốt nhất (Steepest Ascent)
vector<int> getBestNeighbor(const vector<int> &state)
{
    int n = state.size();
    vector<int> bestState = state;
    int bestConflicts = computeConflicts(state);

    for (int col = 0; col < n; col++)
    {
        for (int row = 0; row < n; row++)
        {
            if (row == state[col])
                continue;
            vector<int> newState = state;
            newState[col] = row;
            int newConflicts = computeConflicts(newState);
            if (newConflicts < bestConflicts)
            {
                bestConflicts = newConflicts;
                bestState = newState;
            }
        }
    }
    return bestState;
}

// Hill Climbing cho N-Queens
vector<int> hillClimbing(int n, int maxRestart = 1000)
{
    srand(time(0));

    for (int restart = 0; restart < maxRestart; restart++)
    {
        // random state ban đầu
        vector<int> state(n);
        for (int i = 0; i < n; i++)
        {
            state[i] = rand() % n;
        }

        while (true)
        {
            int conflicts = computeConflicts(state);
            if (conflicts == 0)
                return state; // tìm được nghiệm

            vector<int> neighbor = getBestNeighbor(state);

            if (computeConflicts(neighbor) >= conflicts)
            {
                // kẹt local optimum -> random restart
                break;
            }
            state = neighbor;
        }
    }
    return {}; // thất bại
}

int main()
{
    int N;
    cout << "Nhap N: ";
    cin >> N;

    vector<int> solution = hillClimbing(N);
    return 0;
}
