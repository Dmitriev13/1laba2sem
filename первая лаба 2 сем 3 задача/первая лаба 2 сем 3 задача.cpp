#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int fourOrMore(int n, int k) {

    vector<vector<int>> dp(n + 1, vector<int>(5, 0));

    dp[1][0] = k - 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            if (dp[i][j] == 0) continue;
            if (j == 4) {
                dp[i + 1][4] += dp[i][4] * k;
            }
            else {
                int newRun = j + 1;
                if (newRun == 4) {
                    dp[i + 1][4] += dp[i][j];
                }
                else {
                    dp[i + 1][newRun] += dp[i][j];
                }
                dp[i + 1][0] += dp[i][j] * (k - 1);
            }
        }
    }

    return dp[n][4]; 
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Введите n(кол-во разрядов) и k (систему счисления)" << endl;
    int n, k;
    cin >> n >> k;
    cout << "Всего чисел с 4 и более нулями, идущими подряд:" << endl;
    cout << fourOrMore(n, k) << endl;
    return 0;
}
