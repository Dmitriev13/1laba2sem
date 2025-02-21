#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
using namespace std;

int minPath(const vector<vector<int>>& bag, vector<vector<pair<int, int>>>& path) {
    int rows = bag.size();
    int cols = bag[0].size();
    vector<vector<int>> dp(rows, vector<int>(cols, 0));

    dp[0][cols - 1] = bag[0][cols - 1];

    for (int r = 0; r < rows; ++r) {
        for (int c = cols - 1; c >= 0; --c) {
            if (r == 0 && c == cols - 1) continue;
            if (r == 0) {
                dp[r][c] = dp[r][c + 1] + bag[r][c];
                path[r][c] = { r, c + 1 };
            }
            else if (c == cols - 1) {
                dp[r][c] = dp[r - 1][c] + bag[r][c];
                path[r][c] = { r - 1, c };
            }
            else {
                if (dp[r - 1][c] < dp[r][c + 1]) {
                    dp[r][c] = dp[r - 1][c] + bag[r][c];
                    path[r][c] = { r - 1, c };
                }
                else {
                    dp[r][c] = dp[r][c + 1] + bag[r][c];
                    path[r][c] = { r, c + 1 };
                }
            }
        }
    }
    return dp[rows - 1][0];
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n;
    input >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    vector<vector<pair<int, int>>> path(n, vector<pair<int, int>>(n, { -1, -1 }));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            input >> grid[i][j];

    int minTrouble = minPath(grid, path);
    output << minTrouble << endl;

    vector<pair<int, int>> route;
    int r = n - 1, c = 0;
    while (r != 0 or c != n - 1) {
        route.push_back({ r, c });
        auto prev = path[r][c];
        r = prev.first;
        c = prev.second;
    }
    route.push_back({ 0, n - 1 });
    reverse(route.begin(), route.end());

    for (const auto& p : route)
        output << p.first + 1 << " " << p.second + 1 << endl;
    cout << "Ответ записан в output.txt";

    return 0;
}
